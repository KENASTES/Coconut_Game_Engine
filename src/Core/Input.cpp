#include <Input.h>
#include <windows.h>

bool Input::Keys_State[256] = {false};

void Input::Update()
{

    for (int i = 0; i < 256; i++)
    {
        Keys_State[i] = (GetAsyncKeyState(i) & 0x8000) != 0;
    }
}

bool Input::Is_Key_Pressed(int Virtual_Key)
{
    return Keys_State[Virtual_Key];
}