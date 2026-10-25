#include <commands.hpp>
#include <iostream>

using namespace std;

namespace bashazel
{
  string usage() {
    return "Usage: bashazel COMMAND\n\
COMMAND:\n\
    start: start deduplicon daemon\n\
    stop: stop deduplicon daemon\n\
    quit: quit bashazel cli";
  }

  void start() {
    cout << "Starting..." << endl;
  }

  void stop() {
    cout << "Stopping..." << endl;
  }

  bool add_monitored_item();
  bool remove_monitored_item();

  vector<string> list_monitored_items();

  void report() {}
  void status() {}
} // namespace bashazel
