#ifndef SHADER_HPP
#define SHADER_HPP
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
GLuint loadDDS(const char * imagepath);
GLuint loadBMP_custom(const char * imagepath);
#endif
