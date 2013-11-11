#include "primitives.h"

//****************************************************
// brdf.h. get the color of a certain pixel with given lights
//****************************************************


//given a point on the unit sphere, return the normal vector 
Vector getNormal(const Point &p){
    return Vector(p.x, p.y, p.z).normalize();
}
//given normalized light and normal vectors, return normal reflection vector
Vector getReflection(Vector l, Vector n){
    l = l.normalize();
    n = n.normalize(); 
    double dp = l.dotProduct(n); 
    Vector v =  (n * 2 * dp) - l; 
    return v.normalize(); 
    
    
}
//given point on sphere and location of light, return normal direction vector to light
Vector getLight(const Point &p, const Point &l){
    Vector v = l - p; 
    return v.normalize();
    
}

Color getBRDF(const Point &point, float radius, const Color &kd, const Color &ks, const Color &ke, int sp, const vector<Light> &lights) {
    
	  Vector  N = getNormal(point); 
	
	  Color baseColor = Color(0.0, 0.0, 0.0); 
	  //Color ambColor = Color(0.0, 0.0, 0.0); 
	
	  Light light;
	  Vector L, R;
	  size_t lightCount = lights.size();
	  for (size_t k = 0; k < lightCount; k++) {
		  light = lights[k];
		  if (light.directional) {
			  L = Vector(-light.x*radius, -light.y*radius, -light.z*radius).normalize(); 
		  } else {
			  L = getLight(point, Point(light.x*radius, light.y*radius, light.z*radius)); 
		  }
		  R = getReflection(L, N); 
		  /* obj.ambient * lights.ambient */
		  //ambColor += light.color; 
		  /* obj.diffuse * (L*N) * light.diffuse */
		  baseColor += kd * light.color * max(0.0, L.dotProduct(N)); 
		  /*specular*/
		  baseColor += ks * light.color * pow(max(0.0, R.dz), sp); 
	 
		  baseColor += ke;  // * ambColor; 
		  
		  throw 7;
		  
		  //baseColor += global ambient term
		  //cout << "need to addd global ambient term" << endl;
	 }
        
}
