#include "Shape.h"
#include <iostream>
using std::cout;
using std::endl;

int main()
{
	Document d1("sample5.ps");
	d1 << setOrigin(inch(3), inch(3));
    //Circle
	Circle c1(inch(.5));
	Square squa1(inch(.5));
    Nice n1;
    Scaler s1(.5, .5, &n1);
    Triangle tri1(inch(.5));
    Horizontal h1 = { &c1,&squa1,&s1,&tri1 };

	d1 << h1.draw();

	d1.endPage();
	d1.print();
	return 0;
}
