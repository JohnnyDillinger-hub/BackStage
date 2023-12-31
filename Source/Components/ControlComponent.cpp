#include "ControlComponent.h"

#define GLEW_STATIC
#include <GL/glew.h> // required to link GL before linking GLFW
#include <glfw/glfw3.h>

#include "../Application/GameApplication.h" 
#include "../Communication/EventManager.h"
#include "../Physics/Event_PostCollisionAdd.h" 
#include "../Physics/Event_PostCollisionRemove.h" 
#include "../Physics/Box2DPhysics.h"
#include "../Audio/AudioEngine.h"
#include "../Scene/LightNode.h"
#include "../Scene/Scene.h"

#include <algorithm>

ControlComponent::ControlComponent() : m_Velocity(0.0), m_IsJumping(false), m_NrGroundCollisionsAdd(0), m_NrGroundCollisionsRemove(0)
{

}

ControlComponent::~ControlComponent()
{
    // remove callback functions from event queue
    EventListenerDelegate listener1 = fastdelegate::MakeDelegate(this, &ControlComponent::PostCollisionAdd);
    GameApplication::GetInstance()->GetEventManager()->RemoveListener(listener1, Event_PostCollisionAdd::s_EventType);
}

bool ControlComponent::VInit(void)
{
    m_Velocity = 3.0;
    // register callback functions
    EventListenerDelegate listener = fastdelegate::MakeDelegate(this, &ControlComponent::PostCollisionAdd);
    GameApplication::GetInstance()->GetEventManager()->AddListener(listener, Event_PostCollisionAdd::s_EventType);
    return true;
}

void ControlComponent::VUpdate(float deltaTime)
{
    // pre-calculate relevant state
    glm::vec2 bodyCenter = m_Owner->GetPosition() + m_Owner->GetScale() * 0.5f;
    Box2DPhysics *physics = GameApplication::GetInstance()->GetPhysics();
    std::shared_ptr<ISceneNode> node = GameApplication::GetInstance()->GetScene()->GetSceneNode(m_Owner->GetID());
    std::shared_ptr<SpriteNode> sprite = std::dynamic_pointer_cast<SpriteNode>(node);
    // apply forces based on user input
    float max = m_Velocity;
    bool moved = false;
    b2Vec2 vel = physics->FindBody(m_Owner->GetID())->GetLinearVelocity();
    if (GameApplication::GetInstance()->IsKeyPressed(GLFW_KEY_D))
    {
        if (vel.x <= max)
            physics->ApplyImpulse(m_Owner->GetID(), glm::vec2(m_Velocity * 500.0f * deltaTime, 0.0), bodyCenter);
        moved = true;
        if (sprite)
            sprite->SetReverse(false);
    }
    if (GameApplication::GetInstance()->IsKeyPressed(GLFW_KEY_A))
    {
        if (vel.x >= -max)
            physics->ApplyImpulse(m_Owner->GetID(), glm::vec2(-m_Velocity * 500.0f * deltaTime, 0.0), bodyCenter);
        moved = true;
        if (sprite)
            sprite->SetReverse(true);
    }
    if (GameApplication::GetInstance()->IsKeyPressed(GLFW_KEY_SPACE) && !m_IsJumping)
    {
        GameApplication::GetInstance()->GetAudio()->PlaySound("audio/jump.mp3");
        if (vel.y >= -5.0f)
            GameApplication::GetInstance()->GetPhysics()->ApplyImpulse(m_Owner->GetID(), glm::vec2(0.0, -750.0), bodyCenter);
        m_IsJumping = true;
    }

    if (sprite)
    {
        if (m_IsJumping)
            sprite->ActivateAnimation("jump");
        else if (moved)
            sprite->ActivateAnimation("walk");
        else
            sprite->ActivateAnimation("idle");
    }

    // rethink Actor->SceneNode relations, this can probably be done in a more 'elegant' way
    auto actorNodeChildren = GameApplication::GetInstance()->GetScene()->GetSceneNode(m_Owner->GetID())->GetChildren();
    for (auto it = actorNodeChildren.begin(); it != actorNodeChildren.end(); ++it)
    {
        std::shared_ptr<LightNode> lantern = std::dynamic_pointer_cast<LightNode>((*it));
        if (lantern) // if one of its children is a lightNode, it is a lantern; set relative position
        {
            glm::vec2 offset(12.0f, 10.0f);
            if (sprite && sprite->GetReverse())
                offset = glm::vec2(-offset.x, offset.y);
            lantern->SetPosition(m_Owner->GetPosition() + offset);
        }
    }

    GameApplication::GetInstance()->GetAudio()->SetPlayerPosition(m_Owner->GetPosition());
}

void ControlComponent::SetVelocity(float velocity)
{
    m_Velocity = velocity;
}

void ControlComponent::PostCollisionAdd(std::shared_ptr<IEventData> eventData)
{
    std::shared_ptr<Event_PostCollisionAdd> data = std::dynamic_pointer_cast<Event_PostCollisionAdd>(eventData);
    if (eventData)
    {
        const b2Contact* contact = data->GetContact();
        const b2Body* character = GameApplication::GetInstance()->GetPhysics()->FindBody(m_Owner->GetID());
        const b2Fixture* fixtureA = contact->GetFixtureA();
        const b2Fixture* fixtureB = contact->GetFixtureB();

        if (contact->IsTouching())
        {
            if (fixtureA->GetBody() == character || character == fixtureB->GetBody())
            {   // we have a collision with the character body
                bool fixtureAIsPlayer = fixtureA->GetBody() == character;
                if ((fixtureAIsPlayer && fixtureA->IsSensor()) || (!fixtureAIsPlayer && fixtureB->IsSensor()))
                {
                    // only do stuff if a single one is a sensor
                    if ((fixtureA->IsSensor() && !fixtureB->IsSensor()) || (!fixtureA->IsSensor() && fixtureB->IsSensor()))
                    {
                        m_IsJumping = false;
                        std::shared_ptr<ISceneNode> node = GameApplication::GetInstance()->GetScene()->GetSceneNode(m_Owner->GetID());
                        std::shared_ptr<SpriteNode> sprite = std::dynamic_pointer_cast<SpriteNode>(node);
                        if (sprite)
                            sprite->ActivateAnimation("idle");
                    }
                }
            }
        }
    }
}