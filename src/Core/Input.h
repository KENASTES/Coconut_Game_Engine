#ifndef INPUT_H
#define INPUT_H

#include <windows.h>
#include <cstdint>

class Input {
    public:
    static HWND Target_Window;
    static bool Keys_State[256];
    static bool Previous_Keys_State[256];
    static float Mouse_Position_X;
    static float Mouse_Position_Y;
    
    static void Update();
    static bool Is_Key_Pressed(int Key_Code);
    static bool Is_Key_Just_Pressed(int Key_Code);
    static bool Is_Mouse_Left_Button_Clicked();
};

#endif