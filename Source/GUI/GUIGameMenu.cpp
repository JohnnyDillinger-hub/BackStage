#include "GUIGameMenu.h"

#include "GUIButton.h"

#include "../Application/GameApplication.h"
#include "../Application/Event_QuitGame.h"
#include "../Application/Event_StartLevel.h"
#include "../Communication/EventManager.h"
#include "../Resources/ResourceManager.h"
#include "../Renderer/PostProcesser.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Renderer.h"
#include "../Renderer/shader.h"
#include "../Scene/Camera.h"
#include "../Scene/Scene.h"

#include <fstream>
#include <memory>

GUIGameMenu::GUIGameMenu()
{

}

bool GUIGameMenu::Init()
{
    // full screen 
    SetScale(glm::vec2(GameApplication::GetInstance()->ScreenWidth(), GameApplication::GetInstance()->ScreenHeight()));

    // continue game
    std::shared_ptr<GUIButton> btnContinue(new GUIButton);
    btnContinue->SetName("btnContinue");
    btnContinue->SetPosition(glm::vec2(m_Scale.x * 0.3f, m_Scale.y * 0.3f));
    btnContinue->SetScale(glm::vec2(m_Scale.x * 0.4f, 50.0f));
    btnContinue->SetForeColor(glm::vec4(glm::vec3(0.6f), 1.0f));
    btnContinue->SetHoverColor(glm::vec4(1.0f));
    btnContinue->SetText("Continue");
    // save
    std::shared_ptr<GUIButton> btnSave(new GUIButton);
    btnSave->SetName("btnSave");
    btnSave->SetPosition(glm::vec2(m_Scale.x * 0.3f, m_Scale.y * 0.4f));
    btnSave->SetScale(glm::vec2(m_Scale.x * 0.4f, 50.0f));
    btnSave->SetForeColor(glm::vec4(glm::vec3(0.6f), 1.0f));
    btnSave->SetHoverColor(glm::vec4(1.0f));
    btnSave->SetText("Save");
    // quit
    std::shared_ptr<GUIButton> btnQuit(new GUIButton);
    btnQuit->SetName("btnQuit");
    btnQuit->SetPosition(glm::vec2(m_Scale.x * 0.3f, m_Scale.y * 0.5f));
    btnQuit->SetScale(glm::vec2(m_Scale.x * 0.4f, 50.0f));
    btnQuit->SetForeColor(glm::vec4(glm::vec3(0.6f), 1.0f));
    btnQuit->SetHoverColor(glm::vec4(1.0f));
    btnQuit->SetText("Quit Game");

    // add elements to container control
    AddElement(btnContinue);
    AddElement(btnSave);
    AddElement(btnQuit);

    // load additional resources
    m_BackgroundTexture = ResourceManager::GetInstance()->LoadTexture("game_menu_background", "textures/backgrounds/game_menu_background.png", true);
    return true;
}

void GUIGameMenu::Update(float deltaTime)
{

}

void GUIGameMenu::RenderBackground(Renderer *renderer, TextRenderer *textRenderer)
{
    std::shared_ptr<Shader> spriteShader = ResourceManager::GetInstance()->GetShader("sprite");
    spriteShader->Use();
    spriteShader->SetMatrix4("projection", GameApplication::GetInstance()->GetScene()->GetCamera()->GetProjection());
    spriteShader->SetMatrix4("view", glm::mat4());
    spriteShader->SetInteger("EnableLighting", 0);
    spriteShader->SetVector4f("ColorOverride", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    // render background
    glm::mat4 model;
    model *= glm::scale(glm::vec3(m_Scale, 1.0f));
    spriteShader->SetMatrix4("model", model);
    m_BackgroundTexture->Bind(0);
    renderer->RenderQuad();

    spriteShader->SetInteger("EnableLighting", 1);
}

void GUIGameMenu::OnActivate()
{
    GameApplication::GetInstance()->GetRenderer()->EnableEffect(POST_PROCESS_EFFECT::POST_PROCESS_BLUR);
    //GameApplication::GetInstance()->GetRenderer()->EnableEffect(POST_PROCESS_EFFECT::POST_PROCESS_GRAYSCALE);
    //GameApplication::GetInstance()->GetRenderer()->EnableEffect(POST_PROCESS_EFFECT::POST_PROCESS_INVERT);
}

void GUIGameMenu::OnDeactivate()
{
    GameApplication::GetInstance()->GetRenderer()->DisableEffect(POST_PROCESS_EFFECT::POST_PROCESS_BLUR);
    //GameApplication::GetInstance()->GetRenderer()->DisableEffect(POST_PROCESS_EFFECT::POST_PROCESS_GRAYSCALE);
    //GameApplication::GetInstance()->GetRenderer()->DisableEffect(POST_PROCESS_EFFECT::POST_PROCESS_INVERT);

    GameApplication::GetInstance()->SwitchState(GameState::GAME_MAIN); // back to game state
}
void GUIGameMenu::ButtonPressed(std::shared_ptr<GUIButton> pButton) 
{
    std::string name = pButton->GetName();
    if (name == "btnContinue")
    {   // continue game as usual       
        SetActive(false);
    }
    else if (name == "btnSave")
    {    // send out load game event (with level loaded from savefile)
        std::ofstream file;
        file.open("save.dat", std::ios::trunc);
        file << GameApplication::GetInstance()->GetScene()->GetScenePath();
        file.close();
        SetActive(false);
    }
    else if (name == "btnQuit")
    {   // send out game quit event
        std::shared_ptr<IEventData> pEvent(new Event_QuitGame());
        GameApplication::GetInstance()->GetEventManager()->QueueEvent(pEvent);
    }
}