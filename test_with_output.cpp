#include "Shape.h"
#include <iostream>
#include <iostream>
#include <fstream>



using std::cout;
using std::endl;

int main()
{
    std::ofstream outputFile;
    outputFile.open("shapeTest.ps");
    outputFile << "%!" << endl;
	outputFile << setOrigin(inch(2), 36) << endl;
	//Circle
	Circle c1(inch(3));
	Rotater r1(45,&c1);
	outputFile << r1.draw()<<endl;

	outputFile << endl;

	//Rectangle
	Rectangle rect1(inch(2), inch(3));
	outputFile << rect1.draw() << endl;
	Rotater r2(45, &rect1);
	outputFile << r2.draw() << endl << showPage();

    outputFile.close();


	return 0;
}
