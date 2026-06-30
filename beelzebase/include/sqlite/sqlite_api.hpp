#ifndef SQLITE_API_HPP
#define SQLITE_API_HPP

#include <isql_api.hpp>

#include <sqlite3.h>

#include <filesystem>
#include <sstream>
#include <exception>
#include <string>

namespace beelzebase
{

  class MonitoredFSRecord;

  class SqliteAPI: public ISQLApi
  {
  public:
    SqliteAPI(const std::filesystem::path&);
    virtual ~SqliteAPI();

    bool init_db() override;
    bool update_db() override;


    bool add_monitored_entry(const MonitoredFSRecord&) override;
    bool update_monitored_entry(const std::string&, const MonitoredFSRecord&) override;
    bool delete_monitored_entry(const std::string&) override;

  private:
    sqlite3* db_;
    std::filesystem::path install_path_;
  };

  template<typename Record>
  bool prepare_insert(sqlite3_stmt**, sqlite3*, const Record& record) {
    std::stringstream stream;
    stream << "This insert template function is not specialized for " << typeid(record).name() << std::endl;
    throw std::runtime_error(stream.str());
  }


  template<typename Record>
  bool prepare_update(sqlite3_stmt**, sqlite3*, const std::string&, const Record& record) {
    std::stringstream stream;
    stream << "This udpate template function is not specialized for " << typeid(record).name() << std::endl;
    throw std::runtime_error(stream.str());
  }

  bool prepare_delete(sqlite3_stmt**, sqlite3*, const std::string&);
} // namespace beelzebase

#endif // SQLITE_API_HPP