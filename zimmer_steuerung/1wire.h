



// Zaehlervergleichs Register Wert mal 4   fuer 4mhz cpu
#define TIMERCOUNT(x)  ((x) * 4)


/******** Funktions-Prototypen *****/

extern void pinINPUT();




//Einstellungen

extern void einstellungen_1wire();

// 1wire Bus ein/aus

extern void ein_1wire();

extern void aus_1wire();



//Char auslesen

extern char (getc_1wire)();

//Char senden
extern void putc_1wire(char c);

//Char String senden

extern void putc_str_1wire(char* string);


