#include <daemonarch_listener_mock.hpp>

#include <daemonarch_listener.hpp>

#include <iostream>

using namespace std;

namespace daemonarch::test::mock
{

  DaemonArchListenerMock::DaemonArchListenerMock(): DaemonArchListener() {}
  DaemonArchListenerMock::DaemonArchListenerMock(const on_event_callback_t& callback): DaemonArchListener(), callback_(callback) {}
  DaemonArchListenerMock::~DaemonArchListenerMock() {};


  void DaemonArchListenerMock::set_on_event_callback(const on_event_callback_t& callback) {
    callback_ = callback;
  }

  void DaemonArchListenerMock::on_event(const daemon_arch_event_t& evt) {
    if(callback_) {
      callback_(evt);
      return;
    }
    cout << "on_event called" << endl;
  }




} // namespace daemonarch::test::mock
