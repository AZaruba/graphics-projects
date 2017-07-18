//
//  vertexReader.cpp
//  
//
//  Reads in .zvx files
//  .zvx file format:
//  First line is a header containing how many vertices are in the file
//  following lines are the vertices in floats
//
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

int
getNumVertices(std::ifstream& vertFile)
{
    char firstLine[11];
    
    int arrayLength;
    vertFile.getline(firstLine, 11);
    
    arrayLength = std::stoi(firstLine, nullptr, 10);
    if (arrayLength > 0)
    {
        return arrayLength;
    }

    return 0;
}

std::vector<float>
convertVerts(std::ifstream& vertFile, int numVerts)
{
    std::vector<float> vertArray;
    
    int counter = 0;
    char line[14];
    float floatStorage;
    
    while (counter < numVerts)
    {
        vertFile.getline(line, 14);
        sscanf(line,"%f",&floatStorage);
        vertArray.push_back(floatStorage);
        counter++;
    }
    return vertArray;
}

int
grabVertCount(const char* fileName)
{
    std::ifstream vertexFile;
    vertexFile.open(fileName, std::ios::in);
    
    if (vertexFile.is_open())
    {
        int numVertices = getNumVertices(vertexFile);
        if (numVertices == 0)
        {
            std::cout << "ERROR: Invalid vertex array size\n";
            vertexFile.close();
            return 0;
        }
        return numVertices;
    }
    else
    {
        vertexFile.close();
        return 0;
    }

}

std::vector<float>
parseArray(const char* fileName)
{
    std::vector<float> vertArray;
    std::ifstream vertexFile;
    vertexFile.open(fileName, std::ios::in);
    
    if (vertexFile.is_open())
    {
        int numVertices = getNumVertices(vertexFile);
        if (numVertices == 0)
        {
            std::cout << "ERROR: Invalid vertex array size\n";
            vertexFile.close();
            return vertArray;
        }
        vertArray = convertVerts(vertexFile, numVertices);
        vertexFile.close();
        return vertArray;
        
    }
    else
    {
        vertexFile.close();
        return vertArray;
    }
    vertexFile.close();
    return vertArray;
}
