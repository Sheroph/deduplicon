#ifndef DAEMONARCH_HPP
#define DAEMONARCH_HPP

#include <filesystem>
#include <map>
#include <thread>
#include <mutex>
#include <atomic>

namespace daemonarch
{

  class DaemonArchListener;

  using watched_path_map = std::map<int, std::filesystem::path>;
  using listener_map = std::map<int, DaemonArchListener&>;

  class DaemonArch
  {

    public:

    DaemonArch();
    ~DaemonArch();

    bool watch(const std::filesystem::path&, DaemonArchListener& listener);
    bool start();

    private:

    bool inotify_initialized() const;

    bool init_inotify();

    void run();

    int inotify_fd_;

    watched_path_map watched_path_;
    listener_map listeners_;

    std::mutex watched_map_mtx_;

    std::atomic_bool listener_running_;
    std::thread inotify_listener_;

  };

} // namespace daemonarch

#endif // DAEMONARCH_HPP
