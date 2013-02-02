
#include <avr/io.h>
#include <stdint.h>
#define GETREG(REG_NAME, REG_BIT) (REG_NAME & (1 << REG_BIT))
#define CLRREG(REG_NAME, REG_BIT) (REG_NAME &= ~(1 << REG_BIT))
#define SETREG(REG_NAME, REG_BIT) (REG_NAME |= (1 << REG_BIT))
#define CNGREG(REG_NAME, REG_BIT) (REG_NAME ^= (1 << REG_BIT))

#ifndef F_CPU
#define F_CPU 8000000UL
#endif
#if F_CPU < 2000000UL 
#define USE_2X
#endif
	



#include <util/delay.h>

#define BAUD 9600		// Baudrate
#include <util/setbaud.h>

#define CR "\n"


void long_delay(uint16_t ms)
{
	for(; ms>0; ms--) _delay_ms(1);
}


void uart_init(void)
{

UBRRH = UBRRH_VALUE;
UBRRL = UBRRL_VALUE;

SETREG(UCSRB, TXEN);	// UART TX einschalten (uart senden)

SETREG(UCSRC, URSEL); //
//SETREG(UCSRC, UCSZ1);  asynchron 8n1
//SETREG(UCSRC, UCSZ0); //
UCSRC = (3 << UCSZ0);

#if USE_2X
SETREG(UCSRA, U2X);
#else
SETREG(UCSRA, U2X);
#endif

}

int uart_putc(unsigned char c)
	{
		while (!(UCSRA & (1<<UDRE)))   /* warten bis Senden moeglich */
		{
		}

UDR = c;		/* sende Zeichen */
return 0;
}


void uart_puts (char *s)
{
while (*s)
	{	/* so lange *s != '\0' also ungleich dem "String-Endezeichen(Terminator)" */
	uart_putc(*s);
	s++;
}
}


int main()	{


SETREG(DDRA, PA0);


// DDRA |= 1 << PA0;

while (1)
{
CNGREG(PORTA, PA0);
//PORTA ^= 1 << PA0;
long_delay(1000);

uart_init();

char test[] = "test" CR;

uart_puts(test);

}



return 0;
}
