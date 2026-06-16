#include <daemonarch_listener_mock.hpp>

#include <iostream>

using namespace std;

namespace daemonarch::test::mock
{

  DaemonArchListenerMock::DaemonArchListenerMock(): DaemonArchListener() {
    expected_on_event_call_count_set_ = false;
    expected_on_event_call_count_ = 0;
  }

  void DaemonArchListenerMock::on_event(const daemon_arch_event_t& evt) {
    on_event_call_params_.push_back(evt);
    if(expected_on_event_call_count_set_ && on_event_call_params_.size() >= expected_on_event_call_count_) {
      wait_for_on_event_call_count_pro_.set_value();
    }
  }

  size_t DaemonArchListenerMock::get_on_event_called_count() const {
    return on_event_call_params_.size();
  }


  future<void> DaemonArchListenerMock::wait_for_on_event_call_count(const size_t nb_calls) {
    expected_on_event_call_count_ = nb_calls;
    expected_on_event_call_count_set_ = true;
    return wait_for_on_event_call_count_pro_.get_future();
  }

  vector<daemon_arch_event_t> DaemonArchListenerMock::get_on_event_call_params() const {
    return on_event_call_params_;
  }

} // namespace daemonarch::test::mock
