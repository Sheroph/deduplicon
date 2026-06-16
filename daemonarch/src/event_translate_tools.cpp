#include <event_translate_tools.hpp>

#include <daemonarch_event.hpp>
#include <sys/inotify.h>

#include <iostream>

using namespace std;

namespace daemonarch
{
  bool translate(const inotify_event& src, daemon_arch_event_type_t& dst) {

    if(src.mask & IN_MODIFY) {
      dst = MODIFY;
    }
    else if(src.mask & IN_CREATE) {
      dst = CREATE;
    }
    else if(src.mask & (IN_DELETE | IN_DELETE_SELF)) {
      dst = DELETE;
    }
    else if(src.mask & IN_CLOSE_WRITE) {
      dst = CLOSED;
    }
    else {
      cout << "Inotify mask (" << hex << src.mask << dec << ") is not handled yet " << endl;
      return false;
    }
    return true;
  }

} // namespace daemonarch
