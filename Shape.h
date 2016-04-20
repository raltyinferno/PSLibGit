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
using std::to_string;

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
		filestring << "showpage \n";
	}
	Document & operator <<(const string & str)
	{
		this->file << str << endl;
		this->filestring << str;
		return *this;
	}
	string getFileString()
	{
		return filestring.str();
	}
private:
	ofstream file;
	ostringstream filestring;
};

///////////////////
//Abstract Classes
class Shape
{
public:
	struct BoundingBox
	{
		BoundingBox(double x_right, double x_left, double y_top, double y_bot) :xRight(x_right), xLeft(x_left), yTop(y_top), yBottom(y_bot)
		{}
		float xRight;
		float xLeft;
		float yTop;
		float yBottom;
	};

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
	virtual BoundingBox bounds() = 0;
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
	BoundingBox bounds()
	{
		BoundingBox Bbox(radi,radi , radi, radi);
		return Bbox;
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
	BoundingBox bounds()
	{
		BoundingBox Bbox(edge/2, edge/2, edge/2, edge/2);
		return Bbox;
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


		ostringstream converterO_x;
		ostringstream converterO_y;

		double origin_x = in_width / 2;
		double origin_y = in_height / 2;
		converterO_x << origin_x;
		converterO_y << origin_y;
		origin = "-" + converterO_x.str() + " " + "-" + converterO_y.str();

		//bounding box set-up here.


	}
	string draw()
	{
		string leftside = "0 " + height + " rlineto ";
		string topside = width + " 0 rlineto ";
		string rightside = "0 -" + height + " rlineto ";

		//temporary auto-moveto to point 144 144 until implementation is finalized.
		return " newpath " + origin + " moveto " + leftside + topside + rightside + "closepath stroke \n";
	}
	point center()
	{
		point cent(wdth / 2, hght / 2);
		return cent;
	}
	BoundingBox bounds()
	{
		BoundingBox Bbox(wdth/2,wdth/2,hght/2,hght/2);
		return Bbox;
	}
	~Rectangle() {}
private:
	double wdth;
	double hght;
	string origin;
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

		hght = to_string(height);
		halfS = to_string(halfSide);

		// bounding box here
	}
	string draw()
	{
		string leftSlant = halfS + " " + hght + " rlineto ";
		string rightSlant = halfS + " -" + hght + " rlineto ";
		string origin_offset = "-" + to_string(edge / 2) + " -" + to_string(height/3);

		// temporary moveto point 350 250
		return " newpath " +origin_offset+ " moveto " + leftSlant + rightSlant + "closepath stroke \n";
	}
	point center()
	{
		point cent((sqrt(3) / 6)*edge, edge / 2);
		return cent;
	}
	BoundingBox bounds()
	{
		BoundingBox Bbox(halfSide, halfSide, height/2, height/2);
		return Bbox;
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
	    //formula for odd number of sides
        if (sides%2 == 1)
        {
            double step1 = sin((pi*(sides-1))/(2*sides));
            double step2 = sin(pi/sides);
            double step3 = 1+(cos(pi/sides));
            width = length * (step1/step2);
            height = length * (step3/(2*step2));
        }
        //formula for even number of sides that can be divided by four
        else if (sides%4 == 0)
        {
            double step1 = cos(pi/sides);
            double step2 = sin(pi/sides);
            width = length * (step1/step2);
            height = length * (step1/step2);
        }

        //formula for even number of sides that cannot be divided by four
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

        double pi = 3.14159;
        //draw the sides of the polygon
        for (int i=0; i<numSides; ++i)
        {
            std::ostringstream outo;
            string outs;
            double step1 = sin((((2*i)+1)*pi)/numSides);
            double step2 = sin(pi/numSides);
            double step3 = cos((((2*i)+1)*pi)/numSides);
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
	BoundingBox bounds()
	{
		BoundingBox Bbox(width/2, width/2, height/2, height/2);
		return Bbox;
	}
	~Polygon() {}
private:
	int numSides;
	double myLength;
	double height;
	double width;

	double smallest_x;
	double smallest_y;
	double greatest_x;
	double greatest_y;
};

class Nice : public Shape
{
public:
	string draw()
	{
		x1 = adjustX - 28 - 84.25;
		x2 = adjustX + 243 - 84.25;
		x3 = adjustX + 643 - 84.25;
		x4 = adjustX - 427 - 84.25;
		x5 = adjustX + 108 - 84.25;
		x6 = adjustX + 108 - 84.25;
		x7 = adjustX + 108 - 84.25;
		x8 = adjustX + 108 - 84.25;

		y1 = adjustY + 29 - 62;
		y2 = adjustY + 29 - 62;
		y3 = adjustY + 424 - 62;
		y4 = adjustY + 424 - 62;
		y5 = adjustY + 164 - 62;
		y6 = adjustY + 164 - 62;
		y7 = adjustY - 106 - 62;
		y8 = adjustY + 164 - 62;

		string curve1 = to_string(x1) + " " + to_string(y1) + " 117 14.5 -285 arc stroke"; // upmidleft
		string curve2 = to_string(x2) + " " + to_string(y2) + " 117 -255.5 -194.5 arc stroke"; // upmidrigt

		string curve3 = to_string(x3) + " " + to_string(y3) + " 700 208 217.3 arc stroke"; // left low
		string curve4 = to_string(x4) + " " + to_string(y4) + " 700 322.7 332 arc stroke"; // right low

		string curve5 = to_string(x5) + " " + to_string(y5) + " 108 220 257.5 arc stroke"; // lowmidleft
		string curve6 = to_string(x6) + " " + to_string(y6) + " 108 281.5 320 arc stroke"; // lomidright

		string curve7 = to_string(x7) + " " + to_string(y7) + " 108 78 102 arc stroke"; // lower overarc
		string curve8 = to_string(x8) + " " + to_string(y8) + " 108 -12 192 arc stroke"; // upper overarc

		string upMid = curve1 + "\n" + curve2 + "\n";
		string low = curve3 + "\n" + curve4 + "\n";
		string lowMid = curve5 + "\n" + curve6 + "\n";
		string overArc = curve7 + "\n" + curve8 + "\n";

		return "newpath \n" + upMid + low + lowMid + overArc + "closepath \n";
	}
	point center()
	{
		point cent(adjustX, adjustY);
		return cent;
	}
	BoundingBox bounds()
	{
		BoundingBox Bbox(110,109,136, 140);
		return Bbox;
	}
	~Nice() {}
private:
	double adjustX= -23, adjustY=-64;
	double x1, x2, x3, x4, x5, x6, x7, x8;
	double y1, y2, y3, y4, y5, y6, y7, y8;
};

class Spacer : public Shape
{
public:
	Spacer(double in_height, double in_width) : wdth(in_width), hght(in_height)
	{
		ostringstream converterH;
		converterH << in_height;

		ostringstream converterW;
		converterW << in_width;

		height = converterH.str();
		width = converterW.str();

		ostringstream converterO_x;
		ostringstream converterO_y;

		double origin_x = in_width / 2;
		double origin_y = in_height / 2;
		converterO_x << origin_x;
		converterO_y << origin_y;
		origin = "-" + converterO_x.str() + " " + "-" + converterO_y.str();

		// As nothing is actually drawn, this should only
		// create a bounding box instead using height/width.


	}
	string draw()
	{
		return "";
	}
	point center()
	{
		point cent(wdth / 2, hght / 2);
		return cent;
	}
	BoundingBox bounds()
	{
		BoundingBox Bbox(wdth / 2, wdth / 2, hght / 2, hght / 2);
		return Bbox;
	}
	~Spacer() {}
private:
	double wdth;
	double hght;
	string origin;
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
	BoundingBox bounds()
	{
		BoundingBox Bbox(0, 0, 0, 0);
		return Bbox;
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
	Scaler(double scalex, double scaley, Shape * shape): shp(shape), sclx(scalex), scly(scaley)
	{
		scalex_str = to_string(sclx);
		scaley_str = to_string(scly);
	}
	string draw()
	{
		return "gsave " + scalex_str + " " + scaley_str + " scale \n \t" + shp->draw() +"grestore \n";
	}
	point center()
	{
		point cent(shp->center().x*sclx, shp->center().y*scly);
		return cent;
	}
	BoundingBox bounds()
	{
		BoundingBox Bbox(shp->bounds().xRight * sclx, shp->bounds().xLeft * sclx, shp->bounds().yTop * scly, shp->bounds().yBottom * scly);
		return Bbox;
	}
	~Scaler() {}
private:
	Shape * shp;
	double sclx;
	double scly;
	string scalex_str;
	string scaley_str;
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
	BoundingBox bounds()
	{
		float smallest_x = shapes[0]->bounds().xLeft;
		float smallest_y = shapes[0]->bounds().yBottom;
		float greatest_x = shapes[0]->bounds().xRight;
		float greatest_y = shapes[0]->bounds().yTop;


		for (int i = 0; i < shapes.size(); i++)
		{
			if (shapes[i]->bounds().xLeft > smallest_x)
			{
				smallest_x = shapes[i]->bounds().xLeft;
			}
			if (shapes[i]->bounds().xRight > greatest_x)
			{
				greatest_x = shapes[i]->bounds().xRight;
			}
			if (shapes[i]->bounds().yBottom > smallest_y)
			{
				smallest_y = shapes[i]->bounds().yBottom;
			}
			if (shapes[i]->bounds().yTop > greatest_y)
			{
				greatest_y = shapes[i]->bounds().yTop;
			}

		}

		BoundingBox Bbox(greatest_x,smallest_x,greatest_y,smallest_y);
		return Bbox;
	}
	~Layered() {}
private:

	vector<Shape*> shapes;
};

class Horizontal : public Shape
{
public:
	Horizontal(initializer_list<Shape*> init_list) : shapes(init_list) 
	{
		
	}

	string draw()
	{
		double offset = -(shapes[0]->bounds().xLeft);
		offset += -(this->bounds().xLeft / 2);

		string draw_str = setOrigin(-(shapes[0]->bounds().xLeft),0);
		draw_str += setOrigin(-(this->bounds().xLeft / 2), 0);
		for (Shape* & shape: shapes)
		{
			draw_str+=setOrigin(shape->bounds().xLeft, 0);
			draw_str += shape->draw();
			draw_str += setOrigin(shape->bounds().xRight, 0);
			offset += shape->bounds().xLeft;
			offset += shape->bounds().xRight;
		}
		draw_str += setOrigin(-offset, 0);
		return draw_str;
	}
	point center()
	{
		point cent(0, 0);
		return cent;
	}
	BoundingBox bounds()
	{
		double left = 0, right = 0, top = shapes[0]->bounds().yTop, bottom = shapes[0]->bounds().yBottom;
		for (Shape* & shape : shapes)
		{
			left += shape->bounds().xLeft;
			right += shape->bounds().xRight;
			if (top < shape->bounds().yTop)
			{
				top = shape->bounds().yTop;
			}
			if (bottom < shape->bounds().yBottom)
			{
				bottom = shape->bounds().yBottom;
			}
		}
		BoundingBox Bbox(left, right, top, bottom);
		return Bbox;
	}

	~Horizontal() {}


private:
	vector<Shape*> shapes;
};

class Vertical : public Shape
{
public:
	Vertical(initializer_list<Shape*> init_list) : shapes(init_list) {}

	string draw()
	{
		double offset = (shapes[0]->bounds().yTop);
		offset += (this->bounds().yTop) / 2;
		string draw_str = setOrigin(0, (shapes[0]->bounds().yTop));
		draw_str += setOrigin(0, (this->bounds().yTop) / 2);
		for (Shape* & shape : shapes)
		{
			draw_str += setOrigin(0, -shape->bounds().yTop);
			draw_str += shape->draw();
			draw_str += setOrigin(0, -shape->bounds().yBottom);
			offset += -shape->bounds().yTop;
			offset += -shape->bounds().yBottom;
		}
		draw_str += setOrigin(0, -offset);
		return draw_str;
	}
	point center()
	{
		point cent(0, 0);
		return cent;
	}
	BoundingBox bounds()
	{
		double left = shapes[0]->bounds().xLeft, right = shapes[0]->bounds().xRight, top = 0, bottom = 0;
		for (Shape* & shape : shapes)
		{
			top += shape->bounds().yTop;
			bottom += shape->bounds().yBottom;
			if (shape->bounds().xLeft > left)
			{
				left = shape->bounds().xLeft;
			}
			if (shape->bounds().xRight > right)
			{
				right = shape->bounds().xRight;
			}
		}

		BoundingBox Bbox(right,left,top,bottom);
		return Bbox;
	}

	~Vertical() {}


private:
	vector<Shape*> shapes;
};
#endif
