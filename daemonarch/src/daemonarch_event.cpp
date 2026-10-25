#include <daemonarch_event.hpp>

#include <ostream>

using namespace std;

ostream& operator<<(ostream& out, const daemonarch::daemonarch_event_t& event) {
  return out << "event  : path " << event.path << " type : " << event.event_type;
}

ostream& operator<<(ostream& out, const daemonarch::daemonarch_event_type_t& type) {

  switch (type)
  {
    case daemonarch::CLOSED:
      return out << "CLOSED";

    case daemonarch::MODIFY:
      return out << "MODIFY";

    case daemonarch::DELETE:
      return out << "DELETE";

    case daemonarch::CREATE:
      return out << "CREATE";

    case daemonarch::NOT_DEFINED:
    default:
      return out << "NOT_DEFINED";
  }
}
