#include <hashtaroth.hpp>

#include <fstream>
#include <mutex>
#include <cstring>
#include <iostream>

using namespace std;
using namespace std::filesystem;

namespace hashtaroth
{

  Hashtaroth::Hashtaroth() : running_(false) {};

  Hashtaroth::~Hashtaroth()
  {
    const bool was_running = running_;
    if(was_running)
    {
      running_ = false;
      job_queue_cond_.notify_all();
      server_thread_.join();
    }
  }

  hash_job_future_t Hashtaroth::push_job(const hash_job_t& job)
  {
    unique_lock<mutex> lock(job_queue_mut_);

    hash_job_promise_t promise;
    hash_job_future_t future{promise.get_future()};
    if(!running_)
    {
      promise.set_value(hash_job_response_t());
      return future;
    }


    job_queue_.push_back({job, std::move(promise)});
    job_queue_cond_.notify_all();
    return future;
  }

  void Hashtaroth::start()
  {
    if(running_)
    {
      return;
    }
    unique_lock<mutex> lock(job_queue_mut_);
    running_ = true;
    server_thread_ = std::move(thread(&Hashtaroth::run, this));
  }



  void Hashtaroth::get_next_job(internal_hash_job_t &job)
  {

    unique_lock<mutex> lock(job_queue_mut_);
    job_queue_cond_.wait(lock, [&]()
                         { return !job_queue_.empty() || !running_; });
    if (!running_)
    {
      return;
    }
    job.swap(job_queue_.front());
    job_queue_.pop_front();
  }

  void Hashtaroth::run()
  {
    // OpenSSL context
    EVP_MD_CTX *openssl_ctx = EVP_MD_CTX_new();
    EVP_MD *msg_digest = EVP_MD_fetch(nullptr, "SHA256", nullptr);

    while (running_)
    {
      internal_hash_job_t job;
      // Pop next job
      get_next_job(job);

      const path &file = get<hash_job_t>(job).get_file_path();
      if (!exists(file))
      {
        continue;
      }

      hash_path(job, openssl_ctx, msg_digest);
      EVP_MD_CTX_reset(openssl_ctx);
    }
    EVP_MD_CTX_free(openssl_ctx);
  }

  void Hashtaroth::hash_path(internal_hash_job_t &job, EVP_MD_CTX *openssl_ctx, EVP_MD *msg_digest)
  {

    static constexpr size_t buffer_size{8192};
    static char buffer[buffer_size];
    const path& file_path{get<hash_job_t>(job).get_file_path()};

    std::ifstream file(file_path, std::ios::binary);
    if (!file)
    {
      return;
    }

    EVP_DigestInit_ex(openssl_ctx, msg_digest, nullptr);

    size_t bytes_to_read = file_size(file_path);    
    while (bytes_to_read > 0)
    {
      const size_t bytes_read = file.readsome(buffer, buffer_size);
      if(bytes_read) {
        EVP_DigestUpdate(openssl_ctx, buffer, bytes_read);
        bytes_to_read -= bytes_read;
      }
    }
    hash_job_response_t response;
    memset(response.digest, 0, EVP_MAX_MD_SIZE);
    EVP_DigestFinal_ex(openssl_ctx, response.digest, NULL);
    get<hash_job_promise_t>(job).set_value(response);
  }

} // namespace hashtaroth
