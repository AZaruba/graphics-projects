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

#include <OpenGL/gl.h>
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
const char* basicShader;

// z-coord is zero to appear 2D
float triVerts[] = {
    0.0f,0.0f,0.0f,
    0.0f,0.5f,0.0f,
    0.5f,0.25f,0.0f
};

unsigned int vertBuff;
unsigned int shader;

void
framebuffer_size_callback(GLFWwindow* window, int width, int height);

void
bufferSetup(unsigned int* buffer)
{
    glGenBuffers(1, buffer);
    glBindBuffer(GL_ARRAY_BUFFER, *buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triVerts), triVerts, GL_STATIC_DRAW); // GL_STREAM???
}

void
compileShader(unsigned int* shaderLoc, const char* shaderName)
{
    basicShader = parseShader(shaderName);
    char infoLog[512];
    if (!*basicShader) {
        std::cout << "ERROR: could not parse shader file " << shaderName << "\n";
        return;
    }
    *shaderLoc = glCreateShader(GL_VERTEX_SHADER);
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
    
    bufferSetup(&vertBuff);
    std::string tempShader = "vertShader";
    compileShader(&shader, tempShader.c_str());
    
    while (!glfwWindowShouldClose(window))
    {
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
