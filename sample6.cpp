#include "Shape.h"
#include <iostream>
using std::cout;
using std::endl;

int main()
{
	Document d1("sample6.ps");
	d1 << setOrigin(inch(3), inch(3));
    //Circle
    Circle c1(inch(.5));
	Polygon p1(5,inch(1));
	Scaler s1(0.5,0.5, &p1);
	Rotater r3(45, &s1);
	Layered l2 = { &c1,&r3 };
	Square squa1(inch(.5));
	Horizontal h1 = { &l2,&squa1,&l2 };
	Vertical v1 = { &h1 ,&h1 ,&h1 ,&h1};

    d1 << v1.draw();


	d1.endPage();
	d1.print();
	return 0;
}
