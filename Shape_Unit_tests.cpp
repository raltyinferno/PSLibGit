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



