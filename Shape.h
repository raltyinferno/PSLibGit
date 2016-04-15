#pragma once

#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

#include <sstream>
#include <iostream>
#include <fstream>
using std::cout;
using std::endl;
using std::string;
using std::ostringstream;
using std::ofstream;

////////////////////////////
//General Library Functions

//to convert from standard postscript units to inches
double inch(double unit)
{
	return unit * 72;
}

//to actually print page once all desired shapes have been drawn
string showPage()
{
	return "showpage ";
}

//to translate
string setOrigin(int x, int y)
{
	ostringstream xcon, ycon;
	xcon << x;
	ycon << y;
	string origin = (xcon.str() + " " + ycon.str() + " " + "translate ");
	return origin;
}

//to output to a postscript file
//Adeline or Trace you were planning on doing this one right?

class Document
{
public:
	Document(string docName)
	{
		file.open(docName.c_str());
	}
	void print()
	{
		file.close();
	}
	void endPage()
	{
		file << "showpage \n";
	}
	Document & operator <<(const string & str)
	{
		this->file << str << endl;
		return *this;
	}
private:
	ofstream file;
};

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
	struct point
	{
		point(double inp_x, double inp_y):x(inp_x),y(inp_y)
		{}
		double x;
		double y;
	};
	//Constructor
	virtual ~Shape() {}
	//Methods
	virtual string draw() = 0;
	virtual point center() = 0;
};

class Decorator : public Shape
{
public:
	Decorator() {}
	virtual ~Decorator() {}
	virtual string draw() = 0;
	virtual point center() = 0;
};

class CompoundShape : public Shape
{
public:
	CompoundShape() {}
	virtual ~CompoundShape() {}
	virtual string draw() = 0;
	virtual point center() = 0;
};

/////////////////////////////
//Basic Shape Classes
class Circle : public Shape
{
public:
	Circle(double rad) :radi(rad)
	{
		ostringstream converter;
		converter << rad;
		radius = converter.str();
		middle = converter.str() +" " + converter.str();
	}
	string draw()
	{
		return  "newpath "+middle+" " +radius +" 0 360 arc closepath stroke \n";
	}
	point center()
	{
		point cent(radi, radi);
		return cent;
	}
	~Circle() {}
private:
	double radi;
	string radius;
	string middle;
};

class Square : public Shape
{
public:
	Square(double side)
	{}
	string draw()
	{}
	point center()
	{}
	~Square() {}
private:
	string side;
};

class Rectangle : public Shape
{
public:
	Rectangle(double in_height, double in_width) : wdth(in_width), hght(in_height)
	{
		ostringstream converterH;
		converterH << in_height;

		ostringstream converterW;
		converterW << in_width;

		height = converterH.str();
		width = converterW.str();

		//bounding box set-up here.
	}
	string draw()
	{
		string leftside = "0 " + height + " rlineto ";
		string topside = width + " 0 rlineto ";
		string rightside = "0 -" + height + " rlineto ";

		//temporary auto-moveto to point 144 144 until implementation is finalized.
		return " newpath 144 144 moveto " + leftside + topside + rightside + "closepath stroke \n";
	}
	point center()
	{
		point cent(wdth / 2, hght / 2);
		return cent;
	}
	~Rectangle() {}
private:
	double wdth;
	double hght;
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
	point center()
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
	point center()
	{}
	~Polygon() {}
private:
	int sides;
	string length;
};

class Spacer : public Shape
{
public:
	Spacer(double in_height, double in_width)
	{
		ostringstream converterH;
		converterH << in_height;

		ostringstream converterW;
		converterW << in_width;

		height = converterH.str();
		width = converterW.str();

		// As nothing is actually drawn, this should only
		// create a bounding box instead using height/width.
	}
	string draw()
	{
		return "";
	}
	point center()
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
	Rotater(int ang, Shape * shape): shp(shape)//figured it out, you have to pass a pointer to the base shape to be decorated
	{
		ostringstream converter;
		converter << ang;
		angle = converter.str();
		passed_shape = shape->draw();
	}	
	string draw()
	{
		string start = "gsave ";
		string rot = angle + " rotate ";
		string end = "grestore ";
		return start + rot + "\n \t" + passed_shape +end + "\n";
	}
	point center()
	{
		return shp->center();
	}
	~Rotater() {}
private:
	Shape * shp;
	string angle;
	string passed_shape;
};

class Scaler : public Decorator
{
public:
	Scaler(double scale, Shape * shape): shp(shape), scl(scale)
	{
		ostringstream convert;
		convert << scale; 
		scale_str = convert.str();
	}
	string draw()
	{
		return "gsave " + scale_str + " " + scale_str + " scale \n \t" + shp->draw() +"grestore \n";
	}
	point center()
	{
		point cent(shp->center().x*scl, shp->center().y*scl);
		return cent;
	}
	~Scaler() {}
private:
	Shape * shp;
	double scl;
	string scale_str;
};

///////////////////////////
//Compound Shape Classes


#endif