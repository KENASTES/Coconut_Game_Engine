#ifndef WINODW_INTERACTION_H
#define WINODW_INTERACTION_H

#include <windows.h>

class Window_Interaction {
    private:
    HWND hwnd;
    HDC hdc;
    HGLRC hrc;
    bool isRunning;

    bool Init_OpenGL();

    public:
    Window_Interaction();
    ~Window_Interaction();
     
    static LRESULT CALLBACK Window_Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    void Set_Running(bool State);
    bool Initialize(int Width, int Height, const char* Title);
    bool Process_Messages();
    void Swap_Buffers();
    HWND Get_HWND() const;
    bool Is_Running() const;
};

#endif