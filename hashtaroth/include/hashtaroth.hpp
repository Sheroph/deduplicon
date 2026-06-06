#ifndef HASH_EXTRACTOR_HPP
#define HASH_EXTRACTOR_HPP

#include <atomic>
#include <condition_variable>
#include <list>
#include <thread>

#include <hash_job.hpp>

namespace hashtaroth {

class Hashtaroth {
public:
  Hashtaroth();
  ~Hashtaroth();


  void start();

private:

  std::list<hash_job_t> job_queue_;
  std::atomic_bool running_;

  std::condition_variable job_queue_cond_;
  std::mutex job_queue_mut_;

  std::thread server_thread_;
  
  void get_next_job(hash_job_t &job);
  void hash_path(hash_job_t &job, EVP_MD_CTX *openssl_ctx, EVP_MD *msg_digest);

  void run();
};

} // namespace hashtaroth

#endif // HASH_EXTRACTOR_HPP
