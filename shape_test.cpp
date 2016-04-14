#include "Shape.h"
#include <iostream>
using std::cout;
using std::endl;

int main()
{
	//Circle
	Circle c1(inch(3));
	Rotater r1(45,&c1);
	cout << showPage(r1.draw())<<endl;

	cout << endl;

	//Rectangle
	Rectangle rect1(inch(2), inch(3));
	cout << showPage(rect1.draw()) << endl;
	Rotater r2(45, &rect1);
	cout << showPage(r2.draw());

	return 0;
}