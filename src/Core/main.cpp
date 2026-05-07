#include <string>
#include <GL/gl.h>
#include <stddef.h>
#include <Input.h>
#include <Player.h>
#include <vector>

#include "Window_Interaction.h"
#include "OpenGL_Loader.h"
#include "Sprite_Renderer.h"
#include "Shader_Loader.h"
#include "Sprite_Render_Math.h"
#include "Resource_Manager.h"
#include "Game_Object.h"

Window_Interaction Game_Window;

extern "C"
{
    __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    const char CLASS_NAME[] = "MyEngineWindowClass";

    WNDCLASS wc = {};
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = Window_Interaction::Window_Proc;
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

    Game_Window.Initialize(1200, 720, "My Custom Game Engine");

    if (!Load_Modern_OpenGL())
    {
        return 0;
    }

    Resource_Manager::Load_Texture("assets/sprites/player.jpg", "player");
    Resource_Manager::Load_Texture("assets/sprites/Box.png", "box");
    GLuint Shader_Program = Load_And_Compile_Shader("assets/shader/normal_vertex.vert", "assets/shader/normal_fragment.frag");

    Player player;
    std::vector<Game_Object> Game_World;

    Game_World.push_back(Game_Object(200.0f, 100.0f, 50.0f, 50.0f, 0.0f, Resource_Manager::Get_Texture("box")));
    Game_World.push_back(Game_Object(300.0f, 100.0f, 50.0f, 50.0f, 0.0f, Resource_Manager::Get_Texture("box")));
    Game_World.push_back(Game_Object(400.0f, 100.0f, 50.0f, 50.0f, 0.0f, Resource_Manager::Get_Texture("box")));

    Sprite_Renderer sprite_Renderer;
    sprite_Renderer.Set_Shader(Shader_Program);

    RECT rect;
    GetClientRect(Game_Window.Get_HWND(), &rect);
    glViewport(0, 0, rect.right, rect.bottom);

    std::string gpuName = "Unknown GPU";
    const char *rendererStr = (const char *)glGetString(GL_RENDERER);
    if (rendererStr)
        gpuName = rendererStr;

    ShowWindow(Game_Window.Get_HWND(), nCmdShow);
    UpdateWindow(Game_Window.Get_HWND());

    LARGE_INTEGER frequency, time_Start, time_End;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&time_Start);

    double Delta_Time = 0.0;
    double Time_Elapsed = 0.0;
    int Frame_Count = 0;

    MSG msg = {};

    while (Game_Window.Process_Messages())
    {
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                Game_Window.Set_Running(false);
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (!Game_Window.Is_Running())
            break;

        QueryPerformanceCounter(&time_End);
        Delta_Time = (double)(time_End.QuadPart - time_Start.QuadPart) / frequency.QuadPart;
        time_Start = time_End;

        Input::Update();
        player.Update_Logic(Delta_Time, Game_World);

        Frame_Count++;
        Time_Elapsed += Delta_Time;
        if (Time_Elapsed >= 1.0)
        {
            std::string title = "My Custom Game Engine | GPU: " + gpuName +
                                " | FPS: " + std::to_string(Frame_Count) +
                                " | Delta Time: " + std::to_string(Delta_Time) +
                                "s | X: " + std::to_string(player.Position_X) +
                                " | Y: " + std::to_string(player.Position_Y);
            SetWindowText(Game_Window.Get_HWND(), title.c_str());
            Frame_Count = 0;
            Time_Elapsed -= 1.0;
        }

        glClearColor(0.1f, 0.2f, 0.4f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(Shader_Program);

        float orthoMatrix[16];

        Render_Math::Create_Orthographic_Matrix(orthoMatrix, 0.0f, 800.0f, 0.0f, 600.0f);

        for (auto& obj : Game_World) {
            obj.Update_Model_Matrix(); 
            obj.Draw(sprite_Renderer, Shader_Program);
        }

        player.Update_Model_Matrix();

        GLint projLocation = glGetUniformLocation(Shader_Program, "u_Projection");
        glUniformMatrix4fv(projLocation, 1, GL_FALSE, orthoMatrix);

        GLint modelLocation = glGetUniformLocation(Shader_Program, "u_Model");
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, player.Model_Matrix);

        glActiveTexture(GL_TEXTURE0);
        Resource_Manager::Get_Texture("player").Bind();
        glUniform1i(glGetUniformLocation(Shader_Program, "u_Texture"), 0);

        sprite_Renderer.Draw();

        Game_Window.Swap_Buffers();
    }
    return 0;
}