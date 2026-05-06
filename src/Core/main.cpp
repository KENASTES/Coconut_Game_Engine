#include <windows.h>
#include <string>
#include <GL/gl.h>
#include <stddef.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "OpenGL_Loader.h"
#include <Input.h>
#include <Player.h>

GLuint Create_Basic_Shader()
{
    const char *vertexShaderSource =
        "#version 330 core\n"
        "layout(location = 0) in vec3 aPos;\n"
        "layout(location = 1) in vec2 aTexCoord;\n"
        "out vec2 TexCoord;\n"
        "uniform vec2 u_Offset;\n"
        "uniform mat4 u_Projection;\n"
        "void main()\n"
        "{\n"
        "   vec4 WorldPos = vec4(aPos.x + u_Offset.x, aPos.y + u_Offset.y, aPos.z, 1.0);\n"
        "   gl_Position = u_Projection * WorldPos;\n"
        "   TexCoord = aTexCoord;\n"
        "}\0";

    const char *fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec2 TexCoord;\n"
        "uniform sampler2D ourTexture;\n"
        "void main()\n"
        "{\n"
        "   vec4 texColor = texture(ourTexture, TexCoord);\n"
        "   if(texColor.a < 0.1) discard;\n"
        "   FragColor = texColor;\n"
        "}\0";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLint success;
    char InfoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, InfoLog);
        MessageBox(NULL, InfoLog, "Shader Compilation Error", MB_OK);
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, InfoLog);
        MessageBox(NULL, InfoLog, "Shader Linking Error", MB_OK);
    }

    return shaderProgram;
}

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

void Create_Orthographic_Matrix(float* matrix, float left, float right, float bottom, float top){
    for (int i = 0; i < 16; i++) {
        matrix[i] = 0.0f;
    }

    matrix[0] = 2.0f / (right - left);
    matrix[5] = 2.0f / (top - bottom);
    matrix[10] = -1.0f;
    matrix[12] = -(right + left) / (right - left);
    matrix[13] = -(top + bottom) / (top - bottom);
    matrix[15] = 1.0f;
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

    GLuint shaderProgram = Create_Basic_Shader();

    float vertices[] = {
        100.0f,  100.0f, 0.0f,          1.0f, 1.0f,
        100.0f,    0.0f, 0.0f,          1.0f, 0.0f,
          0.0f,    0.0f, 0.0f,          0.0f, 0.0f,
          0.0f,  100.0f, 0.0f,          0.0f, 1.0
    };

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char *data = stbi_load("assets/sprites/player.jpg", &width, &height, &nrChannels, 0);

    if (data)
    {
        GLenum format = (nrChannels == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    }
    else
    {
        MessageBox(NULL, "Failed to load texture!", "Texture Error", MB_OK);
    }

    stbi_image_free(data);

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

        glUseProgram(shaderProgram);

        float orthoMatrix[16];

        Create_Orthographic_Matrix(orthoMatrix, 0.0f, 800.0f, 0.0f, 600.0f);

        GLint projLocation = glGetUniformLocation(shaderProgram, "u_Projection");
        glUniformMatrix4fv(projLocation, 1, GL_FALSE, orthoMatrix);

        GLint offsetLocation = glGetUniformLocation(shaderProgram, "u_Offset");

        glUniform2f(offsetLocation, player.Player_Position_X, player.Player_Position_Y);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        SwapBuffers(hdc);
    }
    return 0;
}