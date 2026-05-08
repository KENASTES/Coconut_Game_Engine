#ifndef CAMERA_PROJECTION_H
#define CAMERA_PROJECTION_H

#include "../Entities/Game_Object.h"

class Camera_Projection {
    public:
    float Camera_Position_X;
    float Camera_Position_Y;
    float Viewport_Width;
    float Viewport_Height;

    Camera_Projection(float Width, float Height);

    void Object_Follow(const Game_Object& Target);

    void Get_Projection_Matrix(float* Matrix);
};

#endif