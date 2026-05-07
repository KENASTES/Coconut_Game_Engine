#ifndef TEXTURE_2D_H
#define TEXTURE_2D_H

#include <GL/gl.h>
#include "OpenGL_Loader.h"

class Texture_2D
{
    public:
    GLuint Texture_ID;
    int Width, Height;

    Texture_2D();

    void Generate(int Width, int Height, unsigned char* Data_Stream, int nrChannels);
    void Bind() const;
};

#endif