#ifndef HASH_JOB_HEADER
#define HASH_JOB_HEADER

#include <hash_response.hpp>

#include <filesystem>
#include <functional>

namespace hashtaroth {


class hash_job_t
{
  public:

    hash_job_t();
    hash_job_t(const std::filesystem::path file_path);

    std::filesystem::path get_file_path() const ;

    void set_file_path(const std::filesystem::path& file_path);

    
  protected:
    std::filesystem::path file_path_;
};


} // namespace hashtaroth
#endif // HASH_JOB_HEADER