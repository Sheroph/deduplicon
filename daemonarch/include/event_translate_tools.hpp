#ifndef EVENT_TRANSLATE_TOOLS_HPP
#define EVENT_TRANSLATE_TOOLS_HPP


struct inotify_event;

namespace daemonarch
{
  struct daemon_arch_event_t;

  bool translate(const inotify_event&, daemon_arch_event_t&);

} // namespace daemonarch

#endif // EVENT_TRANSLATE_TOOLS_HPP