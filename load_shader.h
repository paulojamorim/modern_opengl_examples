#ifndef LOAD_SHADER_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define LOAD_SHADER_H

#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);

#endif
