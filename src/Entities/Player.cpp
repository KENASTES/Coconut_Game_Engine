#include <Player.h>
#include <Input.h>
#include <math.h>


Player::Player() {
    Update_Model_Matrix();
}

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
    Update_Model_Matrix();
};

void Player::Update_Model_Matrix() {
    for (int i = 0; i < 16; i++) {
        Model_Matrix[i] = 0.0f;
    }

    float Rad = Rotation * (3.14159265359f / 180.0f);
    float Cos_Value = cos(Rad);
    float Sin_Value = sin(Rad);

    Model_Matrix[0]  = Player_Width * Cos_Value;  
    Model_Matrix[1]  = Player_Width * Sin_Value;
    Model_Matrix[4]  = Player_Height * -Sin_Value;
    Model_Matrix[5]  = Player_Height * Cos_Value;
    Model_Matrix[10] = 1.0f;
    Model_Matrix[12] = Player_Position_X;
    Model_Matrix[13] = Player_Position_Y;
    Model_Matrix[15] = 1.0f;
}
