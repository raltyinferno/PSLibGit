#pragma once

#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

#include <sstream>
#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::ostringstream;

////////////////////////////
//General Library Functions

//to convert from standard postscript units to inches
double inch(double unit)
{
	return unit * 72;
}

//to actually print page once all desired shapes have been drawn
string showPage(string ps_script)
{
	return ps_script + " showpage";
}

//to output to a postscript file
//Adeline or Trace you were planning on doing this one right?

///////////////////
//Abstract Classes
class Shape
{
	struct BoundingBox
	{
		float xTop;
		float xBottom;
		float yTop;
		float yBottom;
	};
public:
	//Constructor
	virtual ~Shape() {}
	//Methods
	virtual string draw() = 0;
};

class Decorator : public Shape
{
public:
	Decorator() {}
	~Decorator() {}
	virtual string draw() = 0;
};


/////////////////////////////
//Basic Shape Classes
class Circle : public Shape
{
public:
	Circle(double rad)
	{
		ostringstream converter;
		converter << rad;
		radius = converter.str();
		center = converter.str() +" " + converter.str();
	}
	string draw()
	{
		return  "newpath "+center+" " +radius +" 0 360 arc closepath stroke ";
	}
	~Circle() {}
private:
	string radius;
	string center;
};

class Square : public Shape
{
public:
	Square(double side)
	{}
	string draw()
	{}
	~Square() {}
private:
	string side;
	string center;
};

class Rectangle : public Shape
{
public:
	Rectangle(double height, double width)
	{}
	string draw()
	{}
	~Rectangle() {}
private:
	string height;
	string width;
};

class Triangle : public Shape
{
public:
	Triangle(double side)
	{}
	string draw()
	{}
	~Triangle() {}
private:
	string side;
};

class Polygon : public Shape
{
public:
	Polygon(int sides, double length)
	{}
	string draw()
	{}
	~Polygon() {}
private:
	int sides;
	string length;
};

class Spacer : public Shape
{
public:
	Spacer(double height, double width)
	{}
	string draw()
	{}
	~Spacer() {}
private:
	string height;
	string width;
};

////////////////////////////////
//Decorator Classes
class Rotater : public Decorator
{
public:
	Rotater(int ang, Shape * shape)//figured it out, you have to pass a pointer to the base shape to be decorated
	{
		ostringstream converter;
		converter << ang;
		angle = converter.str();
		passed_shape = shape->draw();
	}	
	string draw()
	{
		string start = " gsave ";
		string rot = angle + " rotate ";
		string end = "grestore ";
		return start + rot + passed_shape + end;
	}
	~Rotater() {}
private:
	string angle;
	string passed_shape;
};

class Scaler : public Decorator
{
public:
	Scaler(double scale, Shape * shape)
	{}
	string draw()
	{}
	~Scaler() {}
private:
	string scale;};
#endif