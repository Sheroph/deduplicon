#include <command_parser.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace bashazel;

class BashazelTest : public testing::Test
{
};

TEST_F(BashazelTest, parse_forwarded_cmd)
{
  command_t command = parse_command("start");
  EXPECT_EQ(static_cast<size_t>(0), command.parameters.size());

  command = parse_command("start");
  EXPECT_EQ(static_cast<size_t>(0), command.parameters.size());
}

TEST_F(BashazelTest, parse_start)
{
  command_t command = parse_command("start");
  EXPECT_EQ(START, command.type);
}

TEST_F(BashazelTest, parse_stop)
{
  command_t command = parse_command("stop");
  EXPECT_EQ(STOP, command.type);
}

TEST_F(BashazelTest, parse_quit)
{
  command_t command = parse_command("quit");
  EXPECT_EQ(QUIT, command.type);
}

TEST_F(BashazelTest, parse_add_monitored_item)
{
  const string path{"/path/to/monitored"};
  command_t command = parse_command("add_monitored_item " + path);
  EXPECT_EQ(ADD_MONITORED_ITEM, command.type);
  EXPECT_EQ(static_cast<size_t>(1), command.parameters.size());
  EXPECT_EQ(path, command.parameters[0]);
}

TEST_F(BashazelTest, parse_add_monitored_item_error)
{
  command_t command = parse_command("add_monitored_item");
  EXPECT_EQ(UNKNOWN, command.type);
  EXPECT_EQ(static_cast<size_t>(0), command.parameters.size());
}
