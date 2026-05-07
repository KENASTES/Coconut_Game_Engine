#ifndef PLAYER_H
#define PLAYER_H

#include "vector"
#include "Game_Object.h"

class Player : public Game_Object {
    public:
    float Player_Movement_Speed = 200.0f;

    Player();
    void Update_Logic(double Delta_Tim, std::vector<Game_Object>& Game_World);
};

#endif