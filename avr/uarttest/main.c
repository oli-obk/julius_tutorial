#include <avr/io.h>
#include <stdint.h>

#ifndef F_CPU
#define F_CPU 8000000         //3686400
#endif
#define UART_BAUD_RATE 9600
#define UART_BAUD_CALC(UART_BAUD_RATE,F_OSC) ((F_CPU) / ((UART_BAUD_RATE)*16L)-1)

//unsigned char get;

char test[] = "1";

int uart_putc(unsigned char c)
{
  while (!(UCSRA & (1<<UDRE)));
UDR = c;
return 0;
}

int main(void)
{

UCSRB |= (1<<TXEN);  //Transmitter Enabled
UCSRC |= (1<<URSEL) | (3<<UCSZ0);  //Asynchron 8N1
	    
UCSRB |= (1<<RXEN);  //Emfpang enabl

UBRRH=(uint8_t) (UART_BAUD_CALC(UART_BAUD_RATE,F_CPU)>>8);
UBRRL=(uint8_t)UART_BAUD_CALC(UART_BAUD_RATE,F_CPU);

DDRB = 0xFF;
PORTB = 0xFF;

while(1)
{

//while(!(UCSRA & (1<<RXC)))
//{
//PORTB = ~get;
//}
// get = UDR;
uart_putc(test);

}
}




