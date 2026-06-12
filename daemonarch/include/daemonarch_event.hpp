#ifndef DAEMONARCH_EVENT_HPP
#define DAEMONARCH_EVENT_HPP

#include <string>

namespace daemonarch
{

  enum daemon_arch_event_type_t
  {
    MODIFY,
    DELETE,
    CREATE,
    NOT_DEFINED
  };

  struct daemon_arch_event_t
  {
    std::string path;
    daemon_arch_event_type_t event_type;
  };

} // namespace daemonarch
#endif // DAEMONARCH_EVENT_HPP