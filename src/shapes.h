/*
 * shapes
*/


#include <iostream>
#include <math.h>
#include <vector>
#include "primitives.h"

#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

#define LARGE_NUM 1000000

class BRDF{
    public:
        Color kd, ks, ke;
        float kr; 
        int sp; 
    
    BRDF(); 
    BRDF(const Color&, const Color&, const Color&, float, int);
    BRDF clone() const;
};

class BoundingBox{
  public:
    float min_x, max_x;
    float min_y, max_y;
    float min_z, max_z; 
    
    BoundingBox(){};
    BoundingBox(float, float, float, float, float, float); 
    
    int getLongestAxis() const; 
    float getMidPoint(int) const; 
    bool intersect(const Ray&) const; 
};


class Shape{
  public:   
    BRDF brdf;
    virtual bool getIntersect(const Ray&, double*) const = 0; 
    virtual bool getIntersect(const Ray&) const = 0; 
    virtual Vector getNormal(const Point&) const = 0; 
    virtual BoundingBox getBB() const = 0; 
    
    bool isSphere;
    
};


class ShapeList{ //see AggregatePrimitive on website 
    public:
        vector<Shape*> allShapes; 
        bool checkIntersect(const Ray&, Point*, Shape*&, double) const;
        bool checkIntersect(const Ray&, double) const;
        
        BoundingBox getRootBox() const; 
        
        ShapeList() {}; 
        ShapeList(const vector<Shape*>&); 
};

class AABB_Node{
  public:
        BoundingBox bb;
        AABB_Node* children[2];  
        ShapeList containedShapes; 
        
        AABB_Node(const ShapeList&, int); 
        bool CollisionTest(const Ray&, Point*, Shape*&) const; 
};


class Sphere: public Shape{
    public:
        Point center;
        float radius;
        
        Matrix R;
        Matrix Rinv;
        Matrix S;
        Matrix Sinv;
        Matrix invertTrans;
        
    
        Sphere() {}; 
        Sphere(const Point&, float); 
        Sphere(const Point&, float, const Matrix&, const Matrix&, const Matrix&, const Matrix&); 
        
        
  
        bool getIntersect(const Ray&, double*) const; 
        bool getIntersect(const Ray&) const; 
        Vector getNormal(const Point&) const; 
        BoundingBox getBB() const; 
        
        Ray getLight(const Ray&) const;
        
      
};


class Triangle: public Shape{
    public:
        vector<Point> vertices; 
        Point v1, v2, v3; 
        Matrix RtimesSinv;
    
        Triangle() {};
        Triangle(const Point&, const Point&, const Point&, const Matrix&); 
        
        bool getIntersect(const Ray&, double*) const; 
        bool getIntersect(const Ray&) const; 
        Vector getNormal(const Point&) const; //no need for Point b/c all normals are same on triangle
        BoundingBox getBB() const; 

};







