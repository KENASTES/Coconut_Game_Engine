#include "Game_Object.h"
#include "../Utils/Sprite_Render_Math.h"
#include <math.h>

Game_Object::Game_Object() : Position_X(0) , Position_Y(0), Width(100), Height(100), Rotation(0), Sprite() {
    Update_Model_Matrix();
}

Game_Object::Game_Object(float Position_X, float Position_Y, float Width, float Height, float Rotation, Texture_2D Sprite) : Position_X(Position_X), Position_Y(Position_Y), Width(Width), Height(Height), Rotation(Rotation), Sprite(Sprite) {
    Update_Model_Matrix();
}

void Game_Object::Update_Model_Matrix() {
    Render_Math::Create_Model_Matrix(Model_Matrix, Position_X, Position_Y, Rotation, Width, Height);
}

void Game_Object::Draw(Sprite_Renderer& renderer, GLuint shader_program) {
    GLint modelLocation = glGetUniformLocation(shader_program, "u_Model");
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, this->Model_Matrix);
    glActiveTexture(GL_TEXTURE0);
    this->Sprite.Bind();
    glUniform1i(glGetUniformLocation(shader_program, "u_Texture"), 0);
    renderer.Draw();
}