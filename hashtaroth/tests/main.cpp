#include <hashtaroth.hpp>
#include <gtest/gtest.h>

#include <memory>
#include <filesystem>
#include <fstream>
#include <algorithm>

using namespace hashtaroth;
using namespace std;
using namespace std::filesystem;

constexpr char fake_file_name[]{"fake_file.avi"};

constexpr char fake_data[]{"efgrsdwesfojêrqgadzmlkjhlsfjbnslekjfbelskjbfljkbslfjbdlswj<bflks<jblfj<bl<sjbskldhbzqqmdinms"};
const size_t fake_data_size{strlen(fake_data)};

class HashtarothTest : public testing::Test
{
  public:
    void SetUp() override;

  protected:
    unique_ptr<Hashtaroth> instance;
    path temp_file;
    hash_job_t job;
};


void HashtarothTest::SetUp() {

  if(exists(temp_file))
  {
    std::filesystem::remove(temp_file);
  }

  temp_file = temp_directory_path() / fake_file_name;
  ofstream stream(temp_file, ios::out | ios::trunc | ios::binary);
  stream.write(fake_data, fake_data_size);
  stream.close();

  job.set_file_path(temp_file);
  instance = make_unique<Hashtaroth>();
}


TEST_F(HashtarothTest, ctor_dtor)
{
  Hashtaroth test;
}

TEST_F(HashtarothTest, start_dtor)
{
  instance->start();
}

TEST_F(HashtarothTest, push_job_not_started)
{
  instance->push_job(job);
}


TEST_F(HashtarothTest, hash_job)
{
  instance->start();
  hash_job_future_t job_future{instance->push_job(job)};
  hash_job_response_t response{job_future.get()};
  size_t null_bytes{0};
  for(size_t idx =0 ; idx < EVP_MAX_MD_SIZE; ++idx) {
    if(response.digest[idx] == 0) {
      ++null_bytes;
    }
  }
  ASSERT_NE(EVP_MAX_MD_SIZE, null_bytes);
}
