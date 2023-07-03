#include "Actor.h"

Actor::Actor() :  m_Position(0.0), m_Scale(1.0), m_Depth(0)
{

}

Actor::~Actor(void)
{

}

void Actor::Destroy(void)
{
    m_components.clear();
}

void Actor::Update(float deltaTime)
{
    ActorComponents::iterator it = m_components.begin();
    while (it != m_components.end())
        (it++)->second->VUpdate(deltaTime);
}

// NOTE(Joey): See header note
//template<class ComponentType> std::weak_ptr<ComponentType> Actor::GetComponent(std::string type);

void Actor::addComponent(std::shared_ptr<ActorComponent> component)
{
    m_components[component->m_Type] = component;
}

void Actor::setID(ActorID ID)
{
    m_id = ID;
}