#ifndef GUI_BUTTON_H
#define GUI_BUTTON_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "GUIElement.h"

#include <string>

class Shader;
class Renderer;
class TextRenderer;

/*
    A button to be used for GUIs. GUIButton contains text and a background color
    at a rectangle surrounding the text. Whenever a mouse hovers over the rectangle
    the text color brights and can be clicked from GUI container(s).
*/
class GUIButton : public GUIElement
{
private:
    std::string m_Text;       // the text to render at the center of the button
    glm::vec4   m_HoverColor; // the color of the text when the mouse hovers over the button
public:
    GUIButton();

    // getters
    std::string GetText();
    glm::vec4   GetHoverColor();
    // setters
    void SetText(std::string text);
    void SetHoverColor(glm::vec4 color);

    // calculates the world-space model matrix for rendering the button
    void CalculateModel();
    // renders the button's background container and foreground text
    void Render(Renderer *renderer, TextRenderer *textRenderer, std::shared_ptr<Shader> shader);
};
#endif