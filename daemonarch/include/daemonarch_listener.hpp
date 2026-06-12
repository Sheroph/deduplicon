#ifndef DAEMONARCH_LISTENER_HPP
#define DAEMONARCH_LISTENER_HPP

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

  class DaemonArchListener
  {

  public:
    DaemonArchListener() {};
    virtual ~DaemonArchListener() {};
    virtual void on_event(const daemon_arch_event_t &) = 0;
  };

} // namespace daemonarch

#endif // DAEMONARCH_LISTENER_HPP