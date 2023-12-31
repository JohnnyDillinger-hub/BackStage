#include "GUIButton.h"

#include "../Application/GameApplication.h"
#include "../Renderer/TextRenderer.h"
#include "../Renderer/Renderer.h"
#include "../Renderer/shader.h"

GUIButton::GUIButton()
{

}

std::string GUIButton::GetText()
{
    return m_Text;
}
glm::vec4 GUIButton::GetHoverColor()
{
    return m_HoverColor;
}

void GUIButton::SetText(std::string text)
{
    m_Text = text;
}
void GUIButton::SetHoverColor(glm::vec4 color)
{
    m_HoverColor = color;
}


void GUIButton::CalculateModel()
{
    m_Model = glm::mat4();
    m_Model *= glm::translate(glm::vec3(m_Position, 0.0));
    m_Model *= glm::scale(glm::vec3(m_Scale, 1.0));
}

void GUIButton::Render(Renderer *renderer, TextRenderer* textRenderer, std::shared_ptr<Shader> shader)
{
    // shader is passed from top hierarchy, we only control its parameter/rendering configuration
    if (m_BackColor != glm::vec4(1.0f)) // if a back-color is set, render box
    {
        shader->SetMatrix4("model", m_Model);
        shader->SetVector4f("backColor", m_BackColor);
        renderer->RenderQuad();
    }
    // always render text (GUIButtons are by default text w/ box)
    textRenderer->RenderText(m_Text, m_Position, 3.5f, false, m_MouseEntered ? m_HoverColor : m_ForeColor, m_Scale);
}