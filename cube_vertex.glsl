#version 330 core

layout(location = 1) in vec3 vertexColor;
in vec3 vertexPosition_modelspace;
uniform mat4 MVP;

out vec3 fragmentColor;

void main()
{
    //Output position of the vertex, in clip space: MVP * position
    vec4 v = vec4(vertexPosition_modelspace,1); //Transform an homogeneus 4D vector
    gl_Position = MVP * v;
    fragmentColor = vertexColor;
}

