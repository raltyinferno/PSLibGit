#define CATCH_CONFIG_MAIN  // We want Catch to write function main
#include "catch.hpp"       // For the "Catch" unit-testing framework
#include "Shape.h"

// ***** Test Cases *****


TEST_CASE("Inch Conversion Tests", "[Inch]")
{
	REQUIRE(inch(0) == 0);
	REQUIRE(inch(2) == 144);
	REQUIRE(inch(1.5) == 108);
}

TEST_CASE("Origin Translations", "[Translate]")
{
	REQUIRE(setOrigin(inch(2), inch(2)) == "144 144 translate ");
	REQUIRE(setOrigin(inch(0), inch(0)) == "0 0 translate ");
	REQUIRE(setOrigin(inch(-3), inch(20)) == "-216 1440 translate ");
}


TEST_CASE("Creating Shapes", "[Shapes]")
{
	Circle c1(inch(2));
	REQUIRE(c1.draw() == "newpath 0 0 144 0 360 arc closepath stroke \n");

	Circle c2(inch(-2));
	REQUIRE(c2.draw() == "newpath 0 0 -144 0 360 arc closepath stroke \n");

	class Rectangle r1(inch(2), inch(4));
	REQUIRE(r1.draw() == " newpath -144 -72 moveto 0 144 rlineto 288 0 rlineto 0 -144 rlineto closepath stroke \n");
}

TEST_CASE("Rotating Shapes", "[Rotate]")
{
	Circle c1(inch(2));
	Rotater r1(45, &c1);

	REQUIRE(r1.draw() == "gsave 45 rotate \n \tnewpath 0 0 144 0 360 arc closepath stroke \ngrestore \n");
}

TEST_CASE("Scaling Shapes", "[Scale]")
{
	Circle c1(inch(2));
	Scaler s1(2,2, &c1);

	REQUIRE(s1.draw() == "gsave 2.000000 2.000000 scale \n \tnewpath 0 0 144 0 360 arc closepath stroke \ngrestore \n");
}

TEST_CASE("Bounding Boxes", "[Bounding]") //needs reworking along with bounding boxes to work with position
{
	class Rectangle r1(inch(2), inch(4));
	REQUIRE(r1.bounds().xLeft == 144);
	REQUIRE(r1.bounds().xRight == 144);
	REQUIRE(r1.bounds().yTop == 72);
	REQUIRE(r1.bounds().yBottom == 72);

	Circle c1(inch(2));
	REQUIRE(c1.bounds().xLeft == 144);
	REQUIRE(c1.bounds().xRight == 144);
	REQUIRE(c1.bounds().yTop == 144);
	REQUIRE(c1.bounds().yBottom == 144);

	Square s1(inch(2));
	REQUIRE(s1.bounds().xLeft == 72);
	REQUIRE(s1.bounds().xRight == 72);
	REQUIRE(s1.bounds().yTop == 72);
	REQUIRE(s1.bounds().yBottom == 72);

}


TEST_CASE("Document Creation", "[Document]")
{
	Document d1("unit_test_document.ps");
	Document d2("unit_test_document.ps");
	Document d3("unit_test_document.ps");

	//Circle
	Circle c1(inch(2));
	Rotater r1(45, &c1);
	d1 << r1.draw();
	REQUIRE(d1.getFileString() == r1.draw());

	Square s1(inch(2));
	class Rectangle rect1(inch(2), inch(4));

	//Horizontal
	Horizontal h1 = { &c1,&s1,&rect1,&rect1 };
	d2 << h1.draw();
	REQUIRE(d2.getFileString() == h1.draw());

	//Vertical
	Vertical v1 = { &c1,&rect1,&s1,&rect1 };
	d3 << v1.draw();
	REQUIRE(d3.getFileString() == v1.draw());
}



