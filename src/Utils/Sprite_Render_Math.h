#ifndef SPRITE_RENDER_MATH_H
#define SPRITE_RENDER_MATH_H

#include <math.h>

namespace Render_Math
{
    inline void Create_Orthographic_Matrix(float *matrix, float left, float right, float bottom, float top)
    {
        for (int i = 0; i < 16; i++)
        {
            matrix[i] = 0.0f;
        }

        matrix[0] = 2.0f / (right - left);
        matrix[5] = 2.0f / (top - bottom);
        matrix[10] = -1.0f;
        matrix[12] = -(right + left) / (right - left);
        matrix[13] = -(top + bottom) / (top - bottom);
        matrix[15] = 1.0f;
    }

    inline void Create_Model_Matrix(float* Matrix, float Position_X, float Position_Y, float Rotation_Deg, float Scale_X, float Scale_Y) {
        for (int i = 0; i < 16; i++) Matrix[i] = 0.0f;
        
        float Rad = Rotation_Deg * (3.14159265359f / 180.0f);
        float Cos_Value = cos(Rad);
        float Sin_Value = sin(Rad);

        Matrix[0]  = Scale_X * Cos_Value;  
        Matrix[1]  = Scale_X * Sin_Value;  
        Matrix[4]  = Scale_Y * -Sin_Value; 
        Matrix[5]  = Scale_Y * Cos_Value;  
        Matrix[10] = 1.0f;
        Matrix[12] = Position_X;
        Matrix[13] = Position_Y;
        Matrix[15] = 1.0f;
    }
}

#endif