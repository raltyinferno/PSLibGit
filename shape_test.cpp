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

	//Scaler
	Scaler s1(2, &r2);
	d1 << s1.draw();
	d1 << c1.draw();
	d1.endPage();
	d1.print();
	return 0;
}