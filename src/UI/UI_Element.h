#ifndef UI_ELEMENT_H
#define UI_ELEMENT_H

#include <GL/gl.h>
#include "../Graphics/Texture_2D.h"
#include "../Graphics/Sprite_Renderer.h"

class UI_Element {
    public:
    float Position_X;
    float Position_Y;
    float Width;
    float Height;
    Texture_2D Texture;
    float Model_Matrix[16];

    UI_Element(float Position_X, float Position_Y, float Width, float Height, const Texture_2D& UI_Texture);

    bool Is_Mouse_Hovered(float Mouse_X, float Mouse_Y) const;
    bool Is_Mouse_Clicked(float Mouse_X, float Mouse_Y) const;

    void Update_UI_Matrix();
    void UI_Draw(Sprite_Renderer& Renderer, GLuint Shader_ID);
};

#endif