#include <Input.h>

namespace Input {
    HWND Current_Window_Handle = NULL;

    void Update(HWND windowHandle) {
        Current_Window_Handle = windowHandle;
    }

    bool Is_Key_Pressed(int Virtual_Key) {
        if (GetForegroundWindow() != Current_Window_Handle) {
            return false;
        }

        return (GetAsyncKeyState(Virtual_Key) & 0x8000) != 0;
    }
}