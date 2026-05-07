#include <windows.h>
#include <string>
#include <GL/gl.h>
#include <stddef.h>
#include <Input.h>
#include <Player.h>
#include "OpenGL_Loader.h"
#include "Sprite_Renderer.h"
#include "Shader_Loader.h"
#include "Sprite_Render_Math.h"
#include "Resource_Manager.h"

HDC hdc;
HGLRC hrc;

extern "C"
{
    __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

bool Init_OpenGL(HWND hwnd)
{
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
    SetPixelFormat(hdc, pixel_Format, &pfd);
    if (!pixel_Format)
        return false;
    if (!SetPixelFormat(hdc, pixel_Format, &pfd))
        return false;

    hrc = wglCreateContext(hdc);
    wglMakeCurrent(hdc, hrc);
    if (!hrc)
        return false;
    if (!wglMakeCurrent(hdc, hrc))
        return false;

    return true;
}

LRESULT CALLBACK Window_Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_ERASEBKGND:
        return 1;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        BeginPaint(hwnd, &ps);
        EndPaint(hwnd, &ps);
        return 0;
    }

    case WM_SIZE:
        if (hrc)
        {
            glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
        }
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    Player player;
    const char CLASS_NAME[] = "MyEngineWindowClass";

    WNDCLASS wc = {};
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = Window_Proc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "My Custom Game Engine",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1200, 720,
        NULL,
        NULL,
        hInstance,
        NULL);

    if (hwnd == NULL)
        return 0;

    Init_OpenGL(hwnd);

    if (!Load_Modern_OpenGL())
    {
        return 0;
    }

    Resource_Manager::Load_Texture("assets/sprites/player.jpg", "player");

    GLuint Shader_Program = Load_And_Compile_Shader("assets/shader/normal_vertex.vert", "assets/shader/normal_fragment.frag");
    
    Sprite_Renderer sprite_Renderer;
    sprite_Renderer.Set_Shader(Shader_Program);

    RECT rect;
    GetClientRect(hwnd, &rect);
    glViewport(0, 0, rect.right, rect.bottom);

    std::string gpuName = "Unknown GPU";
    const char *rendererStr = (const char *)glGetString(GL_RENDERER);
    if (rendererStr)
        gpuName = rendererStr;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    LARGE_INTEGER frequency, time_Start, time_End;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&time_Start);

    double Delta_Time = 0.0;
    double Time_Elapsed = 0.0;
    int Frame_Count = 0;

    bool isRunning = true;

    MSG msg = {};

    while (isRunning)
    {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                isRunning = false;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (!isRunning)
            break;

        QueryPerformanceCounter(&time_End);
        Delta_Time = (double)(time_End.QuadPart - time_Start.QuadPart) / frequency.QuadPart;
        time_Start = time_End;

        Input::Update(hwnd);
        player.Update_Logic(Delta_Time);

        Frame_Count++;
        Time_Elapsed += Delta_Time;
        if (Time_Elapsed >= 1.0)
        {
            std::string title = "My Custom Game Engine | GPU: " + gpuName + 
                                " | FPS: " + std::to_string(Frame_Count) + 
                                " | Delta Time: " + std::to_string(Delta_Time) + 
                                "s | X: " + std::to_string(player.Player_Position_X) +
                                " | Y: " + std::to_string(player.Player_Position_Y);
            SetWindowText(hwnd, title.c_str());
            Frame_Count = 0;
            Time_Elapsed -= 1.0;
        }

        glClearColor(0.1f, 0.2f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(Shader_Program);

        float orthoMatrix[16];

        Render_Math::Create_Orthographic_Matrix(orthoMatrix, 0.0f, 800.0f, 0.0f, 600.0f);

        player.Update_Model_Matrix();

        GLint projLocation = glGetUniformLocation(Shader_Program, "u_Projection");
        glUniformMatrix4fv(projLocation, 1, GL_FALSE, orthoMatrix);

        GLint modelLocation = glGetUniformLocation(Shader_Program, "u_Model");
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, player.Model_Matrix);

        glActiveTexture(GL_TEXTURE0);
        Resource_Manager::Get_Texture("player").Bind();
        glUniform1i(glGetUniformLocation(Shader_Program, "u_Texture"), 0);

        sprite_Renderer.Draw();

        SwapBuffers(hdc);
    }
    return 0;
}