#include <daemonarch.hpp>

#include <daemonarch_listener_mock.hpp>

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

class DaemonArchTest : public testing::Test
{
  public:
    void SetUp() override;

    future<void> write_in_temp_file(const ios::openmode& open_mode)
    {
      return async([&] ()
      {
        this_thread::sleep_for(chrono::milliseconds(50));
        ofstream stream(temp_file, open_mode);
        stream.close(); 
      });
    }

  protected:
    unique_ptr<DaemonArch> instance;
    unique_ptr<DaemonArchListener> listener_mock;
    path temp_file;
};


void DaemonArchTest::SetUp() {
  
  if(exists(temp_file))
  {
    std::filesystem::remove(temp_file);
  }
  
  temp_file = temp_directory_path() / fake_file_name;
  ofstream stream(temp_file, ios::out | ios::trunc | ios::binary);
  stream.write(fake_data, fake_data_size);
  stream.close();
  
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


TEST_F(DaemonArchTest, modified_notif)
{
  
  promise<bool> on_event_called_promise;
  future<bool> on_event_called_future{on_event_called_promise.get_future()};

  const on_event_callback_t callback{[&](const daemon_arch_event_t& evt) {
    on_event_called_promise.set_value(true);
  }};

  dynamic_cast<DaemonArchListenerMock*>(listener_mock.get())->set_on_event_callback(callback);

  ASSERT_TRUE(instance->watch(temp_file, *listener_mock));

  ASSERT_TRUE(instance->start());

  future write{write_in_temp_file(ios::app)};

  const future_status status{on_event_called_future.wait_for(chrono::milliseconds(1000))};

  write.get();
  ASSERT_TRUE(status == future_status::ready);
  ASSERT_TRUE(on_event_called_future.get());
}
