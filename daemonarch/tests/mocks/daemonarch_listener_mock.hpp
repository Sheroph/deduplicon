#ifndef DEAMONARCH_LISTENER_MOCK_HPP
#define DEAMONARCH_LISTENER_MOCK_HPP

#include <daemonarch_listener.hpp>
#include <daemonarch_event.hpp>

#include <functional>
#include <future>
#include <list>


namespace daemonarch::test::mock
{

  class DaemonArchListenerMock : public DaemonArchListener
  {

    public:
    DaemonArchListenerMock();

    void on_event(const daemon_arch_event_t&) override;

    size_t get_on_event_called_count() const;

    std::future<void> wait_for_on_event_call_count(const size_t);

    std::vector<daemon_arch_event_t> get_on_event_call_params() const;

    protected:
      std::promise<void> wait_for_on_event_call_count_pro_;
      size_t expected_on_event_call_count_;
      bool expected_on_event_call_count_set_;

      std::vector<daemon_arch_event_t> on_event_call_params_;
  };

} // namespace daemonarch::test::mock
#endif // DEAMONARCH_LISTENER_MOCK_HPP