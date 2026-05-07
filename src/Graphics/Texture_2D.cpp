#include "Texture_2D.h"

Texture_2D::Texture_2D() : Width(0), Height(0), Texture_ID(0){

}

void Texture_2D::Generate(int Width, int Height, unsigned char* Data_Stream, int nrChannels)
{
    this->Width = Width;
    this->Height = Height;

    if (this->Texture_ID == 0){
        glGenTextures(1, &this->Texture_ID);
    }

    glBindTexture(GL_TEXTURE_2D, this->Texture_ID);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    GLenum Format = (nrChannels == 4) ? GL_RGBA : GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0, Format, Width, Height, 0, Format, GL_UNSIGNED_BYTE, Data_Stream);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture_2D::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->Texture_ID);
}