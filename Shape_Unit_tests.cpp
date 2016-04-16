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


TEST_CASE("Creating Circles", "[Circle]")
{
	Circle c1(inch(2));
	REQUIRE(c1.draw() == "newpath 144 144 144 0 360 arc closepath stroke \n");
}

TEST_CASE("Rotating Shapes", "[Rotate]")
{
	Circle c1(inch(2));
	Rotater r1(45, &c1);

	REQUIRE(r1.draw() == "gsave 45 rotate \n \tnewpath 144 144 144 0 360 arc closepath stroke \ngrestore \n");
}



