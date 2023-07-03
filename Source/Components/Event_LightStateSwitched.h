#ifndef EVENT_LIGHT_STATE_SWITCHED_H
#define EVENT_LIGHT_STATE_SWITCHED_H

#include "../Communication/IEventData.h"

/*
    Represents the different states of (colored) light sources/blocks
*/
enum LightState
{
    OFF,
    WHITE,
    RED,
    GREEN,
    BLUE
};

/*
    Fires whenever the state of light of an actor has changed. 
*/
class Event_LightStateSwitched : public IEventData
{
private:
    LightState m_LightState; // the state the actor's light is currently in
public:
    static const EventType s_EventType;
    Event_LightStateSwitched(LightState lightState) : m_LightState(lightState) { }

    // returns the type of event
    const EventType& GetEventType() { return s_EventType; }
    // returns the event name
    const std::string GetName() const { return "Event_LightStateSwitched"; }
    // copies the event 
    std::shared_ptr<IEventData> Copy() const { return std::shared_ptr<IEventData>(new Event_LightStateSwitched(m_LightState)); }
    // returns the current state of the light
    const LightState GetLightState() const { return m_LightState; }
};
#endif