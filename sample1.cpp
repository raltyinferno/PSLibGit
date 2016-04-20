#include "Shape.h"

int main()
{
	Document d1("sample1.ps");

	Triangle t1(inch(1));
	Scaler s1(2, 1, &t1);
	Rotater r1(45,&s1);

	d1 << setOrigin(inch(3), inch(3));
	d1 << r1.draw();

	d1.endPage();
	d1.print();
}
