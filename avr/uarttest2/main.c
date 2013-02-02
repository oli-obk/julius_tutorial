#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <uart.h>
#include <uart.c>



#ifndef F_CPU
#define F_CPU 8000000         //3686400
#endif

#define UART_BAUD_RATE 9600

main()
{

unsigned int c;
char buffer[7];
int num=123;

/*
 * Intialize UART library, pass baudrate and AVR cpu clock
 * with macro
 * UART_BAUD_SELECT() (normal speed mode)
 * of
 * UART_BAUD_SELECT_DOUBLE_SPEED() (double speed mode)
 */
uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );

/*
 * now enable interrupt, since UART library is interrupt controlled
 */

sei();

/*
 * transmit string to uart
 * the string is buffered by the uart library is a circular buffer
 * and one character at a time is transmitted to the UART using interrupts.
 * uart_puts() blocks if it can not write the whole string to the circular
 * buffer
 */

unsigned char test [] = "test \n";

while(1)
{

uart_puts(test);
};
return 0;
}

