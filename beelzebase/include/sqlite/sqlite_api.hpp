#ifndef SQLITE_API_HPP
#define SQLITE_API_HPP

#include <isql_api.hpp>

#include <sqlite3.h>

#include <filesystem>
#include <sstream>
#include <exception>

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

  private:
    sqlite3* db_;
    std::filesystem::path install_path_;
  };

  template<typename Record>
  bool bind_sqlite3_param(sqlite3_stmt**, sqlite3*, const Record& record) {
    std::stringstream stream;
    stream << "This template function is not specialized for " << typeid(record).name() << std::endl;
    throw std::runtime_error(stream.str());
  }
} // namespace beelzebase

#endif // SQLITE_API_HPP