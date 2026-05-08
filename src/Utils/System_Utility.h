#ifndef SYSTEM_UTILITY_H
#define SYSTEM_UTILITY_H

#include <windows.h>

class System_Utility {
    public:
    
    static void Update_Logical_Mouse_Position(HWND hwnd, float Logical_Width, float Logical_Height);
};

#endif