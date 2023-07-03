#ifndef EVENT_ACTOR_MOVED_H
#define EVENT_ACTOR_MOVED_H

#include <glm/glm.hpp>

#include "../Communication/IEventData.h"
#include "../Components/Actor.h"

/*
    Fires when an actor should be moved due to changes in the physics world.
*/
class Event_ActorMoved : public IEventData
{
private:
    ActorID   m_ActorID;     // the unique ID of the actor to be moved
    glm::vec2 m_NewPosition; // the new world-space position of the actor
    float     m_Rotation;    // the new world-space rotation of the actor
public:
    static const EventType s_EventType;
    Event_ActorMoved(ActorID actorID, glm::vec2 NewPos, float Rotation) : m_ActorID(actorID), m_NewPosition(NewPos), m_Rotation(Rotation) { }

    // returns the type of event
    virtual const EventType& GetEventType() { return s_EventType; }
    // returns the event name
    virtual const std::string GetName() const { return "Event_ActorMoved"; }
    // copies the event 
    virtual std::shared_ptr<IEventData> Copy() const { return std::shared_ptr<IEventData>(new Event_ActorMoved(m_ActorID, m_NewPosition, m_Rotation)); }

    // getters
    const ActorID   GetActorID()     const { return m_ActorID; }
    const glm::vec2 GetNewPosition() const { return m_NewPosition; }
    const float     GetNewRotation() const { return m_Rotation; }
};
#endif