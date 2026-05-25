#ifndef HASH_JOB_HEADER
#define HASH_JOB_HEADER

#include <filesystem>
#include <openssl/evp.h>

namespace hashtaroth {

struct hash_job_response_t {
  unsigned char digest[EVP_MAX_MD_SIZE];
};

struct hash_job_t {
  hash_job_response_t response;
  std::filesystem::path file_path;
};

} // namespace hashtaroth
#endif // HASH_JOB_HEADER