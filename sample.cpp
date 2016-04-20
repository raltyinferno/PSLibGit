#include "Shape.h"

int main()
{
	Document d1("pretty_picture.ps");
	Circle c1(inch(1));
	Square s1(inch(2));
	Layered l1 = {&c1,&s1};
	Horizontal h1 = {&l1,&l1};
	Vertical v1 = {&h1, &h1};
	Vertical v2 = {&v1, &v1};
	Rotater r1(45,&v1);
	Triangle t1(inch(1));
	
	d1 << setOrigin(inch(3), inch(8));
	d1 << v2.draw();
	d1 << t1.draw();
	
	d1.endPage();
	d1.print();
}