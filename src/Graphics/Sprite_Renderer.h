#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <GL/gl.h>
#include "OpenGL_Loader.h"

struct Vertex {
    float Position[3];
    float TexCoord[2];
};

class Sprite_Renderer {
    private:
    GLuint VAO, VBO, EBO;
    GLuint Current_Shader_ID;

    public:
    Sprite_Renderer();
    ~Sprite_Renderer();

    void Set_Shader(GLuint shaderID);
    void Draw();
};

#endif