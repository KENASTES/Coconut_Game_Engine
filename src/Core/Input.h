#pragma once
#include <windows.h>

namespace Input {
    void Update(HWND windowHandle);
    bool Is_Key_Pressed(int Virtual_Key);
}