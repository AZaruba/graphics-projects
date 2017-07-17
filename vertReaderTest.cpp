//
//  vertReaderTest.cpp
//  
//
//  Created by Andrew Zaruba on 7/15/17.
//  Test file for vertexReader
//

#include <stdio.h>
#include <string>
#include "vertexReader.cpp"

int
main (int argc, char **argv)
{
    int vertCount = grabVertCount("testVerts.zvx");
    if (!vertCount || vertCount <= 0)
    {
        std::cout << "Test failed: could not grab vertex count\n";
    }
    
    float* vertexArray = parseArray("testVerts.zvx");
    if (!vertexArray)
    {
        std::cout << "Test failed: could not parse .zvx file\n";
    }
    
    int counter = 0;
    while (counter < vertCount)
    {
        std::cout << "Vertex " << counter << ": " << vertexArray[counter] << '\n';
        counter++;
    }
    
    free(vertexArray);
    return 1;
}
