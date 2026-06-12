#include <event_translate_tools.hpp>

#include <daemonarch_event.hpp>
#include <sys/inotify.h>

namespace daemonarch
{
  bool translate(const inotify_event& src, daemon_arch_event_t& dst) {

    if(src.mask & IN_MODIFY) {
      dst.event_type = MODIFY;
    }
    else if(src.mask & IN_CREATE) {
      dst.event_type = CREATE;
    }
    else if(src.mask & IN_DELETE) {
      dst.event_type = DELETE;
    }
    else {
      return false;
    }
    return true;
  }

} // namespace daemonarch
