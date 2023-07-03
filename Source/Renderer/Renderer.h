#ifndef RENDERER_H
#define RENDERER_H

#include "PostProcesser.h"

/*
    The primary render system, managing all OpenGL related render functionality.
*/
class Renderer
{
private:
    PostProcessor* m_PostProcessor; // the post processor in use to render post-processing effects
    unsigned int   m_VAO, m_VBO;    // the OpenGL render state for rendering a single sprite

    // configures the OpenGL render state for rendering a single sprite
    void configureQuad();
public:
    Renderer();
    ~Renderer();

    // initializes the renderer and all relevant OpenGL state
    virtual void Initialize();
    // render operations before rendering the scene
    virtual void PreRender();
    // renders a 1x1 quad in normalized device coordinates
    virtual void RenderQuad();

    // configures the post-processer to store the next render calls into the post-processing buffers
    virtual void PrePostProcessRender();
    // stops storing all render calls in the post-processing buffers and saves the render data
    virtual void PostPostProcessRender();
    // renders a quad with the stored render data plus additional post-processing effects applied
    virtual void PostProcessQuadRender();

    // enables a specific post-processing effect
    virtual void EnableEffect(POST_PROCESS_EFFECT effect);
    // disables a specific post-processing effect
    virtual void DisableEffect(POST_PROCESS_EFFECT effect);
};
#endif