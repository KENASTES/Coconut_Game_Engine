#ifndef SHADER_LOADER_H
#define SHADER_LOADER_H

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

std::string Load_Shader_Source(const char* File_Path);
GLuint Load_And_Compile_Shader(const char *Vertex_Path, const char *Fragment_Path);

#endif