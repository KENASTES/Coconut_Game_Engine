#include "Asset_Loader.h"
#include "Resource_Manager.h"
#include "../Graphics/Shader_Loader.h"

void Asset_Loader::Load_Initial_Assets(GLuint& Out_Shader_Program){
    Resource_Manager::Load_Texture("assets/sprites/player.jpg", "player");
    Resource_Manager::Load_Texture("assets/sprites/Box.png", "box");
    Out_Shader_Program = Load_And_Compile_Shader("assets/shader/normal_vertex.vert", "assets/shader/normal_fragment.frag");

}