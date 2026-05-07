#include "Player.h"
#include "../Core/Input.h"
#include <math.h>

Player::Player() : Game_Object()
{
    this->Position_X = 0.0f;
    this->Position_Y = 0.0f;
    this->Width = 100.0f;
    this->Height = 100.0f;
}

void Player::Update_Logic(double Delta_Time, std::vector<Game_Object>& Game_World)
{
    float Old_Position_Y = Position_Y;

    if (Input::Is_Key_Pressed('W'))
        Position_Y += Player_Movement_Speed * Delta_Time;
    if (Input::Is_Key_Pressed('S'))
        Position_Y -= Player_Movement_Speed * Delta_Time;

    for (auto &obj : Game_World)
    {

        if (this->Check_Collision(obj)) 
        {
            Position_Y = Old_Position_Y;
            break;
        }
    }

    float Old_Position_X = Position_X;

    if (Input::Is_Key_Pressed('A'))
        Position_X -= Player_Movement_Speed * Delta_Time;
    if (Input::Is_Key_Pressed('D'))
        Position_X += Player_Movement_Speed * Delta_Time;

    for (auto &obj : Game_World)
    {
        if (this->Check_Collision(obj))
        {
            Position_X = Old_Position_X;
            break;
        }
    }

    this->Update_Model_Matrix();
};
