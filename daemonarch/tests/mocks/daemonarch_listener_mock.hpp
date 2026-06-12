#ifndef DEAMONARCH_LISTENER_MOCK_HPP
#define DEAMONARCH_LISTENER_MOCK_HPP

#include <daemonarch_listener.hpp>

#include <functional>

namespace daemonarch::test::mock
{ 

  typedef std::function<void (const daemon_arch_event_t&)> on_event_callback_t ;

  class DaemonArchListenerMock : public DaemonArchListener
  {
    
    public:
    DaemonArchListenerMock();
    DaemonArchListenerMock(const on_event_callback_t&);
    ~DaemonArchListenerMock();

    void set_on_event_callback(const on_event_callback_t&);
    
    void on_event(const daemon_arch_event_t&) override;

    protected:
      on_event_callback_t callback_;
  };
  
} // namespace daemonarch::test::mock
#endif // DEAMONARCH_LISTENER_MOCK_HPP