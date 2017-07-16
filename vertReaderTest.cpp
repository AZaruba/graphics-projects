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
    float* vertexArray = parseArray("testVerts.zvx");
    
    free(vertexArray);
    return 1;
}
