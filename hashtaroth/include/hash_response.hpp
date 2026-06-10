#ifndef HASH_RESPONSE_HPP
#define HASH_RESPONSE_HPP

#include <openssl/evp.h>
#include <iostream>

namespace hashtaroth
{

  class hash_job_response_t
  {

  public:
    hash_job_response_t();
    hash_job_response_t(const hash_job_response_t &response);

    unsigned char digest[EVP_MAX_MD_SIZE];
  };

} // namespace hashtaroth

std::ostream& operator<<(std::ostream&, const hashtaroth::hash_job_response_t&);

#endif // HASH_RESPONSE_HPP