#include <avr/io.h> 
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <string.h>
#include "tastenplex.c"
#include "dtmf.c"
#include "clip.c"
#include "lcd.c"
#include "lcd.h"

//Nebenstellen Nummern angeben (in Anführungszeichen)
const char NS1[] PROGMEM 	= "1";	
const char NS1AB[] PROGMEM 	= "600";
const char NS2[] PROGMEM 	= "610";
const char NS2AB[] PROGMEM 	= "601";
const char NS3[] PROGMEM 	= "611";
const char NS3AB[] PROGMEM 	= "602";
const char NS4[] PROGMEM 	= "620";
const char NS4AB[] PROGMEM 	= "601";
//Fritzbox spezifische Kommandos
const char RUFEN[] PROGMEM = "**";
const char HOLEN[] PROGMEM = "*0";
const char ALL[] PROGMEM = "9";


/*
R-Taste zuletzt drücken, löst dann wählen aus

Makros(werden aktiv wenn nur 2 Nummern gedrückt):
1 -> holen (2 mal 1 -> alle holen)
4 -> weiterleiten
7 -> anrufen (2 mal 7 -> rundruf)
3 -> NS1 / 2 -> AB
6 -> NS2 / 5 -> AB
9 -> NS3 / 8 -> AB
# -> NS4 / 0 -> AB
*/

uint8_t getastet = 0;
uint8_t taster = 0;
uint8_t i = 0;
char Num[21];
char Nums[10];

void rtast(void){
	PORTC |= (1<<PC1);
	_delay_ms(70);
	PORTC &= ~(1<<PC1);
	_delay_ms(70);
}

int main(void){
	
	//Port init
	DDRB  = (1<<PB3) | (1<<PB5); //DTMF, LCD Licht
	DDRC  = (1<<PC1); //R Taste Relais
	PORTC = (1<<PC0);//R-Taste Schalter Pullup
	//Restliches Port Init in den Librarys 
	
	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
	init_tastenplex();
	//init_clip();
	sei();
	while(1){
		//Eingabe speichern
		getastet = get_tastenplex();
		taster = !((PINC & (1<<PC0))>>PC0);
		//Taste gedrückt und noch Platz im String
		if ((getastet != 0) && (i < 21)){
			//Taste gedrückt, timeout neustarten
			timeout = 0;
			//get_digits(getastet);
			//andere Zeichen in ASCI wandeln
			switch (getastet) {
				case 10:
					Num[i] = '*';
					break;
				case 11:
					Num[i] = 48;
					break;
				case 12:
					Num[i] = '#';
				default:
					if (getastet < 10){
						Num[i] = getastet+48;
					}
			}
			PORTB |= (1<<PB5);
			lcd_putc(Num[i]);
			//get_digits(Num[i]);
			//Pointer zeigt auf nächste Stelle
			i++;
			//String terminieren
			Num[i] = 0;
		}
		//für 2sek keine Eingabe mehr oder R-Taste -> wählen
		if (((timeout >= 800) || taster) && (Num[0] != 0)){
			if (i == 2){
				//speziell wählen
				Nums[0] = 0;
				switch (Num[0]){
					case '1':
						strcat_P(Nums, HOLEN);
						break;
					case '4':
						strcat_P(Nums, RUFEN);
						taster = 1;
						break;
					default:
						strcat_P(Nums, RUFEN);
				}
				switch (Num[1]){
					case '1':
					case '7':
						strcat_P(Nums, ALL);
						break;
					case '2':
						strcat_P(Nums, NS1AB);
						break;
					case '3':
						strcat_P(Nums, NS1);
						break;
					case '5':
						strcat_P(Nums, NS2AB);
						break;
					case '6':
						strcat_P(Nums, NS2);
						break;
					case '8':
						strcat_P(Nums, NS3AB);
						break;
					case '9':
						strcat_P(Nums, NS3);
						break;
					case '0':
						strcat_P(Nums, NS4AB);
						break;
					default:
						strcat_P(Nums, NS4);
				}
				if (taster){
					taster = 0;
					rtast();
				}
				dtmf_out(Nums);
			}else{
				//normal wählen
				if (taster){
					taster = 0;
					rtast();
				}
				dtmf_out(Num);
			}
			//warten wenn noch gewählt wird
			while(get_dtmfdone()){
				;
			}
			PORTB &= ~(1<<PB5);
			lcd_clrscr();
			i = 0;
			Num[0] = 0;
		}
		
	}
	return 0;
}