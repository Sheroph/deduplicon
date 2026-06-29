
#include <records/monitored_fs_record.hpp>

#include <gtest/gtest.h>

using namespace beelzebase;
using namespace std;
using namespace std::filesystem;

const path TEST_FILE_PATH("/var/data/sample/path.txt");

class MonitoredFSRecordTest : public testing::Test
{
  public:
    void SetUp() override;
    void TearDown() override;

  protected:
    unique_ptr<MonitoredFSRecord> instance;
};

void MonitoredFSRecordTest::TearDown() {
  instance = nullptr;
}
void MonitoredFSRecordTest::SetUp() {
  instance = make_unique<MonitoredFSRecord>(TEST_FILE_PATH);
}

TEST_F(MonitoredFSRecordTest, ctor_dtor)
{
  instance = nullptr;
}

TEST_F(MonitoredFSRecordTest, default_ctor) {
  ASSERT_EQ(TEST_FILE_PATH, instance->get_file_path());
  ASSERT_TRUE(instance->get_file_hash().empty());
  ASSERT_EQ(static_cast<size_t>(0), instance->get_file_size());
  ASSERT_EQ(static_cast<time_t>(0), instance->get_last_hash_update());
}
