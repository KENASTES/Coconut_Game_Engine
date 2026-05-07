#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Game_Object.h"

class Player : public Game_Object {
    public:
    float Player_Movement_Speed = 200.0f;

    Player();
    void Update_Logic(double Delta_Time);
};

#endif