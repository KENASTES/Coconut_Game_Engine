#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#include <string>
#include <GL/gl.h>

GLuint Load_And_Compile_Shader(const char *Vertex_Path, const char *Fragment_Path);

#endif