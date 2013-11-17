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

#define LARGE_NUM 1000000

/* Type */
//index
#define RAY_ORIGIN_IDX 0
#define RAY_DIRECTION_IDX 4
#define LIGHT_SRC_IDX 0
#define LIGHT_COLOR_IDX 4
#define LIGHT_ISDIR_IDX 8
#define BRDF_KD_IDX 0
#define BRDF_KS_IDX 4
#define BRDF_KE_IDX 8
#define BRDF_KR_IDX 12
#define BRDF_SP_IDX 13
#define TRIANGLE_PT1_IDX 0
#define TRIANGLE_PT2_IDX 4
#define TRIANGLE_PT3_IDX 8
#define TRIANGLE_NORMAL_IDX 12

//type
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
void vector3Sub(Vector3 dst, constVector3 v1, constVector3 v2); // v1 - v2
void vector3Scale(Vector3 dst, constVector3 v1, const float scalar);
float vector3Dot(constVector3 v1, constVector3 v2);
void vector3Cross(Vector3 dst, constVector3 v1, constVector3 v2); // v1 x v2
void vector3Normalize(Vector3 dst, constVector3 v1);
void vector3Copy(Vector3 dst, constVector3 src);

//triangle
void setTriangle(Triangle triangle, constVector3 p1, constVector3 p2, constVector3 p3);
bool intersectTriangle(constTriangle triangle, constRay ray, float &rr); // check if intersect with the triangle
bool hasIntersect(const float[][16] triangleList, const int triangleCount, constRay ray, const float tmax); // only check if intersect with any triangle
bool nearestIntersect(const float[][16] triangleList, const int triangleCount, constRay ray, Vector3 intersectPt, int &triangleIdx, const float tmax); // check every possible triangle and return the nearest

//ray
void setRayByValue(Ray ray, float x, float y, float z, float dx, float dy, float dz);
void setRayByPoint(Ray ray, constVector3 origin, constVector3 p);
void setRayByVector(Ray ray, constVector3 origin, constVector3 direction);
void getReflection(Vector3 reflectionDirection, constVector3 rayDirection, constVector3 normal); // get reflection ray direction, normal should be normalized vector

//light
void setLight(Light light, float x, float y, float z, float r, float g, float b, bool isDir);

//brdf
void brdfCopy(Brdf dst, constBrdf src);

//aabb tree

#endif
