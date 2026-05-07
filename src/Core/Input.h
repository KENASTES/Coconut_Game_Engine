#ifndef INPUT_H
#define INPUT_H

class Input {
    public:
    static bool Keys_State[256];

    static void Update();
    static bool Is_Key_Pressed(int Virtual_Key);
};

#endif