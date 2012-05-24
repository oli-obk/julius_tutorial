
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

//using namespace std;
/*
int= Zahl (32bit: -2mio bis +2mio, 64bit: -9223372036854775808 bis +9223372036854775808)
char= einstelliger character (zeichen)
char*= array von char (rohstring im ram)
char**= array von array von char
array ist zusammenfassung von objekten vom gleichen typ im arbeitsspeicher
*/
int datenbankabfrage(){
}






int main(int argc, char** argv)
/*
int	---	rückgabetyp (in diesem fall für fehlermeldungen)
main	---	funktionsname (in diesem fall, die funktion, die den code enthält, der als erstes ausgefuehrt wird wenn das prog gestartet wird)
()	---	parameterliste für die funktion (in diesem fall:
			int argc	---	anzahl der parameter (programmname + parameter) die uebergeben werden
			char** argv	---	die parameter
	*/
{


std::string datenbankname = argv[1];   /* std::string erster-- definition eines strings mit namen erster, 
					als argv[1] -- 'argv' paramter der beim programmstart uebergeben wird, [zahl] -- paramternummer 0=programmname 1=erster parameter... 
					zur Sicherheit immer alles in strings konvertieren */
std::string durchlaufmodus = argv[2];
	
	if(!(durchlaufmodus == "random" && "bydate" && "straight")) {			//wenn erster paramter datei1 lautet
			std::cout << "kein zulaessiger modus, ZULAESSIGEMODI: random/bydate/straight" << std::endl;
			return -1;
		}
	}


	if(durchlaufmodus == "random") {
	}

	if(durchlaufmodus == "bydate") {
	}

	if(durchlaufmodus == "straight") {
	}








	std::stringstream ss1(auswahl);
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
	std::cout << "Bitte geb eine zahl ein: " << std::flush;
	std::cin >> zahl;
	std::cout << "Zahl: " << zahl << std::endl;

	return 0;
}
