#ifndef LIGHT_SWITCH_COMPONENT_H
#define LIGHT_SWITCH_COMPONENT_H

#include "ActorComponent.h"
#include "Event_LightStateSwitched.h"

/*
    Allows the owning actor to change its rendering light state and properly informs all
    relevant sub-systems that its light state has changed.
*/
class LightSwitchComponent : public ActorComponent
{
private:
    LightState m_LightState;  // the current state of light the actor has enabled    
    bool       m_Initialized; // disable the light the first update run (light is off by default)
public:
    LightSwitchComponent();
    ~LightSwitchComponent();

    // initializes the light switch component
    bool VInit();
    // updates the light switch component
    void VUpdate(float deltaTime);
};
#endif