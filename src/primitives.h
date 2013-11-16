//****************************************************
// primitives.h
// Contains:
// - Point
// - Ray
// - Vector
// - Light
// - Color
// - Camera 
// - Triangle
// - AABB Tree?
//****************************************************

#ifndef LIGHTS_H
#define LIGHTS_H

#include <cstdlib>
#include <cmath>

using namespace std;

/* Type */
typedef float Vector3[4]; // [x, y, z, dummy]
typedef const float constVector3[4];
typedef float Color[4]; // [r, g, b, dummy]
typedef const float constColor[4];
typedef float Ray[8]; // [Vector3[origin], Vector3[direction]]
typedef const float constRay[8];
typedef float Light[12]; // [Vector3[source] , Color[color], isDirectional, dummy, dummy, dummy]
typedef const float constLight[12];
typedef float Brdf[16]; // [Color[kd], Color[ks], Color[ke], kr, sp, dummy, dummy]
typedef const float constBrdf[16];
typedef float Triangle[16]; // [Vector3[pt1], Vector3[pt2], Vector3[pt3], Vector3[normal]]
typedef const float constTriangle[16];

/* utility function */
//vector
void vector3Add(Vector3 dst, constVector3 v1, constVector3 v2);
void vector3Sub(Vector3 dst, constVector3 v1, constVector3 v2);
void vector3Scale(Vector3 dst, constVector3 v1, const float scalar);
float vector3Dot(constVector3 v1, constVector3 v2);
void vector3Cross(Vector3 dst, constVector3 v1, constVector3 v2);
void vector3Normalize(Vector3 dst, constVector3 v1);
void vector3Copy(Vector3 dst, constVector3 src);

//triangle
bool intersectTriangle();

//ray

//light

//aabb tree

#endif
