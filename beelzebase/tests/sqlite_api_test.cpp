
#include <sqlite/sqlite_api.hpp>

#include <gtest/gtest.h>

#include <memory>
#include <filesystem>

using namespace beelzebase;
using namespace std;
using namespace std::filesystem;

class SqliteApiTest : public testing::Test
{
  public:
    void SetUp() override;
    void TearDown() override;

  protected:
    path db_file;
    unique_ptr<ISQLApi> instance;
};

void SqliteApiTest::TearDown() {
  instance = nullptr;
  remove(db_file);
}
void SqliteApiTest::SetUp() {

  remove(db_file);

  db_file = temp_directory_path() / "beelzebase.db";
  instance = make_unique<SqliteAPI>(db_file);
}

TEST_F(SqliteApiTest, ctor_dtor)
{
  instance = nullptr;
}

TEST_F(SqliteApiTest, init_db) {
  ASSERT_TRUE(instance->init_db());
}


TEST_F(SqliteApiTest, update_db) {
  instance->init_db();
  ASSERT_TRUE(instance->update_db());
}