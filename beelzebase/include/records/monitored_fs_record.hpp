#ifndef MONITORED_FS_RECORD_HPP
#define MONITORED_FS_RECORD_HPP

#include <filesystem>
#include <string>
#include <ctime>

namespace beelzebase
{

  class MonitoredFSRecord
  {
  public:
    MonitoredFSRecord(const std::filesystem::path&, const size_t& = 0, const std::string& = "", const time_t& = 0);
    virtual ~MonitoredFSRecord();

    std::filesystem::path get_file_path() const;
    size_t get_file_size() const;
    std::string get_file_hash() const;
    time_t get_last_hash_update() const;


  private:
    std::filesystem::path file_path_;
    size_t file_size_;
    std::string file_hash_;
    time_t last_hash_update_;
  };

} // namespace beelzebase

#endif // MONITORED_FS_RECORD_HPP