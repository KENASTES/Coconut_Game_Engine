#include <Input.h>
#include <windows.h>

bool Input::Keys_State[256] = {false};
float Input::Mouse_Position_X = 0.0f;
float Input::Mouse_Position_Y = 0.0f;

bool Input::Is_Key_Pressed(int Virtual_Key)
{
    return Keys_State[Virtual_Key];
}

bool Input::Is_Mouse_Left_Button_Clicked() {
    return Keys_State[VK_LBUTTON];
}