#ifndef DAEMONARCH_EVENT_HPP
#define DAEMONARCH_EVENT_HPP

#include <string>

namespace daemonarch
{

  enum daemonarch_event_type_t
  {
    CLOSED,
    MODIFY,
    DELETE,
    CREATE,
    NOT_DEFINED
  };

  struct daemonarch_event_t
  {
    std::string path;
    daemonarch_event_type_t event_type;
  };

} // namespace daemonarch
#endif // DAEMONARCH_EVENT_HPP