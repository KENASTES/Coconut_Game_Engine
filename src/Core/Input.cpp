#include <Input.h>
#include <windows.h>

HWND Input::Target_Window = NULL;
bool Input::Keys_State[256] = {false};
float Input::Mouse_Position_X = 0.0f;
float Input::Mouse_Position_Y = 0.0f;



bool Input::Is_Key_Pressed(int Key_Code)
{
    if (GetForegroundWindow() != Target_Window) return false;
    return (GetAsyncKeyState(Key_Code) & 0x8000) != 0;
}

bool Input::Is_Mouse_Left_Button_Clicked() {
    if (GetForegroundWindow() != Target_Window) return false;
    return (GetAsyncKeyState(0x01) & 0x8000) != 0;
}