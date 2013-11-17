#include "primitives.h"

/* utility function */
//vector
void setVector3(Vector3 dst, float x, float y, float z){
	dst[0] = x;
	dst[1] = y;
	dst[2] = z;
	dst[3] = 0;
} // set vector

void vector3Add(Vector3 dst, constVector3 v1, constVector3 v2){	
	dst[0] = v1[0] + v2[0];
	dst[1] = v1[1] + v2[1];
	dst[2] = v1[2] + v2[2];
	dst[3] = 0;
} // vector add

// v1 - v2
void vector3Sub(Vector3 dst, constVector3 v1, constVector3 v2){
	dst[0] = v1[0] - v2[0];
	dst[1] = v1[1] - v2[1];
	dst[2] = v1[2] - v2[2];
	dst[3] = 0;
} // vector subtract

void vector3Scale(Vector3 dst, constVector3 v1, const float scalar){
	dst[0] = v1[0] * scalar;
	dst[1] = v1[1] * scalar;
	dst[2] = v1[2] * scalar;
	dst[3] = 0;
} // vector scale

float vector3Dot(constVector3 v1, constVector3 v2){
	return (v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2]); 
} // dot product

// v1 x v2
void vector3Cross(Vector3 dst, constVector3 v1, constVector3 v2){
	Vector3 tmp; // incase dst == v1 or dst == v2
	tmp[0] = v1[1] * v2[2] - v1[2] * v2[1]; // y1 * z2 - z1 * y2
	tmp[1] = v1[2] * v2[0] - v1[0] * v2[2]; // z1 * x2 - x1 * z2
	tmp[2] = v1[0] * v2[1] - v1[1] * v2[0]; // x1 * y2 - y1 * x2

	dst[0] = tmp[0];
	dst[1] = tmp[1];
	dst[2] = tmp[2];
	dst[3] = 0;
} // cross product

void vector3Normalize(Vector3 dst, constVector3 v1){
	float mag = sqrt(vector3Dot(v1, v1));

	dst[0] = v1[0] / mag;
	dst[1] = v1[1] / mag;
	dst[2] = v1[2] / mag;
	dst[3] = 0;
} // normalize

void vector3Copy(Vector3 dst, constVector3 src){
	dst[0] = src[0];
	dst[1] = src[1];
	dst[2] = src[2];
	dst[3] = 0;
} // copy

void colorMultiply(Color dst, constColor c1, constColor c2){
	dst[0] = c1[0] * c2[0];
	dst[1] = c1[1] * c2[1];
	dst[2] = c1[2] * c2[2];
	dst[3] = 0;
} // color multiply

//triangle
void setTriangle(Triangle triangle, constVector3 p1, constVector3 p2, constVector3 p3){
	Vector3 v1;
	Vector3 v2;
	
	vector3Sub(v1, p1, p3); // v1 = p1 - p3
	vector3Sub(v2, p2, p3); // v2 = p2 - p3
	vector3Cross(&(triangle[TRIANGLE_NORMAL_IDX]), v1, v2); // normal = v1 x v2, normalize
	vector3Normalize(&(triangle[TRIANGLE_NORMAL_IDX]), &(triangle[TRIANGLE_NORMAL_IDX]));

	vector3Copy(&(triangle[TRIANGLE_PT1_IDX]), p1);
	vector3Copy(&(triangle[TRIANGLE_PT2_IDX]), p2);
	vector3Copy(&(triangle[TRIANGLE_PT3_IDX]), p3);
} // set triangle

// check if intersect with the triangle
// http://geomalgorithms.com/a06-_intersect-2.html
bool intersectTriangle(constTriangle triangle, constRay ray, float &rr){
	Vector3 u, v, w, w0, intersect;
	float nDotV = vector3Dot(&(triangle[TRIANGLE_NORMAL_IDX]), &(ray[RAY_DIRECTION_IDX]));

	if(nDotV == 0) return false; // ray parallel to triangle

	vector3Sub(u, &(triangle[TRIANGLE_PT2_IDX]), &(triangle[TRIANGLE_PT1_IDX]));
	vector3Sub(v, &(triangle[TRIANGLE_PT3_IDX]), &(triangle[TRIANGLE_PT1_IDX]));
	vector3Sub(w0, &(ray[RAY_ORIGIN_IDX]), &(triangle[TRIANGLE_PT1_IDX]));

	float nDotW0 = -vector3Dot(&(triangle[TRIANGLE_NORMAL_IDX]), w0);
	float r = nDotW0 / nDotV;

	if(r < 0) return false; // ray goes away from triangle

	// intersect = ray.origin + r * ray.direction
	vector3Scale(intersect, &(ray[RAY_DIRECTION_IDX]), r);
	vector3Add(intersect, intersect, &(ray[RAY_ORIGIN_IDX]));

	// check intersect in triangle
	vector3Sub(w, intersect, &(triangle[TRIANGLE_PT1_IDX]));
	float uu = vector3Dot(u,u);
    float uv = vector3Dot(u,v);
    float vv = vector3Dot(v,v);
    float wu = vector3Dot(w,u);
    float wv = vector3Dot(w,v);
    float D = uv * uv - uu * vv;
	// get and test parametric coords
    float s = (uv * wv - vv * wu) / D;
    float t = (uv * wu - uu * wv) / D;
    if (s < 0.0 || t < 0.0 || (s + t) > 1.0) return false; // intersect is outside triangle        

	rr = r;
    return true;                       // intersect is in triangle
} // triangle intersect test

