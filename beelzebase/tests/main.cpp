#include <beelzebase.hpp>
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

  protected:
    unique_ptr<Beelzebase> instance;
};


void BeelzebaseTest::SetUp() {
  instance = make_unique<Beelzebase>();
}


TEST_F(BeelzebaseTest, ctor_dtor)
{
  Beelzebase test;
}