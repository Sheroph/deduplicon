#ifndef DAEMONARCH_LISTENER_HPP
#define DAEMONARCH_LISTENER_HPP

namespace daemonarch
{

  struct daemonarch_event_t;

  class DaemonArchListener
  {

  public:
    DaemonArchListener() {};
    virtual ~DaemonArchListener() {};
    virtual void on_event(const daemonarch_event_t &) = 0;
  };

} // namespace daemonarch

#endif // DAEMONARCH_LISTENER_HPP