#include <daemonarch.hpp>

#include <daemonarch_listener_mock.hpp>
#include <file_modifier.hpp>

#include <gtest/gtest.h>

#include <fstream>
#include <future>

using namespace daemonarch;
using namespace std;
using namespace std::filesystem;

constexpr char fake_file_name[]{"daemonarch_test.txt"};
constexpr char fake_data[]{"This is a test file."};
const size_t fake_data_size{strlen(fake_data)};

using namespace daemonarch::test::mock;
using namespace daemonarch::test::tools;

class DaemonArchTest : public testing::Test
{
  public:
    void SetUp() override;


  protected:
    unique_ptr<DaemonArch> instance;
    unique_ptr<DaemonArchListenerMock> listener_mock;
    unique_ptr<FileModifier> file_handler_;
    path temp_file;
};


void DaemonArchTest::SetUp() {

  if(exists(temp_file))
  {
    std::filesystem::remove(temp_file);
  }

  temp_file = temp_directory_path() / fake_file_name;
  file_handler_ = make_unique<FileModifier>(temp_file);
  file_handler_->write_bytes(fake_data, fake_data_size, ios::trunc);

  instance = make_unique<DaemonArch>();

  listener_mock = make_unique<DaemonArchListenerMock>();
}


TEST_F(DaemonArchTest, ctor_dtor)
{
  DaemonArch test;
}

TEST_F(DaemonArchTest, start_dtor)
{
  ASSERT_TRUE(instance->start());
}

TEST_F(DaemonArchTest, add_watch)
{
  instance->watch(temp_file, *listener_mock);
}


TEST_F(DaemonArchTest, modified_notif_open_close)
{
  ASSERT_TRUE(instance->watch(temp_file, *listener_mock) && instance->start());

  future wait_call{listener_mock->wait_for_on_event_call_count(1)};

  file_handler_->open_close();

  future_status status{wait_call.wait_for(200ms)};
  ASSERT_EQ(future_status::ready, status);

  ASSERT_EQ(1, listener_mock->get_on_event_called_count());
}
