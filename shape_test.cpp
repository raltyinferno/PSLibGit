#include "Shape.h"
#include <iostream>
using std::cout;
using std::endl;

int main()
{
	cout << setOrigin(inch(2), 36) << endl;
	//Circle
	Circle c1(inch(3));
	Rotater r1(45,&c1);
	cout << r1.draw()<<endl;

	cout << endl;

	//Rectangle
	Rectangle rect1(inch(2), inch(3));
	cout << rect1.draw() << endl;
	Rotater r2(45, &rect1);
	cout << r2.draw() << endl << showPage();

	return 0;
}