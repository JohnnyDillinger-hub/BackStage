#ifndef EVENT_POST_COLLISION_REMOVE_H
#define EVENT_POST_COLLISION_REMOVE_H

#include <Box2D/Box2D.h>

#include "../Communication/IEventData.h"

/*
    Fires when a collision is resolved.
*/
class Event_PostCollisionRemove : public IEventData
{
private:
    b2Contact* m_Contact;  // the collision contact of the collision
public:
    static const EventType s_EventType;
    Event_PostCollisionRemove(b2Contact* contact) : m_Contact(contact) { }

    // returns the type of event
    const EventType& GetEventType() { return s_EventType; }
    // returns the event name
    const std::string GetName() const { return "Event_PostCollisionRemove"; }
    // copies the event 
    std::shared_ptr<IEventData> Copy() const { return std::shared_ptr<IEventData>(new Event_PostCollisionRemove(m_Contact)); }

    // getters
    const b2Contact* GetContact() const { return m_Contact; }
};
#endif