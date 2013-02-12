#include <avr/io.h> 
#include <avr/interrupt.h>

#define DDR(x) (*(&x - 1))
#define PIN(x) (*(&x - 2))

//Port angeben und Pins für Spalten/Zeilen
#define SPALTENPORT PORTD
#define SPALTE0	PD2
#define SPALTE1 PD1
#define SPALTE2 PD0
#define ZEILENPORT  PORTC
#define ZEILE0	PC2
#define ZEILE1	PC5
#define ZEILE2	PC4
#define ZEILE3	PC3
#define TASTSCHWELLWERT 4

/*
	Spalte0 - Spalte1 - Spalte2
Zeile0  1		2		3
Zeile1	4		5		6
Zeile2	7		8		9
Zeile3	*(10)	0(11)	#(12)
*/

volatile uint8_t rawtast = 0;
volatile uint8_t taste = 0;
volatile uint8_t tastdel = 0;
uint8_t zeile = 0;
uint8_t base = 0;
volatile uint16_t timeout = 0;

void init_tastenplex(void){
	//Timer Init (222Hz)
	TCCR0 = (1<<CS02); //CLK/256
	TIMSK |= (1<<TOIE0); //OVF ISR
	
	//Spalten auf in mit Pullup schalten
	DDR(SPALTENPORT) &= ~((1<<SPALTE0) | (1<<SPALTE1) | (1<<SPALTE2));
	SPALTENPORT |= ((1<<SPALTE0) | (1<<SPALTE1) | (1<<SPALTE2));
	//Zeilen auf GND
	ZEILENPORT &= ~((1<<ZEILE0) | (1<<ZEILE1) | (1<<ZEILE2) | (1<<ZEILE3));
}

//liefert gedrückte taste und gibt diese zum löschen frei
uint8_t get_tastenplex(void){
	if((rawtast > TASTSCHWELLWERT) && (tastdel == 0)){
		tastdel = taste;
		taste = 0;
		return tastdel;
	}
	return 0;
}

ISR(TIMER0_OVF_vect){
	//alle Zeilen auf in und nur Zeile auf GND, die aktiv ist
	//DDR(TASTENPORT) &= ~((1<<ZEILE0) | (1<<ZEILE1) | (1<<ZEILE2) | (1<<ZEILE3));
	switch (zeile){
		case 0:
			DDR(ZEILENPORT) |= (1<<ZEILE0);
			break;
		case 1:
			DDR(ZEILENPORT) |= (1<<ZEILE1);
			break;
		case 2:
			DDR(ZEILENPORT) |= (1<<ZEILE2);
			break;
		default:
			DDR(ZEILENPORT) |= (1<<ZEILE3);
	}
	base = zeile*3;
	//Spalten auslesen
	if ((PIN(SPALTENPORT) & (1<<SPALTE0)) == 0){
		if (taste == base+1){
			rawtast++;
		}else{
			taste = base+1;
			rawtast = 0;
		}
	} else if((base+1) == tastdel) {
		rawtast = 0;
		tastdel = 0;
	}
	if ((PIN(SPALTENPORT) & (1<<SPALTE1)) == 0){
		if (taste == base+2){
			rawtast++;
		}else{
			taste = base+2;
			rawtast = 0;
		}
	} else if((base+2) == tastdel) {
		rawtast = 0;
		tastdel = 0;
	}
	if ((PIN(SPALTENPORT) & (1<<SPALTE2)) == 0){
		if (taste == base+3){
			rawtast++;
		}else{
			taste = base+3;
			rawtast = 0;
		};
	} else if((base+3) == tastdel) {
		rawtast = 0;
		tastdel = 0;
	}
	//hochzählen und normalisieren
	zeile ++;
	zeile &= 3;
	timeout ++;
	DDR(ZEILENPORT) &= ~((1<<ZEILE0) | (1<<ZEILE1) | (1<<ZEILE2) | (1<<ZEILE3));
}

/*rudimentär:
-bei jedem drück event hochzählen
-zurücksetzen nur wenn taste erkannt und ausgelesen
*/

/*
gleiche taste gedrückt -> hochzählen
gleiche taste nicht mehr gedrückt -> 0
andere taste gedrückt -> 0 und taste variable ändern
*/