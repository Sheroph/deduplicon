#include <hashtaroth.hpp>

#include <fstream>
#include <mutex>
#include <cstring>

using namespace std;
using namespace std::filesystem;

namespace hashtaroth {

Hashtaroth::Hashtaroth() : running_(false) {};


Hashtaroth::~Hashtaroth() {
  running_ = false;
  job_queue_cond_.notify_all();

}

void Hashtaroth::get_next_job(hash_job_t &job) {

  unique_lock<mutex> lock(job_queue_mut);
  job_queue_cond_.wait(lock, [&]() { return !job_queue_.empty() || !running_; });

  if (!running_) {
    return;
  }

  job = job_queue_.front();
  job_queue_.pop_front();
}

void Hashtaroth::hash_loop() {

  // OpenSSL context
  EVP_MD_CTX *openssl_ctx = EVP_MD_CTX_new();
  EVP_MD *msg_digest = EVP_MD_fetch(nullptr, "SHA256", nullptr);

  while (running_) {
    hash_job_t job;
    // Pop next job
    get_next_job(job);

    const path &file = job.file_path;
    if (!exists(file)) {
      continue;
    }

    hash_path(job, openssl_ctx, msg_digest);
    EVP_MD_CTX_reset(openssl_ctx);
  }
  EVP_MD_CTX_free(openssl_ctx);
}

void Hashtaroth::hash_path(hash_job_t &job, EVP_MD_CTX *openssl_ctx, EVP_MD *msg_digest) {

  static constexpr size_t buffer_size{8192};
  static char buffer[buffer_size];

  std::ifstream file(job.file_path.string(), std::ios::binary);
  if (!file) {
    return;
  }

  EVP_DigestInit_ex(openssl_ctx, msg_digest, nullptr);

  size_t bytes_read = 0;
  while (!file.eof()) {
    bytes_read = file.readsome(buffer, buffer_size);
    if (bytes_read > 0) {
      EVP_DigestUpdate(openssl_ctx, buffer, bytes_read);
    }
  }
  memset(job.response.digest, 0, EVP_MAX_MD_SIZE);
  EVP_DigestFinal_ex(openssl_ctx, job.response.digest, NULL);
}
} // namespace hashtaroth
