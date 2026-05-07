#include <Player.h>
#include <Input.h>
#include <math.h>


Player::Player() : Game_Object() {
    this->Position_X = 0.0f;
    this->Position_Y = 0.0f;
    this->Width = 100.0f;
    this->Height = 100.0f;
}

void Player::Update_Logic(double Delta_Time)
{
    if (Input::Is_Key_Pressed('W'))
        Position_Y += Player_Movement_Speed * Delta_Time;
    if (Input::Is_Key_Pressed('S'))
            Position_Y -= Player_Movement_Speed * Delta_Time;
    if (Input::Is_Key_Pressed('A'))
        Position_X -= Player_Movement_Speed * Delta_Time;
    if (Input::Is_Key_Pressed('D'))
        Position_X += Player_Movement_Speed * Delta_Time;
    this->Update_Model_Matrix();
};

