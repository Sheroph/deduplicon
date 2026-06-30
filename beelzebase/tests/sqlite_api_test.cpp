
#include <sqlite/sqlite_api.hpp>
#include <records/monitored_fs_record.hpp>

#include <gtest/gtest.h>

#include <memory>
#include <filesystem>

using namespace beelzebase;
using namespace std;
using namespace std::filesystem;

const path MONITORED_FILE_SAMPLE{"/this/is/a/monitored/file"};

class SqliteApiTest : public testing::Test
{
  public:
    SqliteApiTest() : testing::Test(), record(MONITORED_FILE_SAMPLE) {}
    virtual ~SqliteApiTest() {}

    void SetUp() override;
    void TearDown() override;

  protected:
    path db_file;
    unique_ptr<ISQLApi> instance;

    MonitoredFSRecord record;
};

void SqliteApiTest::TearDown() {
  instance = nullptr;
  remove(db_file);
}
void SqliteApiTest::SetUp() {

  remove(db_file);
  db_file = temp_directory_path() / "beelzebase.db";
  instance = make_unique<SqliteAPI>(db_file);
  instance->init_db();

  record = MonitoredFSRecord(MONITORED_FILE_SAMPLE);
}

TEST_F(SqliteApiTest, ctor_dtor)
{
  instance = nullptr;
}


TEST_F(SqliteApiTest, update_db) {
  ASSERT_TRUE(instance->update_db());
}

TEST_F(SqliteApiTest, init_db) {
  ASSERT_TRUE(instance->init_db());
}

TEST_F(SqliteApiTest, insert_record) {
  ASSERT_TRUE(instance->add_monitored_entry(record));
}

TEST_F(SqliteApiTest, insert_record_twice) {
  instance->add_monitored_entry(record);
  ASSERT_FALSE(instance->add_monitored_entry(record));
}

TEST_F(SqliteApiTest, delete_record) {
  instance->add_monitored_entry(record);
  ASSERT_TRUE(instance->delete_monitored_entry(MONITORED_FILE_SAMPLE));
}

TEST_F(SqliteApiTest, update_record) {
  instance->add_monitored_entry(record);
  record = MonitoredFSRecord(MONITORED_FILE_SAMPLE, 10);
  ASSERT_TRUE(instance->update_monitored_entry(MONITORED_FILE_SAMPLE, record));
}