//****************************************************
// primitives.h
// Contains:
// - Point
// - Ray
// - Vector
// - Light
// - Color
// - Camera 
// - MatrixStack
// - Matrix 
//****************************************************

#ifndef LIGHTS_H
#define LIGHTS_H

#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;


//****************************************************
// CLASS DECLARATIONS AND CONSTRUCTORS 
//****************************************************
class Vector; 
class Point{ 
public:
    Point() {};
    Point(double, double, double); 

    double x, y, z;
    //Vector subtract(const Point&) const; 
    Point operator + (const Vector&) const; //position + direction = position 
    Point operator + (const Point&) const; // point addition; shortcut for camera's ray formula
    Point operator * (double) const; 
    Vector operator - (const Point&) const;  
    
    
    
};

    
    
class Vector{
 public:
    Vector() {};  
    Vector(double, double, double);
    Vector(const Point&); 
    Vector(const Point&, const Point&); 
    
    double dx, dy, dz;
    double mag;
    
    Vector normalize() const;
    double dotProduct(const Vector&) const;
    Vector negative() const;
    Vector crossProduct(const Vector&) const;
    
    //allow for scalar * and vector +
    Vector operator * (double) const;
    Vector operator + (const Vector&) const; 
    Vector operator - (const Vector&) const; 
    
    
};




class Ray{
public:
    Ray() {}; 
    Ray(double, double, double, double, double, double);
    Ray(const Point&, const Point&); 
    Ray(const Point&, const Vector&);

    Vector direction; 
    Point origin; 
   
    
};


/*
 *  Color class keeps track of r g b values, which are [0, 1]
 */ 
 class Color{
     public:
        Color() {};
        Color(double, double, double);
        
        double r, g, b;
        
        Color operator + (const Color&) const;  
        Color operator * (const Color&) const; 
        Color operator * (double) const; 
        void operator += (const Color&); 
        
        Color clone() const;
 };

/*
 *  Light class describes a light source that extends in all directions with rgb value from point x y z
 */ 

class Light {
  public:
    Light() {}; 
    Light (double, double, double, double, double, double, bool); 

    void initPos(double, double, double);
    void initRGB(double, double, double); 
    Color color; 
    Point source; 
    double x, y, z, r, g, b;
	bool directional;

};

class Matrix{
    public:
		double m[4][4]; 
    Matrix();
    
    // Instantiator shortcut for translation, scaling, or rotating (depends upon input char)
    Matrix(char, double, double, double, double); 
    
    Matrix operator * (const Matrix&) const; 
    Point operator * (const Point&) const;
    Vector operator * (const Vector&) const;
    Ray operator * (const Ray&) const;
    
    Matrix invert() const;
    void debug() const;
    Matrix clone() const;
    
    Vector vectorTimesM(const Vector&) const; 
};

class MatrixStack{
    public:
    MatrixStack(); 
    
    vector<Matrix> stack;
    vector<Matrix> stackT;
    vector<Matrix> stackS;
    vector<Matrix> stackR;
    Matrix product;
    Matrix productT; // product of all the T matrices
    Matrix productS;
    Matrix productR;
    
    void push(); 
    void pop();
    void addTransform(const Matrix&, char);
     
};







 
#endif
