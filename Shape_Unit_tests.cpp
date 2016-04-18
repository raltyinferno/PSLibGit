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


TEST_CASE("Creating Circles", "[Circle]")
{
	Circle c1(inch(2));
	REQUIRE(c1.draw() == "newpath 0 0 144 0 360 arc closepath stroke \n");

	Circle c2(inch(-2));
	REQUIRE(c2.draw() == "newpath 0 0 -144 0 360 arc closepath stroke \n");
}

TEST_CASE("Creating Rectangles", "[Rectangle]")
{
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
	Scaler s1(2, &c1);

	REQUIRE(s1.draw() == "gsave 2 2 scale \n \tnewpath 0 0 144 0 360 arc closepath stroke \ngrestore \n");
}

TEST_CASE("Bounding Boxes", "[Bounding]") //needs reworking along with bounding boxes to work with position
{
	class Rectangle r1(inch(2), inch(4));
	REQUIRE(r1.bounds().xLeft == -144);
	REQUIRE(r1.bounds().xRight == 144);
	REQUIRE(r1.bounds().yTop == 72);
	REQUIRE(r1.bounds().yBottom == -72);

	Circle c1(inch(2));
	REQUIRE(c1.bounds().xLeft == -72);
	REQUIRE(c1.bounds().xRight == 72);
	REQUIRE(c1.bounds().yTop == 72);
	REQUIRE(c1.bounds().yBottom == -72);

	Square s1(inch(2));
	REQUIRE(s1.bounds().xLeft == -72);
	REQUIRE(s1.bounds().xRight == 72);
	REQUIRE(s1.bounds().yTop == 72);
	REQUIRE(s1.bounds().yBottom == -72);

}

TEST_CASE("Bounding Boxes-Translated", "[BBox-Translate]") //needs reworking along with bounding boxes to work with position
{
	//hypothetical document creation
	//document << setOrigin(inch(1),inch(1));
	class Rectangle r1(inch(2), inch(4));

	REQUIRE(r1.bounds().xLeft == -72);
	REQUIRE(r1.bounds().xRight == 216);
	REQUIRE(r1.bounds().yTop == 144);
	REQUIRE(r1.bounds().yBottom == 0);

}





TEST_CASE("Document Creation", "[Document]")
{
	/*
	Document d1("unit_test_document.ps");
	Document test("tester.ps");
	test << "gsave 45 rotate \n \tnewpath 0 0 144 0 360 arc closepath stroke \ngrestore \n";

	d1 << setOrigin(inch(2), inch(2));
	//Circle
	Circle c1(inch(2));
	Rotater r1(45, &c1);
	d1 << r1.draw();

	//d1.endPage();

	//REQUIRE(d1 == test);
	*/
}



