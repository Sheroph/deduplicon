#ifndef HASH_EXTRACTOR_HPP
#define HASH_EXTRACTOR_HPP

#include <atomic>
#include <condition_variable>
#include <list>

#include <hash_job.hpp>

namespace hashtaroth {

class Hashtaroth {
public:
  Hashtaroth();
  ~Hashtaroth();

private:

  std::list<hash_job_t> job_queue_;
  std::atomic_bool running_;

  std::condition_variable job_queue_cond_;
  std::mutex job_queue_mut;

  void run();

private:
  void get_next_job(hash_job_t &job);
  void hash_loop();
  void hash_path(hash_job_t &job, EVP_MD_CTX *openssl_ctx, EVP_MD *msg_digest);
};

} // namespace hashtaroth

#endif // HASH_EXTRACTOR_HPP
