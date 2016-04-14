#include "Shape.h"
#include <iostream>
using std::cout;
using std::endl;

int main()
{
	Circle c1(inch(3));
	Rotater r1(45,&c1);
	cout << r1.draw()<<endl;
	cout << "program ran" << endl;
	return 0;
}