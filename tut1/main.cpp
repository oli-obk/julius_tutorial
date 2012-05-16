
#include <string>
#include <iostream>
#include <sstream>

int main(int argc, char** argv)   /* int main--- main body der code enthaelt der ausgefuehrt wird,   
    (**parameter**)--int argc -anzahl der parameter die uebergeben werden ????????????
parameter definitionen	int= Zahl -2mio bis +2mio
			char= einstelliger character	*roh string im im ram	**arrey von arrey 	| arrey zusammenfassung von parametern im arbeitsspeicher
			

	*/
{
	std::string erster = argv[1];   /* std::string erster-- definition eines strings mit namen erster, 
					als argv[1] -- 'argv' paramter der beim programmstart uebergeben wird, [zahl] -- paramternummer 0=programmname 1=erster parameter... 
					zur Sicherheit immer alles in strings konvertieren */
	if(erster == "hallo") {		// if (abfrage) {code der ausgefuehrt wird wenn abfrage zutrifft }
		std::cout << "tschuss" << std::endl;	// std:cout-- 'Funktion zur Ausgabe an Konsole'   << "text" <<  std::endl; --'Abschliesen der Funktion zur Ausgabe
		return 1;				// return ZAHL;		programm beenden mit ZAHL: 0=
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
