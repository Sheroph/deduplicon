#include <daemonarch.hpp>

#include <daemonarch_listener.hpp>
#include <daemonarch_event.hpp>
#include <event_translate_tools.hpp>

#include <sys/inotify.h>
#include <unistd.h>

#include <exception>
#include <sstream>
#include <cerrno>
#include <cstring>
#include <poll.h>
#include <iostream>

using namespace std;
using namespace std::filesystem;

ostream &operator<<(ostream &out, const inotify_event &evt)
{
  out << "inotify event" << endl;
  out << "\tevt.cookie : " << evt.cookie << endl;
  out << "\tevt.mask : " << hex << evt.mask << dec << endl;
  if(evt.len) {
    out << "\tevt.len : " << evt.len << endl;
    out << "\tevt.name : " << evt.name << endl;
  }
  out << "\tevt.wd : " << hex << evt.wd << dec << endl;

  return out;
}

namespace daemonarch
{

  DaemonArch::DaemonArch() {
    listener_running_ = false;
    inotify_fd_ = -1;
  }

  DaemonArch::~DaemonArch() {

    const bool was_running = listener_running_;
    listener_running_ = false;

    if(was_running)
    {
      close(inotify_fd_);
      inotify_listener_.join();
    }

    else if(inotify_fd_ != -1) {
      close(inotify_fd_);
    }

  }

  bool DaemonArch::watch(const path& path, DaemonArchListener& listener) {

    scoped_lock<mutex> lock(watched_map_mtx_);

    if(!init_inotify())
    {
      return false;
    }

    const int flags = IN_CLOSE_WRITE |
                      IN_CREATE |
                      IN_DELETE |
                      IN_DELETE_SELF |
                      IN_MODIFY |
                      IN_MOVE_SELF |
                      IN_MOVE;

    const int fd = inotify_add_watch(inotify_fd_, path.c_str(), flags);
    if (fd == -1) {
      cerr << "Failed to intialize watcher on " << path.c_str() << " error : " << strerror(errno) << endl;
      return false;
    }

    watched_path_.insert({fd, path});
    listeners_.insert({fd, listener});

    return true;
  }

  bool DaemonArch::start()
  {
    if(listener_running_)
    {
      return true;
    }
    if(!init_inotify())
    {
      return false;
    }

    inotify_listener_ = std::move(thread(&DaemonArch::run, this));
    do{
      this_thread::sleep_for(chrono::milliseconds(10));
    }
    while(!listener_running_);
    return true;
  }


  bool DaemonArch::inotify_initialized() const
  {
    return inotify_fd_ != -1;
  }

  bool DaemonArch::init_inotify()
  {
    if(inotify_initialized())
    {
      return true;
    }

    inotify_fd_ = inotify_init();
    if(!inotify_initialized()) {
      cerr << "Failed to initialize inotify, error : " << strerror(errno) << endl;
    }
    return inotify_initialized();
  }

  void DaemonArch::run()
  {
    listener_running_ = true;
    struct inotify_event os_event;

    pollfd pfd;
    pfd.fd = inotify_fd_;
    pfd.events = POLLIN;

    while(listener_running_)
    {
      const int poll_out{poll(&pfd, 1, 100)};
      if(poll_out <= 0 || (pfd.revents & POLLNVAL))
      {
        if((pfd.revents & POLLNVAL) && listener_running_){
          cerr << "Error on poll call not related on inotify closure." << endl;
        }
        continue;
      }
      ssize_t bytes_read{0};
      while (bytes_read < sizeof(os_event))
      {
        const ssize_t last_bytes_read{read(inotify_fd_, &os_event, sizeof(os_event))};
        if(last_bytes_read < 0){
          cerr << "Failure while reading inotify event. Start a new event read." << endl;
          bytes_read = 0;
          break;
        }
        if(!listener_running_){
          break;
        }
        bytes_read+=last_bytes_read;
      }
      if(bytes_read > 0)
      {
        daemon_arch_event_t event;
        if(translate(os_event, event.event_type)) {
          event.path = watched_path_.at(os_event.wd);
          listeners_.at(os_event.wd).on_event(event);
        }

      }
    }
  }
} // namespace daemonarch
