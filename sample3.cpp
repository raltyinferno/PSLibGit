#include "Shape.h"
#include <iostream>
using std::cout;
using std::endl;

int main()
{
	Document d1("sample3.ps");
	d1 << setOrigin(inch(3), inch(3));
	//Circle
	Circle c1(inch(.5));
	Rotater r1(45,&c1);;
	d1 << r1.draw();

	//Rectangle
	Rectangle rect1(inch(1), inch(.5));
	Rotater r2(45, &rect1);
	d1 << r2.draw();

	// Square
	Square squa1(inch(.5));
	Rotater r3(45, &squa1);
	d1 << r3.draw();

	// Nice
	Nice n1;
	d1 << n1.draw();

	// Triangle
	Triangle tri1(inch(.5));
	Rotater r4(15, &tri1);
	d1 << r4.draw();

	// Polygon
	Polygon p1(5,inch(1));
    d1 << p1.draw();

	//Scaler
	Scaler s1(2,2, &r2);
	d1 << s1.draw();
	Scaler s2(0.7,2, &tri1);
	d1 << s2.draw();
	d1 << c1.draw();

	d1.endPage();
	d1.print();
	return 0;
}