// only check if intersect with any triangle
bool hasIntersect(float(*triangleList)[16] , const int triangleCount, constRay ray, const float tmax){
	float t = -1;
	bool intersect;

    for(int i = 0; i < triangleCount; i++){
       intersect = intersectTriangle(&(triangleList[i][0]), ray, t);
       if (intersect && t < tmax) return true; //there is an intersection              
    } // for
    
    return false;
} // has intersect

// check every possible triangle and return the nearest
bool nearestIntersect(float(*triangleList)[16] , const int triangleCount, constRay ray, Vector3 intersectPt, int &triangleIdx, const float tmax){
	float t = -1;
    float min = LARGE_NUM;
	bool intersect;

	for(int i = 0; i < triangleCount; i++){
        intersect = intersectTriangle(&(triangleList[i][0]), ray, t);
        if (intersect && t < min){
            min = t;
            triangleIdx = i;
        } // if
    } // for

    if(min == LARGE_NUM || min > tmax) return false; //no intersection

	// intersect point = ray.origin + r * ray.direction
	vector3Scale(intersectPt, &(ray[RAY_DIRECTION_IDX]), min);
	vector3Add(intersectPt, intersectPt, &(ray[RAY_ORIGIN_IDX]));

    return true; 
} // nearest intersect

//ray
void setRayByValue(Ray ray, float x, float y, float z, float dx, float dy, float dz){
	ray[RAY_ORIGIN_IDX + 0] = x;
	ray[RAY_ORIGIN_IDX + 1] = y;
	ray[RAY_ORIGIN_IDX + 2] = z;
	ray[RAY_ORIGIN_IDX + 3] = 0;

	ray[RAY_DIRECTION_IDX + 0] = dx;
	ray[RAY_DIRECTION_IDX + 1] = dy;
	ray[RAY_DIRECTION_IDX + 2] = dz;
	ray[RAY_DIRECTION_IDX + 3] = 0;
} // set ray by value

void setRayByPoint(Ray ray, constVector3 origin, constVector3 p){
	Vector3 dir;
	vector3Sub(dir, p, origin);
	vector3Copy(&(ray[RAY_ORIGIN_IDX]), origin);
	vector3Copy(&(ray[RAY_DIRECTION_IDX]), dir);
} // set ray by two point

void setRayByVector(Ray ray, constVector3 origin, constVector3 direction){
	vector3Copy(&(ray[RAY_ORIGIN_IDX]), origin);
	vector3Copy(&(ray[RAY_DIRECTION_IDX]), direction);
} // set ray by origin and direction

void getReflection(Vector3 reflectionDirection, constVector3 rayDirection, constVector3 normal){
	float dp = vector3Dot(rayDirection, normal); 

	// reflection = (normal * 2dp) - rayDirection
	vector3Scale(reflectionDirection, normal, 2 * dp);
	vector3Sub(reflectionDirection, reflectionDirection, rayDirection);
} // get reflection ray direction

//light
void setLight(Light light, float x, float y, float z, float r, float g, float b, bool isDir){
	light[LIGHT_SRC_IDX + 0] = x;
	light[LIGHT_SRC_IDX + 1] = y;
	light[LIGHT_SRC_IDX + 2] = z;
	light[LIGHT_SRC_IDX + 3] = 0;
	light[LIGHT_COLOR_IDX + 0] = r;
	light[LIGHT_COLOR_IDX + 1] = g;
	light[LIGHT_COLOR_IDX + 2] = b;
	light[LIGHT_COLOR_IDX + 3] = 0;
	light[LIGHT_ISDIR_IDX + 0] = isDir ? 1 : 0;
	light[LIGHT_ISDIR_IDX + 1] = 0;
	light[LIGHT_ISDIR_IDX + 2] = 0;
	light[LIGHT_ISDIR_IDX + 3] = 0;
} //set light

//brdf
void brdfCopy(Brdf dst, constBrdf src){
	vector3Copy(&(dst[BRDF_KD_IDX]), &(src[BRDF_KD_IDX]));
	vector3Copy(&(dst[BRDF_KS_IDX]), &(src[BRDF_KS_IDX]));
	vector3Copy(&(dst[BRDF_KE_IDX]), &(src[BRDF_KE_IDX]));
	vector3Copy(&(dst[BRDF_KR_IDX]), &(src[BRDF_KR_IDX]));
} // copy brdf

//aabb tree
