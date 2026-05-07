#include <Player.h>
#include <Input.h>
#include <math.h>

bool Check_Collision(float x1, float y1, float w1, float h1,
                     float x2, float y2, float w2, float h2)
{
    bool Collision_X = x1 < x2 + w2 && x1 + w1 > x2;
    bool Collision_Y = y1 < y2 + h2 && y1 + h1 > y2;
    return Collision_X && Collision_Y;
}

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
        if (Check_Collision(Position_X, Position_Y, Width, Height, obj.Position_X, obj.Position_Y, obj.Width, obj.Height))
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
        if (Check_Collision(Position_X, Position_Y, Width, Height, obj.Position_X, obj.Position_Y, obj.Width, obj.Height))
        {
            Position_X = Old_Position_X;
            break;
        }
    }

    this->Update_Model_Matrix();
};
