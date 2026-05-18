#ifndef GAME_STATE_H
#define GAME_STATE_H

enum class GameState : std::uint8_t {
    MAIN_MENU,
    PLAYING,
    PAUSED,
    GAME_OVER
};

class Game_Engine_State{
    public:
    static GameState Current_State;
};

#endif