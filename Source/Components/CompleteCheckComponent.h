#ifndef LEVEL_COMPLETE_CHECK_H
#define LEVEL_COMPLETE_CHECK_H

#include "ActorComponent.h"

#include "../Communication/IEventData.h"

/*
    Listens to collision events targeting the owning actor to determine if a
    player touches this component. If a player-touch is registered an 
    'Event_StartLevel' is sent holding the next level's path.
*/
class CompleteCheckComponent : public ActorComponent
{
private:
    std::string m_NextLevelString; // holds the string path to the next level
public:
    CompleteCheckComponent();
    ~CompleteCheckComponent();

    // getters
    std::string GetNextLevelString();
    // setters
    void SetNextLevelString(std::string levelPath);

    // initializes the complete check component
    virtual bool VInit();
    // updates the complete check component
    virtual void VUpdate(float delta);

    // listens for post collision events to determine the owning actor-player collision
    void OnPostCollisionAdd(std::shared_ptr<IEventData> eventData);
};
#endif