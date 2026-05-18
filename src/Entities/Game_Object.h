#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <GL/gl.h>
#include "../Graphics/Texture_2D.h"
#include "../Graphics/Sprite_Renderer.h"

class Game_Object {
    public:
    float Position_X;
    float Position_Y;
    float Width;
    float Height;
    float Rotation;
    float Model_Matrix[16];
    Texture_2D Sprite;
    bool Is_Interactable = false;

    Game_Object();
    Game_Object(float Position_X, float Position_Y, float Width, float Height, float Rotation, Texture_2D Sprite);

    virtual ~Game_Object() = default;
    
    bool Check_Collision(const Game_Object& other) const;
    virtual void On_Interaction();
    virtual void Update_Model_Matrix();
    virtual void Draw(Sprite_Renderer& renderer, GLuint shaderID);
};

#endif