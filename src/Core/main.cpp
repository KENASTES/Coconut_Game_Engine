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
#include "Time.h"
#include "Camera_Projection.h"
#include "UI_Element.h"
#include "System_Utility.h"
#include "Asset_Loader.h"

Window_Interaction Game_Window;

extern "C"
{
    __declspec(dllexport) DWORD NvOptimusEnablement = 0x00000001;
    __declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pCmdLine, int nCmdShow)
{
    Game_Window.Initialize(1200, 720, "My Custom Game Engine");
    Input::Target_Window = Game_Window.Get_HWND();
    if (!Load_Modern_OpenGL())
    {
        return 0;
    }

    GLuint Shader_Program;
    Asset_Loader::Load_Initial_Assets(Shader_Program);

    Player player;
    std::vector<Game_Object> Game_World;

    player.Sprite = Resource_Manager::Get_Texture("player");
    UI_Element Test_Button(50.0f, 50.0f, 100.0f, 50.0f, Resource_Manager::Get_Texture("box"));
    Game_World.push_back(Game_Object(200.0f, 100.0f, 50.0f, 50.0f, 0.0f, Resource_Manager::Get_Texture("box")));
    Game_World.push_back(Game_Object(300.0f, 100.0f, 50.0f, 50.0f, 0.0f, Resource_Manager::Get_Texture("box")));
    Game_World.push_back(Game_Object(400.0f, 100.0f, 50.0f, 50.0f, 0.0f, Resource_Manager::Get_Texture("box")));

    Sprite_Renderer sprite_Renderer;

    float UI_Projection_Matrix[16];
    Camera_Projection Main_Camera(800.0f, 600.0f);

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

    double Time_Elapsed = 0.0;
    int Frame_Count = 0;

    MSG msg = {};

    Time::Initialize();

    while (Game_Window.Process_Messages())
    {
        Time::Update();
        POINT mouse_Pt;
        GetCursorPos(&mouse_Pt);
        ScreenToClient(Game_Window.Get_HWND(), &mouse_Pt);
        double Delta_Time = Time::Get_Delta_Time();
        System_Utility::Update_Logical_Mouse_Position(Game_Window.Get_HWND(), 800.0f, 600.0f);
        player.Update_Logic(Delta_Time, Game_World);
        Main_Camera.Object_Follow(player);

        if (Test_Button.Is_Mouse_Clicked(Input::Mouse_Position_X, Input::Mouse_Position_Y))
        {
            SetWindowText(Game_Window.Get_HWND(), "BUTTON CLICKED!!!");
        }

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
        Main_Camera.Get_Projection_Matrix(orthoMatrix);

        GLint projLocation = glGetUniformLocation(Shader_Program, "u_Projection");
        glUniformMatrix4fv(projLocation, 1, GL_FALSE, orthoMatrix);

        for (auto &obj : Game_World)
        {
            obj.Update_Model_Matrix();
            obj.Draw(sprite_Renderer, Shader_Program);
        }

        player.Update_Model_Matrix();
        player.Draw(sprite_Renderer, Shader_Program);

        float UI_Projection_Matrix[16];
        Render_Math::Create_Orthographic_Matrix(UI_Projection_Matrix, 0.0f, 800.0f, 0.0f, 600.0f);

        GLint modelLocation = glGetUniformLocation(Shader_Program, "u_Model");
        glUniformMatrix4fv(projLocation, 1, GL_FALSE, UI_Projection_Matrix);

        Test_Button.UI_Draw(sprite_Renderer, Shader_Program);

        Game_Window.Swap_Buffers();
    }
    return 0;
}