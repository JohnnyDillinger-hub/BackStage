#ifndef EVENT_POST_COLLISION_ADD_H
#define EVENT_POST_COLLISION_ADD_H

#include <Box2D/Box2D.h>

#include "../Communication/IEventData.h"

/*
    Fires when a collision occured.
*/
class Event_PostCollisionAdd : public IEventData
{
private:
    b2Contact* m_Contact; // the collision contact of the collision
public:
    static const EventType s_EventType;
    Event_PostCollisionAdd(b2Contact* contact) : m_Contact(contact) { }

    // returns the type of event
    const EventType& GetEventType() { return s_EventType; }
    // returns the event name
    const std::string GetName() const { return "Event_PostCollisionAdd"; }
    // copies the event 
    std::shared_ptr<IEventData> Copy() const { return std::shared_ptr<IEventData>(new Event_PostCollisionAdd(m_Contact)); }

    // getters
    const b2Contact* GetContact() const { return m_Contact; }
};
#endif