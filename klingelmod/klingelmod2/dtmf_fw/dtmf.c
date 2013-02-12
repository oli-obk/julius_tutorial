#include <avr/pgmspace.h>
#include <avr/eeprom.h>

const uint8_t samplesprung[] PROGMEM = {23, 25, 28, 31, 40, 44, 48, 53};
//(x8) 22.75 - 25.13 - 27.80 - 30.71 - 39.46 - 43.60 - 48.20 - 53.30
//(x16)45.50 - 50.26 - 55.61 - 61.42 - 78.92 - 87.21 - 94.46 - 106.60
const uint8_t samples[] EEMEM = {64,67,70,73,76,79,82,85,88,91,94,96,99,102,104,106,109,111,
113,115,117,118,120,121,123,124,125,126,126,127,127,127,127,127,127,127,126,126,125,124,123,121,
120,118,117,115,113,111,109,106,104,102,99,96,94,91,88,85,82,79,76,73,70,67,64,60,57,54,51,48,
45,42,39,36,33,31,28,25,23,21,18,16,14,12,10,9,7,6,4,3,2,1,1,0,0,0,0,0,0,0,1,1,2,3,4,6,7,9,
10,12,14,16,18,21,23,25,28,31,33,36,39,42,45,48,51,54,57,60};
volatile uint16_t durchlaufen = 0;
volatile uint16_t post = 0;
volatile uint16_t posh = 0;
volatile uint8_t freqt = 0;
volatile uint8_t freqh = 0;
volatile uint8_t pause = 0;
const char *Nummersafe;

void dtmf_nextzahl(void);

//muss nicht aufgerufen werden vom Benutzer
void dtmf_init(void){
	//Timer PWM 8bit (erst einschalten bei Tonerzeugung)
	//Phase Correct PWM, OCN, no Prescaler
	TCCR2 = (1<<WGM20) | (1<<COM21) | (1<<CS20); 
	//Overflow Interrupt
	TIMSK |= (1<<TOIE2);
}

//gibt 0 zurück wenn Wählvorgang abgeschlossen
uint8_t get_dtmfdone(void){
	return (pause != 2);
}

//Wählen (max 250 zeichen)
void dtmf_out(const char *Nummer){
	pause = 0;
	//Pointer speichern
	Nummersafe = Nummer;
	//Timer aktivieren
	dtmf_init();
	//freq setzen
	dtmf_nextzahl();
	return;
}

//muss nicht aufgerufen werden vom Benutzer
//nächste Ziffer rauspicken und Frequenzen setzen
void dtmf_nextzahl(void){
	durchlaufen = 0;
	TCCR2 &= ~(1<<CS20);
	if (*Nummersafe != 0){
		//get_digits(*Nummersafe-48);
		switch (*Nummersafe){
			case '1':
				freqt = 0;
				freqh = 4;
			break;
			case '2':
				freqt = 0;
				freqh = 5;
			break;
			case '3':
				freqt = 0;
				freqh = 6;
			break;
			case 'A':
				freqt = 0;
				freqh = 7;
			break;
			case '4':
				freqt = 1;
				freqh = 4;
			break;
			case '5':
				freqt = 1;
				freqh = 5;
			break;
			case '6':
				freqt = 1;
				freqh = 6;
			break;
			case 'B':
				freqt = 1;
				freqh = 7;
			break;
			case '7':
				freqt = 2;
				freqh = 4;
			break;
			case '8':
				freqt = 2;
				freqh = 5;
			break;
			case '9':
				freqt = 2;
				freqh = 6;
			break;
			case 'C':
				freqt = 2;
				freqh = 7;
			break;
			case '*':
				freqt = 3;
				freqh = 4;
			break;
			case '0':
				freqt = 3;
				freqh = 5;
			break;
			case '#':
				freqt = 3;
				freqh = 6;
			break;
			case 'D':
				freqt = 3;
				freqh = 7;
			break;
			default:
				freqt = 0;
				freqh = 0;
		}
		//auf Nächste Ziffer zeigen
		Nummersafe++;
		TCCR2 |= (1<<CS20);
	} else {
		pause = 2;
	}
}

ISR (TIMER2_OVF_vect){
	//Überspung addieren
	if (!pause){
		post += pgm_read_byte(&samplesprung[freqt]);
		posh += pgm_read_byte(&samplesprung[freqh]);
	}
	//Zeiger normalisieren
	uint8_t samplet = ((post+4)>>3)&127;
	uint8_t sampleh = ((posh+4)>>3)&127;
	//Samples holen
	samplet = (3*eeprom_read_byte(&samples[samplet]))>>2;
	sampleh = eeprom_read_byte(&samples[sampleh]);
	OCR2 = samplet + sampleh;	
	durchlaufen++;
	//pause fertig -> neue Ziffer
	if ((durchlaufen >= 2510) && pause){
		pause = 0;
		dtmf_nextzahl();
	}
	//Ziffer fertig -> pause
	if (durchlaufen >= 3000){
		post = 0;
		posh = 0;
		pause = 1;
		durchlaufen = 0;
	}
}

/*void dtmf_set(char input){
	durchlaufen = 0;
	if (*Nummersafe != 0){
		get_digits(*Nummersafe-48);
		switch (input){
			case '1':
				freqt = 0;
				freqh = 4;
			break;
			case '2':
				freqt = 0;
				freqh = 5;
			break;
			case '3':
				freqt = 0;
				freqh = 6;
			break;
			case 'A':
				freqt = 0;
				freqh = 7;
			break;
			case '4':
				freqt = 1;
				freqh = 4;
			break;
			case '5':
				freqt = 1;
				freqh = 5;
			break;
			case '6':
				freqt = 1;
				freqh = 6;
			break;
			case 'B':
				freqt = 1;
				freqh = 7;
			break;
			case '7':
				freqt = 2;
				freqh = 4;
			break;
			case '8':
				freqt = 2;
				freqh = 5;
			break;
			case '9':
				freqt = 2;
				freqh = 6;
			break;
			case 'C':
				freqt = 2;
				freqh = 7;
			break;
			case '*':
				freqt = 3;
				freqh = 4;
			break;
			case '0':
				freqt = 3;
				freqh = 5;
			break;
			case '#':
				freqt = 3;
				freqh = 6;
			break;
			case 'D':
				freqt = 3;
				freqh = 7;
			break;
			default:
				freqt = 0;
				freqh = 0;
		}
		TCCR0 |= (1<<CS00);
	}
}*/