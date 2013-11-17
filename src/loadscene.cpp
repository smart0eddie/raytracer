#include "loadscene.h"
#include "primitives.h"
using namespace std;


parsedScene loadScene(std::string file) {

  //store variables and set stuff at the end
  parsedScene S;  
  S.outputFileName = "output.png";  

  std::ifstream inpfile(file.c_str());
  if(!inpfile.is_open()) {
    //std::cout << "Unable to open file" << std::endl;
	throw 8;
  } else {
    std::string line;

	int lightIdx = 0;
	int triangleIdx = 0;
	int vertexIdx = 0;
	int vertexCount = 0;

    float (*vertices)[4];
	Brdf brdf = {0.2, 0.2, 0.2, 0, //kd
				 0, 0, 0, 0//ks
				 0, 0, 0, 0//ke
				 0, //kr
				 1, //sp				
				 0, 0}//dummy

    while(inpfile.good()) {
      std::vector<std::string> splitline;
      std::string buf;

      std::getline(inpfile,line);
      std::stringstream ss(line);

      while (ss >> buf) {
        splitline.push_back(buf);
      }
      //Ignore blank lines
      if(splitline.size() == 0) {
        continue;
      }

      //Ignore comments
      if(splitline[0][0] == '#') {
        continue;
      }

      //Valid commands:
      //size width height
      //  must be first command of file, controls image size
      else if(!splitline[0].compare("size")) {
        S.width = atoi(splitline[1].c_str());
        S.height = atoi(splitline[2].c_str());
      }
      //maxdepth depth
      //  max # of bounces for ray (default 5)
      else if(!splitline[0].compare("maxdepth")) {
          S.reflectiondepth = atoi(splitline[1].c_str());
      }
      //output filename
      //  output file to write image to 
      else if(!splitline[0].compare("output")) {
          S.outputFileName = splitline[1];
      }

      //camera lookfromx lookfromy lookfromz lookatx lookaty lookatz upx upy upz fov
      //  speciﬁes the camera in the standard way, as in homework 2.
      else if(!splitline[0].compare("camera")) {		  
		  setVector3(S.lookfrom, 
					 atof(splitline[1].c_str()), //x
					 atof(splitline[2].c_str()), //y
					 atof(splitline[3].c_str())); //z
		  setVector3(S.lookat,
					 atof(splitline[4].c_str()), //x
					 atof(splitline[5].c_str()), //y
					 atof(splitline[6].c_str())); //z
		  setVector3(S.up_dir,
					 atof(splitline[7].c_str()), //x
					 atof(splitline[8].c_str()), //y
					 atof(splitline[9].c_str())); //z
		  S.fov = atof(splitline[10].c_str());		       

      }

      //sphere x y z radius
      //  Deﬁnes a sphere with a given position and radius.
      else if(!splitline[0].compare("sphere")) {
		    //dont care
      }
      //maxverts number
      //  Deﬁnes a maximum number of vertices for later triangle speciﬁcations. 
      //  It must be set before vertices are deﬁned.
      else if(!splitline[0].compare("maxverts")) {
		  vertexCount = atof(splitline[1].c_str());
		  vertices = new float[vertexCount][4];
      }
	  //maxtri number
      //  Deﬁnes a maximum number of triangles for later triangle speciﬁcations. 
      //  It must be set before vertices are deﬁned.
      else if(!splitline[0].compare("maxtri")) {
		  S.triangleCount = atof(splitline[1].c_str());
		  S.triangleList = new float[triangleCount][16];
		  S.brdfList = new float[triangleCount][16];
      }
	  //maxlight number
      //  Deﬁnes a maximum number of lights for later triangle speciﬁcations. 
      //  It must be set before vertices are deﬁned.
      else if(!splitline[0].compare("maxlight")) {
		  S.lightCount = atof(splitline[1].c_str());
		  S.lightList = new float[lightCount][12];
      }
      //maxvertnorms number
      //  Deﬁnes a maximum number of vertices with normals for later speciﬁcations.
      //  It must be set before vertices with normals are deﬁned.
      else if(!splitline[0].compare("maxvertnorms")) {
			//dont care
      }
      //vertex x y z
      //  Deﬁnes a vertex at the given location.
      //  The vertex is put into a pile, starting to be numbered at 0.
      else if(!splitline[0].compare("vertex")) {
        // Create a new vertex with these 3 values, store in some array
		  if(vertexIdx < vertexCount){
			setVector3( &(vertices[vertexIdx][0]),
						atof(splitline[1].c_str()), //x
						atof(splitline[2].c_str()), //y
						atof(splitline[3].c_str())); //z
			++vertexIdx;
		  }//if
		  else{
			  cout << "more verteices than specified" << endl;
			  exit(1);
		  }//else
      }
      //vertexnormal x y z nx ny nz
      //  Similar to the above, but deﬁne a surface normal with each vertex.
      //  The vertex and vertexnormal set of vertices are completely independent
      //  (as are maxverts and maxvertnorms).
      else if(!splitline[0].compare("vertexnormal")) {
			//dont care
      }
      //tri v1 v2 v3
      //  Create a triangle out of the vertices involved (which have previously been speciﬁed with
      //  the vertex command). The vertices are assumed to be speciﬁed in counter-clockwise order. Your code
      //  should internally compute a face normal for this triangle.
      else if(!splitline[0].compare("tri")) {
		  if(triangleIdx < S.triangleCount){
			setTriangle( &(S.triangleList[triangleIdx][0]),
						 &(vertices[atof(splitline[1].c_str())][0]), //p1
						 &(vertices[atof(splitline[2].c_str())][0]), //p2
						 &(vertices[atof(splitline[3].c_str())][0])); //p3
			brdfCopy(&(S.brdfList[triangleIdx][0], brdf);
			++triangleIdx;
		  }//if
		  else{
			  cout << "more triangles than specified" << endl;
			  exit(1);
		  }//else		  
        // v1: atof(splitline[1].c_str())
        // v2: atof(splitline[2].c_str())
        // v3: atof(splitline[3].c_str())
        // Create new triangle:
        //   Store pointer to array of vertices
        //   Store 3 integers to index into array
        //   Store current property values
        //   Store current top of matrix stack
      }
      //trinormal v1 v2 v3
      //  Same as above but for vertices speciﬁed with normals.
      //  In this case, each vertex has an associated normal, 
      //  and when doing shading, you should interpolate the normals 
      //  for intermediate points on the triangle.
      else if(!splitline[0].compare("trinormal")) {
			//dont care
      }

      //translate x y z
      //  A translation 3-vector
      else if(!splitline[0].compare("translate")) {
          //dont care
      }
      //rotate x y z angle
      //  Rotate by angle (in degrees) about the given axis as in OpenGL.
      else if(!splitline[0].compare("rotate")) {
		  //dont care
      }
      //scale x y z
      //  Scale by the corresponding amount in each axis (a non-uniform scaling).
      else if(!splitline[0].compare("scale")) {
		  //dont care
      }
      //pushTransform
      //  Push the current modeling transform on the stack as in OpenGL. 
      //  You might want to do pushTransform immediately after setting 
      //   the camera to preserve the “identity” transformation.
      else if(!splitline[0].compare("pushTransform")) {
          //dont care
      }
      //popTransform
      //  Pop the current transform from the stack as in OpenGL. 
      //  The sequence of popTransform and pushTransform can be used if 
      //  desired before every primitive to reset the transformation 
      //  (assuming the initial camera transformation is on the stack as 
      //  discussed above).
      else if(!splitline[0].compare("popTransform")) {
		  //dont care
      }

      //directional x y z r g b
      //  The direction to the light source, and the color, as in OpenGL.
      else if(!splitline[0].compare("directional")) {
		  if(lightIdx < S.lightCount){
			setLight(&(S.lightList[lightIdx][0]),
					 atof(splitline[1].c_str()), //x
					 atof(splitline[2].c_str()), //y
					 atof(splitline[3].c_str()), //z
					 atof(splitline[4].c_str()), //r
					 atof(splitline[5].c_str()), //g
					 atof(splitline[6].c_str()), //b
					 true); //isDir
			++lightIdx;
		  }//if
		  else{
			  cout << "more lights than specified" << endl;
			  exit(1);
		  }//else  
        // add light to scene...
      }
      //point x y z r g b
      //  The location of a point source and the color, as in OpenGL.
      else if(!splitline[0].compare("point")) {
		  if(lightIdx < S.lightCount){
			setLight(&(S.lightList[lightIdx][0]),
					 atof(splitline[1].c_str()), //x
					 atof(splitline[2].c_str()), //y
					 atof(splitline[3].c_str()), //z
					 atof(splitline[4].c_str()), //r
					 atof(splitline[5].c_str()), //g
					 atof(splitline[6].c_str()), //b
					 false); //isDir
			++lightIdx;
		  }//if
		  else{
			  cout << "more lights than specified" << endl;
			  exit(1);
		  }//else  
        // add light to scene...
      }
      //attenuation const linear quadratic
      //  Sets the constant, linear and quadratic attenuations 
      //  (default 1,0,0) as in OpenGL.
      else if(!splitline[0].compare("attenuation")) {
			//dont care
      }
      //ambient r g b
      //  The global ambient color to be added for each object 
      //  (default is .2,.2,.2)
      else if(!splitline[0].compare("ambient")) {
		setVector3( S.ambient,
					atof(splitline[1].c_str()),  //r
					atof(splitline[2].c_str()),  //g
					atof(splitline[3].c_str())); //b
        /*The global ambient color to be added for each object (default is .2,.2,.2)*/
      }

      //diffuse r g b
      //  speciﬁes the diﬀuse color of the surface.
      else if(!splitline[0].compare("diffuse")) {
		setVector3( brdf[BRDF_KD_IDX],
					atof(splitline[1].c_str()),  //r
					atof(splitline[2].c_str()),  //g
					atof(splitline[3].c_str())); //b        
        // Update current properties
      }
      //specular r g b 
      //  speciﬁes the specular color of the surface.
      else if(!splitline[0].compare("specular")) {
		  setVector3( brdf[BRDF_KS_IDX],
					atof(splitline[1].c_str()),  //r
					atof(splitline[2].c_str()),  //g
					atof(splitline[3].c_str())); //b        
        // Update current properties
      }
      //shininess s
      //  speciﬁes the shininess of the surface.
      else if(!splitline[0].compare("shininess")) {
          brdf[BRDF_SP_IDX] = atof(splitline[1].c_str());
      }
      //emission r g b
      //  gives the emissive color of the surface.
      else if(!splitline[0].compare("emission")) {
        setVector3( brdf[BRDF_KE_IDX],
					atof(splitline[1].c_str()),  //r
					atof(splitline[2].c_str()),  //g
					atof(splitline[3].c_str())); //b        
        // Update current properties
      } else if(!splitline[0].compare("aa")) {
        S.aaDepth = atof(splitline[1].c_str());
        S.aaJitter = atof(splitline[2].c_str());
        
        cout << " ---Anti-aliasing flag turned on:" << endl;
						
        // Update current properties
      } else {
        std::cerr << "Unknown command: " << splitline[0] << std::endl;
      }
    }

    inpfile.close();
    

    //cout << "light x" << S.lights[0].x << ", " <<  S.lights[1].x << endl;
    
    return S;
  }
  throw 5;

} // load scene

parsedScene::parsedScene(){
    width = 400;
    height = 300;
    reflectiondepth = 5;
	triangleCount = 0;
	lightCount = 0;
    
    aaJitter = 0.0; // 1.0
    aaDepth = 1.0; // 4.0
    // aa off by default
    
	setVector3(lookfrom, 0, 0, 1);
	setVector3(lookat, 0, 0, 0);
	setVector3(up_dir, 0, 1, 0);
    fov = 33; // in degrees
    
	setVector3(ambient, 0.2, 0.2, 0.2);
    
    triangleList = NULL;
	lightList = NULL;    
} //parsedScene()


