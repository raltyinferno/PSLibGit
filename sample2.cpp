#include "Shape.h"
#include <iostream>
using std::cout;
using std::endl;

int main()
{
	Document d1("document_test.ps");
	//d1 << setOrigin(inch(3), inch(3));
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

	//Layered
	d1 << setOrigin(inch(3), inch(3));
	Rotater r5(90, &p1);
	Layered l1 = { &c1,&squa1,&p1,&tri1};
	Rotater r6(90, &l1);

	d1 << setOrigin(inch(1), inch(6));
	Layered l2 = { &l1,&r6 };
	d1 << l1.draw();
	d1 << l2.draw();

	//Spacer
	Spacer sp1(inch(.5), inch(1));

	//Horizontal
	Horizontal h1 = { &c1,&squa1,&p1,&tri1 };
	Horizontal h2 = { &l1 ,&l1 ,&sp1 ,&l1 ,&l1 };
	d1 << setOrigin(inch(-3), inch(-4));
	d1 << h2.draw();

	//Vertical
	Vertical v1 = { &l1 ,&l1 ,&l1 ,&l1 ,&l1 };
	Vertical v2 = { &c1 ,&c1 ,&c1 ,&c1 ,&c1 };
	Scaler s3(.5, 2, &h2);
	Vertical v3 = { &h1,&h1 };
	d1 << tri1.draw();
	d1 << v3.draw();
	Rotater r70(90, &tri1);
	d1 << r70.draw();

	d1.endPage();

	d1 << setOrigin(inch(3), inch(7));

	d1 << tri1.draw();//drawn at origin


	Nice n2;
	Scaler s57(.5,.5, &n2);
	Horizontal h69 = { &s57, &p1, &s57 };
	Vertical v20 = { &h69, &l1, &h69, &l1};
	d1 << v20.draw();

	d1.endPage();
	d1.print();
	return 0;
}
