#include "Shape.h"
#include <iostream>
using std::cout;
using std::endl;

int main()
{
	Document d1("sample4.ps");
	d1 << setOrigin(inch(3), inch(3));

	Circle c1(inch(.5));

	Scaler s1(.7,.7, &c1);
	Scaler s2(.5,.5, &c1);
	Scaler s3(.3,.3, &c1);
	Layered l1 = { &c1,&s1,&s2};
	Vertical v1 = { &l1,&l1,&l1,&l1 };
	d1 << v1.draw();


	d1.endPage();
	d1.print();
	return 0;
}
