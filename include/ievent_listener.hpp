#ifndef IEVENT_LISTENER_HPP
#define IEVENT_LISTENER_HPP

namespace deduplicon
{

  class IEvent;

  class IEventListener
  {
  public:
    IEventListener() {}
    virtual ~IEventListener() {}

    virtual bool process_event(const IEvent &) = 0;
  };
} // namespace deduplicon

#endif // IEVENT_LISTENER_HPP