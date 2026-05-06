#pragma once

class Player {
    public:
    float Player_Position_X = 0.0f;
    float Player_Position_Y = 0.0f;
    float Player_Movement_Speed = 200.0f;

    void Update_Logic(double Delta_Time);
};