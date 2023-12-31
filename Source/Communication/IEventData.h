#ifndef I_EVENT_DATA_H
#define I_EVENT_DATA_H

#include "FastDelegate.h"

#include <memory>
#include <string>

// don't use global enum of event types but use Global UID's attached to each specific event type
// this way there is no need to recompile a large array of files for every event type change
// {1E97F18B-B2EE-40C9-9A68-AE5B9481C914} 
// DEFINE_GUID(<<name>>, 
// 0x1e97f18b, 0xb2ee, 0x40c9, 0x9a, 0x68, 0xae, 0x5b, 0x94, 0x81, 0xc9, 0x14);
// Generated via: Tools -> Create GUID -> DEFINE ... -> Copy
typedef unsigned int EventType;
typedef unsigned int ActorID;
class IEventData;
typedef fastdelegate::FastDelegate1<std::shared_ptr<IEventData>> EventListenerDelegate;

/*
    Interface any event has to comply with specified throughout Lucid's EventManager.
*/
class IEventData
{
private:
    // default event state
    const float m_TimeStamp; // time in ms (since application launch) of when the event fired
public:
    IEventData(const float timestamp = 0.0) : m_TimeStamp(timestamp) { }
    ~IEventData() { }
    
    // returns the type of the event
    virtual const EventType& GetEventType() = 0;
    // returns the time the event was created
    virtual float GetTimeStamp() { return m_TimeStamp; }
    // copies the event including its event state
    virtual std::shared_ptr<IEventData> Copy() const = 0;
    // returns the name of the event
    virtual const std::string GetName() const = 0;
};
#endif