#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include "load_shader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>


// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
static const GLfloat g_vertex_buffer_data[] = {
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end

    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
};

// One color for each vertex. They were generated randomly.
static const GLfloat g_color_buffer_data[] = {
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f
};




//using namespace glm;

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

    glfwSetWindowTitle("Cube");

    glfwEnable( GLFW_STICKY_KEYS );

    //Background color
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    

    // ------------- Draw Triangle ---------------------------------   


    // Draw the triangle !

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    GLuint ColorArrayID;
    glGenVertexArrays(2, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

 
    //This will indentify our vertex buffer
    GLuint vertexbuffer;
    //Generate 1 buffer, put the resulting idenfier in vertexbuffer
    glGenBuffers(1,&vertexbuffer);
    //The following commands will talk about our 'vertexbuffer' bufer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    //Give our vertices to openGL
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


    GLuint colorbuffer;
    glGenBuffers(1,&colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW); 
 

    // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f); 
    
    //Camera matrix
    glm::mat4 View = glm::lookAt(
                glm::vec3(2,3,3), //camera is at (4,3,3) in world space
                glm::vec3(0,0,0), // and looks at the origin
                glm::vec3(0,1,0)); // Head is up (set to 0, -1,0 to llo upside-down)

    //Model matrix: an identity matrix (model will be at origin
    glm::mat4 Model = glm::mat4(1.0f); //Change for each model
    
    //Our Model View Projection: Multiplication of our 3 matrices
    glm::mat4 MVP = Projection * View * Model;
    
    // Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders( "../cube_vertex.glsl", "../cube_fragment.glsl");
    
    //Use our shader
    glUseProgram(programID);
    
    //Get a handle for our "MVP" uniform
    // Only at initialisation time
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    
    //Send our transformation to the current bound shader
    //in the "MVP" uniform
    //For each model you render, since the MVP will be different (at least the M part)
    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    
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


        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glVertexAttribPointer(
            1,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void*)0);

        //Draw the triangle
        //glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
        glDrawArrays(GL_TRIANGLES, 0, 12*3); // 12*3 indices starting at 0 -> 12 triangles -> 6 squares

   

        glDisableVertexAttribArray(0);

    }
    while(glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS && glfwGetWindowParam(GLFW_OPENED));
}
