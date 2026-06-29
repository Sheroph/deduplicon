#include <sqlite/sqlite_api.hpp>
#include <records/monitored_fs_record.hpp>

#include <iostream>

using namespace std;

namespace beelzebase
{

  static void no_op(void*) {}

  template<>
  bool bind_sqlite3_param(sqlite3_stmt** stmt, sqlite3* db, const MonitoredFSRecord& record) {

    const std::string stmt_str{"INSERT INTO monitored_fs file_path, file_size, file_hash, last_hash_update \
      VALUES (:file_path, :file_size, :file_hash, :last_hash_update)"};


    if(sqlite3_prepare_v2(db, stmt_str.c_str(), -1, stmt, nullptr) != SQLITE_OK) {
      cerr << "Failed to prepare insert statment of fs monitored record"<< endl;
      return false;
    }

    if(sqlite3_bind_text(*stmt, 1, record.get_file_path().c_str(), -1, no_op) != SQLITE_OK) {
      cerr << "Failed to bind file path value" << endl;
      return false;
    }

    if(sqlite3_bind_int64(*stmt, 2, record.get_file_size()) != SQLITE_OK) {
      cerr << "Failed to bind file size value" << endl;
      return false;
    }

    if(sqlite3_bind_text(*stmt, 3, record.get_file_hash().c_str(), -1, no_op) != SQLITE_OK) {
      cerr << "Failed to bind file hash value" << endl;
      return false;
    }

    if(sqlite3_bind_int64(*stmt, 4, record.get_last_hash_update()) != SQLITE_OK) {
      cerr << "Failed to bind last hash update value" << endl;
      return false;
    }

    return true;
  }


} // namespace beelzebase
