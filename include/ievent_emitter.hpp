#ifndef IEVENTEMITTER_HPP
#define IEVENTEMITTER_HPP

namespace deduplicon
{

  class IEvent;

  class IEventEmitter
  {
  public:
    IEventEmitter() {}
    virtual ~IEventEmitter() {}

    virtual void emit_event(const IEvent &) = 0;
  };

} // namespace deduplicon

#endif // IEVENTEMITTER_HPP