#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <memory>

class Texture2D;

/*
    A conventience class for managing framebuffer objects.
*/
class Framebuffer
{
    std::shared_ptr<Texture2D> m_ColorBuffer; // holds the color data of the framebuffer
    std::shared_ptr<Texture2D> m_DepthBuffer; // holds the depth information of the framebuffer

    unsigned int m_Width, m_Height; // the width and height of the framebuffer
    unsigned int m_FBO, m_RBO;      // the underlying OpenGL object IDs of the framebuffer and underlying render buffer object
public:
    Framebuffer(unsigned int width, unsigned int height);

    // getters
    std::shared_ptr<Texture2D> const GetColorBuffer();
    std::shared_ptr<Texture2D> const GetDepthBuffer();

    // update the texture used as the color buffer
    void UpdateColorBufferTexture(std::shared_ptr<Texture2D> texture);

    // binds the current framebuffer (without clearing)
    void Bind();
    // bind to framebuffer and clear buffers 
    void BeginRender();
    // unbind framebuffer to store data in buffers
    void EndRender();
};
#endif