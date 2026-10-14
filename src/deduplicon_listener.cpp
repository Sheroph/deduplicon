#include <deduplicon_listener.hpp>
#include <daemonarch_event.hpp>

#include <iostream>

using namespace daemonarch;
using namespace std;

namespace deduplicon {

  void DedupliconListener::on_event(const daemonarch_event_t &event) {
    cout << event << endl;
  }
}
