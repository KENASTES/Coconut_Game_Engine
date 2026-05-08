#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>
#include "../Graphics/Texture_2D.h"

class Resource_Manager {
    public:
    static std::map<std::string, Texture_2D> Textures;
    static Texture_2D Load_Texture(const char* File_Path, const std::string& File_Name);
    static Texture_2D& Get_Texture(const std::string& File_Name);
    static void Clear();
};

#endif