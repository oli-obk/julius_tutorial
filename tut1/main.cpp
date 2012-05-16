
#include <string>
#include <iostream>
#include <sstream>

int main(int argc, char** argv)
{
	std::string erster = argv[1];
	if(erster == "hallo") {
		std::cout << "tschuss" << std::endl;
		return 1;
	}
	std::string zweiter = argv[2];

	std::stringstream ss1(erster);
	int int1;

	if(ss1 >> int1)
	{
	}
	else
	{
		std::cout << "erster parameter ist kein int: " << erster << std::endl;
		return -1;
	}

	std::stringstream ss2(zweiter);
	int int2;
	if(!(ss2 >> int2)) {
		std::cout << "zweiter parameter ist kein int: " << zweiter << std::endl;
		return -1;
	}
	
	int ergebnis = int1 + int2;

	std::cout << int1 << " + " << int2 << " = " << ergebnis << std::endl;

	int zahl;
	std::cin >> zahl;
	std::cout << "Zahl: " << zahl << std::endl;

	return 0;
}
