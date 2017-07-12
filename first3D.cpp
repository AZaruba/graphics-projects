//
//  first3D.cpp
//  
//
//  Created by Andrew Zaruba on 6/25/17.
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#include <OpenGL/gl3.h>
#define __gl_h_
#include <OpenGL/glu.h>
#include <GLFW/glfw3.h>

#include "shaderReader.cpp"

/*
 * TODO: 
 * 1) Create a way to take a glsl file and turn it into a sring for use here
 * 2) Create .cpp file that takes a series of vertices in some format (check Blender outputs)
 * and transforms it into 3D vertices/data useful for OpenGL
 */

// temporary
const char* vertShaderCode;
const char* fragShaderCode;

// z-coord is zero to appear 2D
float triVerts[] = {
    0.0f,0.0f,0.0f,
    0.0f,0.5f,0.0f,
    0.5f,0.25f,0.0f
};

unsigned int vertBuff;
unsigned int vertArray;

unsigned int vertexShader;
unsigned int fragShader;

unsigned int shaderProgram;

void
framebuffer_size_callback(GLFWwindow* window, int width, int height);

void
bufferSetup(unsigned int* vb, unsigned int* va)
{
    
    glGenBuffers(1, vb);
    glGenVertexArrays(1, va);
    
    glBindVertexArray(*va);
    
    glBindBuffer(GL_ARRAY_BUFFER, *vb);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triVerts), triVerts, GL_STATIC_DRAW); // GL_STREAM???
    
    //                   (location, vertex size, data type, normalize?, "stride", offset)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    glBindVertexArray(0);
}

/* shaderType: 0 - vertex shader
 *             1 - fragment shader
 *
 */
void
compileShader(unsigned int* shaderLoc, const char* shaderName, const char* basicShader, int shaderType)
{
    basicShader = parseShader(shaderName);
    char infoLog[512];
    if (!*basicShader)
    {
        std::cout << "ERROR: could not parse shader file " << shaderName << "\n";
        return;
    }
    
    switch (shaderType)
    {
        case 0 : { *shaderLoc = glCreateShader(GL_VERTEX_SHADER); break; }
        case 1 : { *shaderLoc = glCreateShader(GL_FRAGMENT_SHADER); break;}
        break;
        default :
        {
            std::cout << "ERROR: invalid shader type\nSHADER TYPES\n"
              << "0 - vertex shader\n1 - fragment shader\n";
        }
    }
    
    glShaderSource(*shaderLoc, 1, &basicShader, NULL);
    glCompileShader(*shaderLoc);
    
    int success;
    glGetShaderiv(*shaderLoc, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(*shaderLoc, 512, NULL, infoLog);
        std::cout << "ERROR: shader failed to compile\n" << infoLog << '\n';
    }
}

void
linkProgram(unsigned int* vs, unsigned int* fs)
{
    char infoLog[512];
    
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, *vs);
    glAttachShader(shaderProgram, *fs);
    glLinkProgram(shaderProgram);
    
    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR: shaders failed to link\n" << infoLog << '\n';
    }
    
    glDeleteShader(*vs);
    glDeleteShader(*fs);
}

int
main(int argc, char** argv)
{
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow* window = glfwCreateWindow(512, 512, "First3D", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "ERROR: Window uninitialized\n";
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    bufferSetup(&vertBuff, &vertArray);
    std::string tempShader = "vertShader";
    compileShader(&vertexShader, tempShader.c_str(), vertShaderCode, 0);
    
    tempShader = "fragShader";
    compileShader(&fragShader, tempShader.c_str(), fragShaderCode, 1);
    
    linkProgram(&vertexShader, &fragShader);
    
    while (!glfwWindowShouldClose(window))
    {
        //input
        //processInput(window);
        
        //render
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        //draw
        glUseProgram(shaderProgram);
        glBindVertexArray(vertArray);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    exit(0);
}

void
framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0,0,width,height);
}
