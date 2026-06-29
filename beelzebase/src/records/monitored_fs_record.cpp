#include <records/monitored_fs_record.hpp>

using namespace std;
using namespace std::filesystem;

namespace beelzebase
{

  MonitoredFSRecord::MonitoredFSRecord(const path &file_path,
                                       const size_t &file_size,
                                       const string &file_hash,
                                       const time_t &last_hash_update) : file_path_{file_path},
                                                                         file_size_{file_size},
                                                                         file_hash_{file_hash},
                                                                         last_hash_update_{last_hash_update} {}
  MonitoredFSRecord::~MonitoredFSRecord() {}

  path MonitoredFSRecord::get_file_path() const {
    return file_path_;
  }
  size_t MonitoredFSRecord::get_file_size() const {
    return file_size_;
  }
  string MonitoredFSRecord::get_file_hash() const {
    return file_hash_;
  }
  time_t MonitoredFSRecord::get_last_hash_update() const {
    return last_hash_update_;
  }

} // namespace beelzebase
