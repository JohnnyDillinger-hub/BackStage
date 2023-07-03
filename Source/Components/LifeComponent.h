#ifndef LIFE_COMPONENT_H
#define LIFE_COMPONENT_H

#include "ActorComponent.h"

/*
    Specifies an actor to have a given amount of Life. This also states that 
    the actor can die after which it will be removed from the game. 
*/
class LifeComponent : public ActorComponent
{
private:
    int m_CurrentHealth; // the current amount of health points the actor has
    int m_MaxHealth;     // the maximum number of health points the actor is allowed to have
public:
    LifeComponent();
    ~LifeComponent();

    // getters
    int GetCurrentHealth();
    int GetMaxHealth();
    // setters
    void SetCurrentHealth(int health);
    void SetMaxHealth(int health);
    
    // initializes the life component
    bool VInit();
    // updates the life component
    void VUpdate(float deltaTime);

    // heals the actor by a given amount (to a maximum of m_MaxHealth)
    void Heal(int amount);
    // damages the actor by a given amount. If the health points reach below zero a 'Event_DestroyActor' is sent
    void Damage(int amount);
};
#endif