#pragma once

class Player {
    public:
    float Player_Position_X = 0.0f;
    float Player_Position_Y = 0.0f;
    float Player_Movement_Speed = 200.0f;
    float Player_Width = 100.0f;
    float Player_Height = 100.0f;
    float Rotation = 0.0f;
    float Model_Matrix[16];

    Player();
    void Update_Logic(double Delta_Time);
    void Update_Model_Matrix();
};