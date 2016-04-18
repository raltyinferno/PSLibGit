#ifndef SHAPE_H_INCLUDED
#define SHAPE_H_INCLUDED

#include <sstream>
#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <vector>
#include <initializer_list>


using std::cout;
using std::endl;
using std::string;
using std::ostringstream;
using std::ofstream;
using std::vector;
using std::initializer_list;

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
		return  "newpath 0 0 " +radius +" 0 360 arc closepath stroke \n";
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
	Square(double in_side) : edge(in_side)
	{
		ostringstream converterS,convert;
		converterS << in_side;

		side = converterS.str();
		double origin_offset = in_side / 2;
		convert << "-" << origin_offset;
		origin = convert.str()+" " + convert.str();
		// bounding box here
	}
	string draw()
	{
		string leftSide = "0 " + side + " rlineto ";
		string topSide = side + " 0 rlineto ";
		string rightSide = "0 -" + side + " rlineto ";

		// temporary moveto point 400 250
		return "newpath " +origin+" moveto " + leftSide + topSide + rightSide + "closepath stroke \n";
	}
	point center()
	{
		point cent(edge / 2, edge / 2);
		return cent;
	}
	~Square() {}
private:
	double edge;
	string origin;
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
	Triangle(double in_side) : edge(in_side)
	{
		height = (in_side / 2)*sqrt(3);
		halfSide = in_side / 2;

		hght = std::to_string(height);
		halfS = std::to_string(halfSide);

		// bounding box here
	}
	string draw()
	{
		string leftSlant = halfS + " " + hght + " rlineto ";
		string rightSlant = halfS + " -" + hght + " rlineto ";

		// temporary moveto point 350 250
		return " newpath 350 250 moveto " + leftSlant + rightSlant + "closepath stroke \n";
	}
	point center()
	{
		point cent((sqrt(3) / 6)*edge, edge / 2);
		return cent;
	}
	~Triangle() {}
private:
	double edge;
	double halfSide;
	double height;
	string hght;
	string halfS;
};

class Polygon : public Shape
{
public:
	Polygon(int sides, double length) : numSides(sides), myLength(length)
	{
	    //calculate the width and height
	    double pi = 3.14159;
        if (sides%2 == 1)
        {
            double step1 = sin((pi*(sides-1))/(2*sides));
            double step2 = sin(pi/sides);
            double step3 = 1+(cos(pi/sides));
            width = length * (step1/step2);
            height = length * (step3/(2*step2));
        }

        else if (sides%4 == 0)
        {
            double step1 = cos(pi/sides);
            double step2 = sin(pi/sides);
            width = length * (step1/step2);
            height = length * (step1/step2);
        }
        else
        {
            double step1 = cos(pi/sides);
            double step2 = sin(pi/sides);
            width = length * (1/step2);
            height = length * (step1/step2);
        }

	}
	string draw()
	{
        string drawPolygon = "";
        drawPolygon += "0.5 setlinewidth";
        drawPolygon += '\n';

        double divideBy = 3.14159;
        //draw the sides of the polygon
        for (int i=0; i<numSides; ++i)
        {
            std::ostringstream outo;
            string outs;
            double step1 = sin((((2*i)+1)*divideBy)/numSides);
            double step2 = sin(divideBy/numSides);
            double step3 = cos((((2*i)+1)*divideBy)/numSides);
            double xcord = (myLength/2) * (step1/step2);
            double ycord = -(myLength/2) * (step3/step2);

            outo << xcord;
            outo << " ";
            outs = outo.str();
            drawPolygon += outs;

            outo.str("");
            outo << ycord;
            if (i == 0)
            {
                outo << " newpath moveto";
            }
            else
            {
                outo << " lineto";
            }

            outs = outo.str();
            drawPolygon += outs;
            drawPolygon += '\n';

        }

        drawPolygon += "closepath";
        drawPolygon += '\n';
        drawPolygon += "0 setgray";
        drawPolygon += '\n';
        drawPolygon += "stroke";
        drawPolygon += '\n';
        return drawPolygon;

	}
	point center()
	{
        point cent(0,0);
		return cent;

	}
	~Polygon() {}
private:
	int numSides;
	double myLength;
	double height;
	double width;
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

class Layered : public CompoundShape
{
public:
	Layered(initializer_list<Shape*> init_list) : shapes(init_list) {}
	string draw()
	{
		string draw_str;
		for (Shape* & shape : shapes)
		{
			draw_str += shape->draw();
		}
		return draw_str;
	}
	point center()
	{
		point cent(0, 0);
		return cent;
	}
	~Layered() {}
private:

	vector<Shape*> shapes;
};

#endif
