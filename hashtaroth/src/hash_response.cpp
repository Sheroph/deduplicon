#include <hash_response.hpp>

#include <cstring>

using namespace std;

namespace hashtaroth
{
  hash_job_response_t::hash_job_response_t()
  {
    memset(digest, 0, EVP_MAX_MD_SIZE);
  }

  hash_job_response_t::hash_job_response_t(const hash_job_response_t &response)
  {
    memcpy(digest, response.digest, EVP_MAX_MD_SIZE);
  }

} // namespace hashtaroth


ostream& operator<<(ostream& out, const hashtaroth::hash_job_response_t& response) {

  out << "digest : ";
  for(size_t i=0;i< EVP_MAX_MD_SIZE; ++i) {
    out << std::hex << static_cast<int>(response.digest[i]) << std::dec << " ";
  }

  return out;
}