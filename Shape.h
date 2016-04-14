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


#endif