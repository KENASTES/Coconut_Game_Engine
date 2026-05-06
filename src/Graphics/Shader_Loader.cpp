#include "Shader_Loader.h"

std::string Load_Shader_Source(const char* File_Path) {
    std::string Shader_Content;
    std::ifstream Shader_File(File_Path, std::ios::in);

    if (!Shader_File.is_open()) {
        std::cerr << "Failed to open shader file: " << File_Path << std::endl;
        return "";
    }

    std::stringstream sstr;
    sstr << Shader_File.rdbuf();
    Shader_Content = sstr.str();
    Shader_File.close();

    return Shader_Content;
}

GLuint Load_And_Compile_Shader(const char *Vertex_Path, const char *Fragment_Path) {
    std::string Vertex_Code = Load_Shader_Source(Vertex_Path);
    std::string Fragment_Code = Load_Shader_Source(Fragment_Path);
    const char* v_Shader_Code = Vertex_Code.c_str();
    const char* f_Shader_Code = Fragment_Code.c_str();

    GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &v_Shader_Code, NULL);
    glCompileShader(vertex);

    GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &f_Shader_Code, NULL);
    glCompileShader(fragment);

    GLuint Shader_Program = glCreateProgram();
    glAttachShader(Shader_Program, vertex);
    glAttachShader(Shader_Program, fragment);
    glLinkProgram(Shader_Program);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return Shader_Program;
}