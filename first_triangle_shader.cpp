// Include standard headers

/* OpenGL Coordinates to 3D

         y
         ^
         `                                                     
         `                                                     
         `                                            
         `                                            
         ;'''''''''''''''>  x
        #                                          
       #                                           
      #                                                     
     |           
    z

*/

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include "load_shader.h"

using namespace glm;

int main()
{
    if(!glfwInit())
    {
        fprintf(stderr, "Problem to initialize GLFW\n");
        return -1;
    }

    glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
    glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if(!glfwOpenWindow(800, 600, 0, 0, 0, 0, 32, 0, GLFW_WINDOW))
    {
        fprintf(stderr, "Failed to open GLFW Window\n");
        glfwTerminate();
    return -1;
    }

    glewExperimental=true;
    
    if(glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    glfwSetWindowTitle("First Triangle");

    glfwEnable( GLFW_STICKY_KEYS );

    //Background color
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    

    // ------------- Draw Triangle ---------------------------------   
 
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    //Array with 3 vectors to represent which vertices
    static const GLfloat g_vertex_buffer_data[] = {
    -1.0f, -1.0f, 0.0f, //left vertex
    1.0f, -1.0f, 0.0f,  //right vertex
    0.0f, 1.0f, 0.0f,}; //top vertex
   
 
    //This will indentify our vertex buffer
    GLuint vertexbuffer;

    //Generate 1 buffer, put the resulting idenfier in vertexbuffer
    glGenBuffers(1,&vertexbuffer);

    //The following commands will talk about our 'vertexbuffer' bufer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

    //Give our vertices to openGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    // Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders( "../first_triangle_shader_vertex.glsl", "../first_triangle_shader_fragment.glsl");

    //Use our shader
    glUseProgram(programID);

    
    do
    {
        glfwSwapBuffers();
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);        

        //1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

        glVertexAttribPointer(
            0, //attribute 0. No particular reason for 0, but must match the layout in the shader.
            3, //size
            GL_FLOAT, //type
            GL_FALSE, //normalized?
            0, //stride
            (void*)0); //array buffer offset

        //Draw the triangle
        glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    
        glDisableVertexAttribArray(0);

    }
    while(glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS && glfwGetWindowParam(GLFW_OPENED));
}
