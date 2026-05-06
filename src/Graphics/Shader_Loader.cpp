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