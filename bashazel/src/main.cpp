#include <commands.hpp>
#include <command_parser.hpp>

#include <string>
#include <iostream>

using namespace std;
using namespace bashazel;

bool main_loop()
{

  string command_line;

  cout << "bashazel > ";
  cin >> command_line;

  const command_t command{parse_command(command_line)};

  switch(command.type) {
    case QUIT:
      return false;
    case START:
      start();
      break;
    case STOP:
      stop();
      break;
    case UNKNOWN:
      cout << "Unknown command : " << command_line << endl;
    default:
      cout << usage() << endl;
  }
  return true;
}

int main()
{

  while (main_loop())
    ;
}
