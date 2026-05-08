#include "System_Utility.h"
#include "../Core/Input.h"

void System_Utility::Update_Logical_Mouse_Position(HWND hwnd, float Logical_Width, float Logical_Height) {
    POINT mouse_Pt;
    GetCursorPos(&mouse_Pt);
    ScreenToClient(hwnd, &mouse_Pt);

    RECT client_rect;
    GetClientRect(hwnd, &client_rect);
    float client_width = (float)client_rect.right;
    float client_height = (float)client_rect.bottom;

    if (client_width == 0 || client_height == 0) return; 

    Input::Mouse_Position_X = ((float)mouse_Pt.x / client_width) * Logical_Width;
    Input::Mouse_Position_Y = Logical_Height - (((float)mouse_Pt.y / client_height) * Logical_Height);
}