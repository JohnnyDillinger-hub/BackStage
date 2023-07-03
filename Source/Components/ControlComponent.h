#ifndef CONTROL_COMPONENT_H
#define CONTROL_COMPONENT_H

#include "ActorComponent.h"
#include "Event_DestroyActor.h"

/*
    Any actor with a control component attached is controlled via user input. 
*/
class ControlComponent : public ActorComponent
{
private:
    float m_Velocity;  // the maximum velocity of movement
    bool  m_IsJumping; // states whether the actor is currently jumping
    bool  m_OnGround;  // states whether the actor is currently on the ground

    int m_NrGroundCollisionsAdd;    // the number of collision events of the owning actor with the ground
    int m_NrGroundCollisionsRemove; // the number of collision removed events between the actor and the ground
public:
    ControlComponent();
    ~ControlComponent();

    // setter
    void SetVelocity(float velocity);

    // initializes the control component
    bool VInit();
    // updates the control component, reading user input and reacting accordingly
    void VUpdate(float deltaTime);
    // determines ground collisions between actor and environment
    void PostCollisionAdd(std::shared_ptr<IEventData> eventData);
};
#endif