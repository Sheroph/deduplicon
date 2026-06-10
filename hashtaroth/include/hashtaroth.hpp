#ifndef HASH_EXTRACTOR_HPP
#define HASH_EXTRACTOR_HPP

#include <openssl/evp.h>

#include <atomic>
#include <condition_variable>
#include <list>
#include <thread>
#include <future>

#include <hash_job.hpp>

namespace hashtaroth {

typedef std::promise<hash_job_response_t> hash_job_promise_t;
typedef std::future<hash_job_response_t> hash_job_future_t;
typedef std::tuple<hash_job_t, hash_job_promise_t> internal_hash_job_t;

class Hashtaroth {
public:
  Hashtaroth();
  ~Hashtaroth();


  hash_job_future_t push_job(const hash_job_t& job);
  void start();

private:

  std::list<internal_hash_job_t> job_queue_;
  std::atomic_bool running_;

  std::condition_variable job_queue_cond_;
  std::mutex job_queue_mut_;

  std::thread server_thread_;
  
  void get_next_job(internal_hash_job_t &job);
  void hash_path(internal_hash_job_t &job, EVP_MD_CTX *openssl_ctx, EVP_MD *msg_digest);

  void run();
};

} // namespace hashtaroth

#endif // HASH_EXTRACTOR_HPP
