//
//  shaderReader.cpp
//  
//
//  Created by Andrew Zaruba on 6/29/17.
//
//

#include <iostream>
#include <string>
#include <fstream>

const char*
parseShader(const char* fileName)
{
    
    std::string currentLine;
    std::ifstream shaderFile;
    shaderFile.open(fileName, std::ios::in);
    
    if (shaderFile.is_open())
    {
        std::string fileText((std::istreambuf_iterator<char>(shaderFile)),
                             std::istreambuf_iterator<char>());
        const char *fileOut = fileText.c_str();
        shaderFile.close();
        return fileOut;
    }
    else
    {
        char badResult = '\0';
        const char *fileOut = &badResult;
        return fileOut;
    }
}
