// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>

using namespace glm;

int main()
{
    if(!glfwInit())
    {
        fprintf(stderr, "Problem to initialize GLFW\n");
        return -1;
    }
}
