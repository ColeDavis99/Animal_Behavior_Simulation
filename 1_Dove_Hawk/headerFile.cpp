#include "headerFile.h"
#include <iostream>
using std::cout;
using std::endl;
/*
FUNCTION DEFINITIONS
*/

void buildVisualizerString(long numDoves, long numHawks, long const EXTRA_SPACE, string &visualizer)
{

    int SCALAR = EXTRA_SPACE/(EXTRA_SPACE*.025);

    //cout<<"SCALAR: "<<SCALAR<<endl;

    for (long i = 0; i < numDoves; i++)
    {
        if (i % 50 == 0)
            visualizer.append("o");
    }
    visualizer.append("\n");

    for (long q = 0; q < numHawks; q++)
    {
        if (q % 50 == 0)
            visualizer.append("|");
    }
    visualizer.append("\n\n");
}
