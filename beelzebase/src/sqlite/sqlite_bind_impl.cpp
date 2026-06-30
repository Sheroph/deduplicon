#include <sqlite/sqlite_api.hpp>
#include <records/monitored_fs_record.hpp>

#include <iostream>

using namespace std;

namespace beelzebase
{

  static void no_op(void*) {}


  static bool bind_record(sqlite3_stmt* stmt, sqlite3* db, const MonitoredFSRecord& record) {

    if(sqlite3_bind_text(stmt, 1, record.get_file_path().c_str(), -1, no_op) != SQLITE_OK) {
      cerr << "Failed to bind file path value for insert statment, error :\n\t" << sqlite3_errmsg(db) << endl;
      return false;
    }

    if(sqlite3_bind_int64(stmt, 2, record.get_file_size()) != SQLITE_OK) {
      cerr << "Failed to bind file size value for insert statment, error :\n\t" << sqlite3_errmsg(db) << endl;
      return false;
    }

    if(sqlite3_bind_text(stmt, 3, record.get_file_hash().c_str(), -1, no_op) != SQLITE_OK) {
      cerr << "Failed to bind file hash value for insert statment, error :\n\t" << sqlite3_errmsg(db) << endl;
      return false;
    }

    if(sqlite3_bind_int64(stmt, 4, record.get_last_hash_update()) != SQLITE_OK) {
      cerr << "Failed to bind last hash update value for insert statment, error :\n\t" << sqlite3_errmsg(db) << endl;
      return false;
    }

    return true;
  }

  template<>
  bool prepare_insert(sqlite3_stmt** stmt, sqlite3* db, const MonitoredFSRecord& record) {

    const std::string stmt_str{"INSERT INTO monitored_fs (file_path, file_size, file_hash, last_hash_update) \
      VALUES (:file_path, :file_size, :file_hash, :last_hash_update)"};


    if(sqlite3_prepare_v2(db, stmt_str.c_str(), -1, stmt, nullptr) != SQLITE_OK) {
      cerr << "Failed to prepare insert statment of fs monitored record, error :\n\t " << sqlite3_errmsg(db) << endl;
      return false;
    }

    return bind_record(*stmt, db, record);
  }


  template<>
  bool prepare_update(sqlite3_stmt** stmt, sqlite3* db, const string& previous_path, const MonitoredFSRecord& record) {
    const string stmt_str{"UPDATE monitored_fs SET file_path = :file_path, \
                                                   file_size = :file_size, \
                                                   file_hash = :file_hash, \
                                                   last_hash_update = :last_hash_update \
                            WHERE file_path = :previous_file_path"};
    if(sqlite3_prepare_v2(db, stmt_str.c_str(), -1, stmt, nullptr) != SQLITE_OK) {
      cerr << "Failed to prepare update statment of fs monitored record, error :\n\t" << sqlite3_errmsg(db) << endl;
      return false;
    }


    if(!bind_record(*stmt, db, record)) {
      return false;
    }

    if(sqlite3_bind_text(*stmt, 5, previous_path.c_str(), -1, no_op) != SQLITE_OK) {
      cerr << "Failed to bind previous file path value for update statment, error :\n\t" << sqlite3_errmsg(db) << endl;
      return false;
    }

    return true;
  }


  bool prepare_delete(sqlite3_stmt** stmt, sqlite3* db, const std::string& file_path) {

    const string stmt_str{"DELETE FROM monitored_fs WHERE file_path = :file_path"};

    if(sqlite3_prepare_v2(db, stmt_str.c_str(), -1, stmt, nullptr) != SQLITE_OK) {
      cerr << "Failed to prepare delete statment of fs monitored record, error :\n\t" << sqlite3_errmsg(db) << endl;
      return false;
    }

    if(sqlite3_bind_text(*stmt, 1, file_path.c_str(), -1, no_op) != SQLITE_OK) {
      cerr << "Failed to bind file path value for delete statment, error :\n\t" << sqlite3_errmsg(db) << endl;
      return false;
    }
    return true;
  }
} // namespace beelzebase
