#pragma once

#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

//#include <string>
#include <sstream>
#include <iostream>
using std::cout;
using std::endl;
using std::string;
using std::ostringstream;

double inch(double unit)
{
	return unit * 72;
}

class Shape
{
	/********************Variables*********************/

public:
	struct BoundingBox 
	{
		float xTop;
		float xBottom;
		float yTop;
		float yBottom;
	};

	virtual string draw() = 0;

	virtual ~Shape() {}

private:
	


	/*********************Function Constructors**************************/


};

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
		return  "newpath "+center+" " +radius +" 0 360 arc closepath stroke";
	}
	~Circle() {}
private:
	string radius;
	string center;
};

class Decorator : public Shape
{
public:
	Decorator() {}
	~Decorator() {}
	virtual string draw() = 0;
};
class Rotateor : public Decorator
{
public:
	Rotateor(int ang, const Shape & shp)
	{
		ostringstream converter;
		converter << angle;
		angle = converter.str();
		passed_shape = shp.draw();
	}
	~Rotateor() {}
	string draw()
	{
		string start = " gsave rotate ";
		string rot = " rotate " + angle +" ";
		string end = " grestore ";
		return start + rot + passed_shape + end;
	}

private:
	string angle;
	string passed_shape;
};
#endif