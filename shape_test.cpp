#include "Shape.h"
#include <iostream>
using std::cout;
using std::endl;

int main()
{
	Document d1("document_test.ps");
	d1 << (setOrigin(inch(2), 36));
	//Circle
	Circle c1(inch(2));
	Rotater r1(45,&c1);;
	d1 << r1.draw();

	//Rectangle
	Rectangle rect1(inch(2), inch(3));
	Rotater r2(45, &rect1);
	d1 << r2.draw();

	// Square
	Square squa1(inch(1.5));
	Rotater r3(45, &squa1);
	d1 << r3.draw();

	// Triangle
	Triangle tri1(inch(2.3));
	Rotater r4(15, &tri1);
	d1 << r4.draw();

	// Polygon
	Polygon r5(5,inch(2));
    d1 << r5.draw();

	//Scaler
	Scaler s1(2, &r2);
	d1 << s1.draw();
	Scaler s2(0.7, &tri1);
	d1 << s2.draw();
	d1 << c1.draw();
	d1.endPage();
	d1.print();
	return 0;
}
