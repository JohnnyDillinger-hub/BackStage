#include "GUISceneIntro.h"

#include "../Application/GameApplication.h"
#include "../Resources/ResourceManager.h"
#include "../Renderer/TextRenderer.h"
#include "../Renderer/Renderer.h"
#include "../Renderer/Shader.h"
#include "../Renderer/Texture2D.h"
#include "../Audio/AudioEngine.h"
#include "../Scene/Camera.h"
#include "../Scene/Scene.h"

#include <memory>

GUISceneIntro::GUISceneIntro() : m_IntroText(""), m_TimeActive(0.0f), m_Alpha(1.0f), m_TextAlpha(1.0f)
{

}

std::string GUISceneIntro::GetIntroText()
{
    return m_IntroText;
}
void GUISceneIntro::SetIntroText(std::string text)
{
    m_IntroText = text;
}

bool GUISceneIntro::Init()
{
    SetScale(glm::vec2(GameApplication::GetInstance()->ScreenWidth(), GameApplication::GetInstance()->ScreenHeight()));
    m_BackgroundTexture = ResourceManager::GetInstance()->LoadTexture("intro_background", "textures/backgrounds/intro_background.jpg", false);
    return true;
}

void GUISceneIntro::Update(float deltaTime)
{
    if (m_IsActive)
    {
        if (m_TimeActive < 10.0f)
        {
            m_TextAlpha += deltaTime * 0.1f;
        }
        else if (m_TimeActive >= 10.0f && m_TimeActive < 11.0f)
        {
            m_Alpha     -= deltaTime * 0.9f; // not 1.0 as to make it more clear we're entering game state
            m_TextAlpha -= deltaTime * 0.9f;
        }
        else if (m_TimeActive >= 11.0f)
        {
            SetActive(false);
        }
        //else // quick hack for disabling intro @ start for quicker live debugging
            //SetActive(false);

        m_TimeActive += deltaTime;
    }
}

void GUISceneIntro::RenderBackground(Renderer *renderer, TextRenderer *textRenderer)
{
    std::shared_ptr<Shader> spriteShader = ResourceManager::GetInstance()->GetShader("sprite");
    spriteShader->Use();
    spriteShader->SetMatrix4("projection", GameApplication::GetInstance()->GetScene()->GetCamera()->GetProjection());
    spriteShader->SetMatrix4("view", glm::mat4());
    spriteShader->SetInteger("EnableLighting", 0);
    spriteShader->SetVector4f("ColorOverride", glm::vec4(1.0f, 1.0f, 1.0f, m_Alpha));
    // 1. first render background
    glm::mat4 model;
    model *= glm::scale(glm::vec3(m_Scale, 1.0f));
    spriteShader->SetMatrix4("model", model);
    m_BackgroundTexture->Bind(0);
    renderer->RenderQuad();
    // 2. then text
    // note that here the sentence is instantly broken as soon as the max char limit per row is reached.
    // in a future system we'd look for \n symbols and then break the text; this should be build in the
    // text renderer.
    std::vector<std::string> subTexts;
    int charsPerNewline = 50;
    std::string line;
    for(int i = 0; i < m_IntroText.size() ; ++i)
    {
        if (i % charsPerNewline == 0 || i == m_IntroText.size() - 1)
        {
            if(i == m_IntroText.size() - 1)
                line += m_IntroText[i]; // in case of last character; add to line before creating new line memory
            if(line != "")
                subTexts.push_back(line);
            line = std::string();
        }
        line += m_IntroText[i];
    }
    for(int i = 0; i < subTexts.size(); ++i)
        textRenderer->RenderText(subTexts[i], glm::vec2(150.0f, 100.0f + 30.0f * i), 2.0f, false, glm::vec4(0.65f, 0.65f, 0.65f, m_TextAlpha), glm::vec2(m_Scale.x - 300.0f, 30.0f));

    spriteShader->SetInteger("EnableLighting", 1);
}

void GUISceneIntro::OnActivate()
{
    m_Alpha = 1.0f;
    m_TextAlpha = 0.0f;
    m_TimeActive = 0.0f;
    GameApplication::GetInstance()->GetAudio()->PlaySound("audio/scene_intro.mp3");
}

void GUISceneIntro::OnDeactivate()
{
    GameApplication::GetInstance()->SwitchState(GameState::GAME_MAIN); // go to game
}



