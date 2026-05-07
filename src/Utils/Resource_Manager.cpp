#include "Resource_Manager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../Graphics/stb_image.h"

std::map<std::string, Texture_2D> Resource_Manager::Textures;

Texture_2D Resource_Manager::Load_Texture(const char* File_Path, std::string File_Name){
    if (Textures.find(File_Name) != Textures.end()) {
        return Textures[File_Name];
    }

    Texture_2D texture;
    stbi_set_flip_vertically_on_load(true);
    int Width, Height, nrChannels;
    unsigned char* Data_Stream = stbi_load(File_Path, &Width, &Height, &nrChannels, 0);

    if(Data_Stream){
        texture.Generate(Width, Height, Data_Stream, nrChannels);
        stbi_image_free(Data_Stream);
    } else {
        printf("Failed to load texture: %s\n", File_Path);
    }

    Textures[File_Name] = texture;
    return Textures[File_Name];
}

Texture_2D Resource_Manager::Get_Texture(std::string File_Name) {
    return Textures[File_Name];
}

void Resource_Manager::Clear() {
    for (auto iter : Textures) {
        glDeleteTextures(1, &iter.second.Texture_ID);
    }
    Textures.clear();
}