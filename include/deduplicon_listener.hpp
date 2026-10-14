#ifndef LISTENER_HPP
#define LISTENER_HPP

#include <daemonarch_listener.hpp>

namespace deduplicon {


  class DedupliconListener: public daemonarch::DaemonArchListener {

    public:
      DedupliconListener() {};
      virtual ~DedupliconListener() {};
      void on_event(const daemonarch::daemonarch_event_t &);

  };

}

#endif // LISTENER_HPP
