#include "Window_Interaction.h"
#include "../Graphics/OpenGL_Loader.h"

static Window_Interaction* Current_Window = nullptr;

Window_Interaction::Window_Interaction() : hwnd(NULL), hdc(NULL), hrc(NULL), isRunning(false) {
    Current_Window = this;
}

Window_Interaction::~Window_Interaction() {
    if (hrc) {
        wglMakeCurrent(NULL, NULL);
        wglDeleteContext(hrc);
    }
    if (hdc) ReleaseDC(hwnd, hdc);
    if (hwnd) DestroyWindow(hwnd);
}

LRESULT CALLBACK Window_Interaction::Window_Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_ERASEBKGND:
            return 1;
        case WM_SIZE:
            if (Current_Window && Current_Window->hrc) {
                glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
            }
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            if (Current_Window) Current_Window->isRunning = false;
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

bool Window_Interaction::Init_OpenGL() {
    hdc = GetDC(hwnd);
    PIXELFORMATDESCRIPTOR pfd = {};
    pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cDepthBits = 0;
    pfd.iLayerType = PFD_MAIN_PLANE;

    int pixel_Format = ChoosePixelFormat(hdc, &pfd);
    if (!pixel_Format || !SetPixelFormat(hdc, pixel_Format, &pfd)) return false;

    hrc = wglCreateContext(hdc);
    wglMakeCurrent(hdc, hrc);

    return true;
}

void Window_Interaction::Set_Running(bool State) {
    isRunning = State;
}

bool Window_Interaction::Initialize(int width, int height, const char* title) {
    const char CLASS_NAME[] = "Coconut_Engine_Window";

    WNDCLASS wc = {};
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = Window_Proc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    hwnd = CreateWindowEx(
        0, CLASS_NAME, title,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, width, height,
        NULL, NULL, GetModuleHandle(NULL), NULL
    );

    if (hwnd == NULL) return false;

    if (!Init_OpenGL()) return false;
    if (!Load_Modern_OpenGL()) return false;

    ShowWindow(hwnd, SW_SHOW);
    UpdateWindow(hwnd);
    
    isRunning = true;
    return true;
}

bool Window_Interaction::Process_Messages() {
    MSG msg = {};
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT) {
            isRunning = false;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return isRunning;
}

void Window_Interaction::Swap_Buffers() {
    SwapBuffers(hdc);
}

HWND Window_Interaction::Get_HWND() const {
    return hwnd;
}

bool Window_Interaction::Is_Running() const {
    return isRunning;
}