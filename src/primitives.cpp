#include "primitives.h"

/* utility function */
//vector
void vector3Add(Vector3 dst, constVector3 v1, constVector3 v2){	
	dst[0] = v1[0] + v2[0];
	dst[1] = v1[1] + v2[1];
	dst[2] = v1[2] + v2[2];
	dst[3] = 0;
} // vector add

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
	dst[0] = v1[0];
	dst[1] = v1[1];
	dst[2] = v1[2];
	dst[3] = 0;
} // copy

//triangle
bool intersectTriangle(){

} // triangle intersect test

//ray

//light

//aabb tree
