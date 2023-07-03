#ifndef ACTOR_FACTORY_H
#define ACTOR_FACTORY_H

#include "ActorComponentDefinitions.h"
#include "ActorComponent.h"
#include "Actor.h"

#include <string>
#include <map>

typedef ActorComponent *(*ActorComponentCreator)(void);
typedef std::map<std::string, ActorComponentCreator> actorComponentCreatorMap;

/*
    Has the ability to generate any type of Actor allowed in the game, returning a
    pointer to a more general abstract interface for each generated Actor; leaving 
    its type-specific implementation to calling code. 
    Different default components are attached to Actors with a specific given type.
    
    IDEA: extend ActorFactory's type w/ attached components completely defined
    in data. Allows artists/level-editors to define different types of Actors purely
    based on the combination of specific game components.
*/
class ActorFactory
{
private:
    unsigned int             m_lastActorID = 1;        // an incrementing ActorID counter
    actorComponentCreatorMap m_actorComponentCreators; // function list for creating components
public:
    ActorFactory();
    ~ActorFactory();

    // creates and returns an actor with default components as specified by its given type
    std::shared_ptr<Actor> CreateActor(DEFAULT_ACTOR_TYPES actorType);
private:
    // creates an actor component to be used in conjunction with an Actor
    std::shared_ptr<ActorComponent> createComponent(std::string component);
    // increments the ActorID counter and returns the subsequent ID
    unsigned int getNextActorID(void);
};
#endif