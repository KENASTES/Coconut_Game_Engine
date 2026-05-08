#ifndef INPUT_H
#define INPUT_H

class Input {
    public:
    static bool Keys_State[256];
    static float Mouse_Position_X;
    static float Mouse_Position_Y;

    static bool Is_Key_Pressed(int Virtual_Key);
    static bool Is_Mouse_Left_Button_Clicked();
};

#endif