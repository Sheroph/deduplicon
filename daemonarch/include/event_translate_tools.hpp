#ifndef EVENT_TRANSLATE_TOOLS_HPP
#define EVENT_TRANSLATE_TOOLS_HPP

#include <daemonarch_event.hpp>

struct inotify_event;

namespace daemonarch
{
  bool translate(const inotify_event&, daemon_arch_event_type_t&);
} // namespace daemonarch

#endif // EVENT_TRANSLATE_TOOLS_HPP