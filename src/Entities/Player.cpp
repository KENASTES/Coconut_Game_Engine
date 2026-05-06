#include <Player.h>
#include <Input.h>

void Player::Update_Logic(double Delta_Time)
{
    if (Input::Is_Key_Pressed('W'))
        Player_Position_Y += Player_Movement_Speed * Delta_Time;
    if (Input::Is_Key_Pressed('S'))
        Player_Position_Y -= Player_Movement_Speed * Delta_Time;
    if (Input::Is_Key_Pressed('A'))
        Player_Position_X -= Player_Movement_Speed * Delta_Time;
    if (Input::Is_Key_Pressed('D'))
        Player_Position_X += Player_Movement_Speed * Delta_Time;
};
