#include "UI_Element.h"
#include "../Utils/Sprite_Render_Math.h"
#include "../Core/Input.h"

UI_Element::UI_Element(float Position_X, float Position_Y, float Width, float Height, const Texture_2D& Texture) {
    Position_X = Position_X;
    Position_Y = Position_Y;
    Width = Width;
    Height = Height;
    Texture = Texture;
    Update_UI_Matrix();
};

bool UI_Element::Is_Mouse_Hovered(float Mouse_X, float Mouse_Y) const {
    return (Mouse_X >= Position_X && Mouse_X <= Position_X + Width && Mouse_Y >= Position_Y && Mouse_Y <= Position_Y + Height);
}

bool UI_Element::Is_Mouse_Clicked(float Mouse_X, float Mouse_Y) const {
    return (Is_Mouse_Hovered(Mouse_X, Mouse_Y) && Input::Is_Mouse_Left_Button_Clicked());
}

void UI_Element::Update_UI_Matrix() {
    Sprite_Render_Math::Create_Model_Matrix( Model_Matrix, Position_X, Position_Y, Width, Height, 0.0f );
}

void UI_Element::UI_Draw(Sprite_Renderer& Renderer, GLuint Shader_ID) {
    GLint Model_Location = glGetUniformLocation(Shader_ID, "u_Model");
    glUniformMatrix4fv(Model_Location, 1, GL_FALSE, Model_Matrix);

    glActiveTexture(GL_TEXTURE0);
    Texture.Bind();
    glUniform1i(glGetUniformLocation(Shader_ID, "u_Texture"), 0);
    Renderer.Draw();
}