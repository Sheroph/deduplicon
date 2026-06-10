#include <hash_job.hpp>

using namespace std;
using namespace std::filesystem;


namespace hashtaroth
{

  hash_job_t::hash_job_t(): file_path_("") {}

  hash_job_t::hash_job_t(const path file_path): file_path_(file_path) {}
  
  path hash_job_t::get_file_path() const {
    return file_path_;
  }

  void hash_job_t::set_file_path(const path& file_path) {
    file_path_ = file_path;
  }

} // namespace hashtaroth
