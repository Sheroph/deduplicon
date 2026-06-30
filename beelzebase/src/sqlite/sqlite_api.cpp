#include <sqlite/sqlite_api.hpp>

#include <records/monitored_fs_record.hpp>

#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

using namespace std;
using namespace std::filesystem;

namespace beelzebase
{
  SqliteAPI::SqliteAPI(const path &db_file) : db_(nullptr)
  {

    const char *root_dir{getenv("BEELZEBASE_ROOT")};
    if (!root_dir)
    {
      const string msg{"BEELZEBASE_ROOT is not defined."};
      cerr << msg << endl;
      throw runtime_error(msg);
    }
    install_path_ = root_dir;
    if (!(is_directory(install_path_) && exists(install_path_)))
    {
      const string msg{"BEELZEBASE_ROOT doesn't point to valid directory."};
      cerr << msg << endl;
      throw runtime_error(msg);
    }

    if (!exists(db_file.parent_path()) && !create_directories(db_file.parent_path()))
    {
      stringstream stream;
      stream << "Failed to create database at " << db_file;
      cerr << stream.str() << endl;
      throw runtime_error(stream.str());
    }

    if (sqlite3_open(db_file.c_str(), &db_) != SQLITE_OK)
    {
      stringstream stream;
      stream << "Failed to open database at " << db_file;
      cerr << stream.str() << endl;
      throw runtime_error(stream.str());
    }
  }

  SqliteAPI::~SqliteAPI()
  {
    if (db_)
    {
      sqlite3_close(db_);
    }
    db_ = nullptr;
  }

  bool SqliteAPI::init_db()
  {
    if (!db_)
    {
      cerr << "Can't initialize database, create it before." << endl;
      return false;
    }

    const path sql_script_path{install_path_ / "sql" / "database_v1.0.sql"};
    if(!exists(sql_script_path) || !is_regular_file(sql_script_path)) {
      cerr << "sql script file " << sql_script_path << " doesn't exist or is not a file" << endl;
      return false;
    }
    ifstream sql_file_stream(sql_script_path);
    ostringstream sql_stream;
    sql_stream << sql_file_stream.rdbuf();

    char *sql_error{nullptr};
    bool success{sqlite3_exec(db_, sql_stream.str().c_str(), nullptr, nullptr, &sql_error) == SQLITE_OK};
    if (!success)
    {
      stringstream stream;
      stream << "SQL init failed : " << sqlite3_errmsg(db_) << " " << sql_error;
      cerr << stream.str() << endl;
      sqlite3_free(sql_error);
      throw runtime_error(stream.str());
    }

    return success && update_db();
  }

  bool SqliteAPI::update_db()
  {
    return true;
  }

  bool SqliteAPI::add_monitored_entry(const MonitoredFSRecord &record)
  {
    sqlite3_stmt *stmt{nullptr};
    if (!prepare_insert(&stmt, db_, record))
    {
      return false;
    }

    if(sqlite3_step(stmt) != SQLITE_DONE) {
      cerr << "Failed to execute insert statment with error :\n\t" << sqlite3_errmsg(db_) << endl;
      return false;
    }
    sqlite3_reset(stmt);
    return true;
  }

  bool SqliteAPI::update_monitored_entry(const string& previous_file_path, const MonitoredFSRecord& record) {
    sqlite3_stmt *stmt{nullptr};

    if(!prepare_update(&stmt, db_, previous_file_path, record)) {
      return false;
    }

    if(sqlite3_step(stmt) != SQLITE_DONE) {
      cerr << "Failed to execute update statment with error :\n\t" << sqlite3_errmsg(db_) << endl;
      return false;
    }
    sqlite3_reset(stmt);
    return true;
  }

  bool SqliteAPI::delete_monitored_entry(const string& file_path) {
    sqlite3_stmt *stmt{nullptr};

    if(!prepare_delete(&stmt, db_, file_path)) {
      return false;
    }
    if(sqlite3_step(stmt) != SQLITE_DONE) {
      cerr << "Failed to execute delete statment with error :\n\t" << sqlite3_errmsg(db_) << endl;
      return false;
    }
    sqlite3_reset(stmt);
    return true;
  }

  extern bool prepare_delete(sqlite3_stmt**, sqlite3*, const std::string&);
  extern template bool prepare_insert(sqlite3_stmt **, sqlite3 *, const MonitoredFSRecord &);
  extern template bool prepare_update(sqlite3_stmt **, sqlite3 *, const string &, const MonitoredFSRecord &);

} // namespace beelzebase
