#ifndef LOADSCENE_H
#define LOADSCENE_H

#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>

#include "primitives.h"

class parsedScene{
    public:		
        int width, height, reflectiondepth, triangleCount, lightCount; 
        float fov;        
        float aaJitter; // jitter distance, 0 means none, 16 means approx 16 pixels???? not really, but it looks like it
						// jitter does not work unless aaDepth >= 2.0
		float aaDepth; // how many more iterations for aa, 1 means none, 32 is really strong, shoudl be d^k

        Color ambient;
        Vector3 lookfrom, lookat, up_dir;

        std::string outputFileName;
        
        float (*triangleList)[16];
		float (*brdfList)[16];
        float (*lightList)[12];
    
    parsedScene(); 
    
};// class parsedScene

parsedScene loadScene(std::string file);
#endif
