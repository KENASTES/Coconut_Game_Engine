#include "Camera_Projection.h"
#include "../Utils/Sprite_Render_Math.h"

Camera_Projection::Camera_Projection(float Width, float Height)
{
    Camera_Position_X = 0.0f;
    Camera_Position_Y = 0.0f;
    Viewport_Width = Width;
    Viewport_Height = Height;
}

void Camera_Projection::Object_Follow(const Game_Object &Target)
{
    Camera_Position_X = Target.Position_X + Target.Width / 2.0f - Viewport_Width / 2.0f;
    Camera_Position_Y = Target.Position_Y + Target.Height / 2.0f - Viewport_Height / 2.0f;
}

void Camera_Projection::Get_Projection_Matrix(float *Matrix)
{
    Render_Math::Create_Orthographic_Matrix(Matrix, Camera_Position_X, Camera_Position_X + Viewport_Width, Camera_Position_Y, Camera_Position_Y + Viewport_Height);
}