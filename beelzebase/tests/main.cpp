#include <beelzebase.hpp>
#include <sqlite/sqlite_api.hpp>

#include <gtest/gtest.h>

#include <memory>
#include <filesystem>
#include <fstream>
#include <algorithm>

using namespace beelzebase;
using namespace std;
using namespace std::filesystem;

class BeelzebaseTest : public testing::Test
{
  public:
    void SetUp() override;
    void TearDown() override;

  protected:
    unique_ptr<Beelzebase> instance;
    path db_file;
};

void BeelzebaseTest::TearDown() {
  instance = nullptr;
  remove(db_file);
}

void BeelzebaseTest::SetUp() {

  remove(db_file);

  db_file = temp_directory_path() / "beelzebase.db";
  unique_ptr<ISQLApi> api{make_unique<SqliteAPI>(db_file)};
  instance = make_unique<Beelzebase>(std::move(api));
}

TEST_F(BeelzebaseTest, ctor_dtor)
{
  instance = nullptr;
}
