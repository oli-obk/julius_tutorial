/*
 */

#include <avr/io.h>
#include <avr/uart.c>
#include <avr/uart.h>
#include <avr/macros.h>
#include <stdlib.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <inttypes.h>
#include "1wire.h"
#include "macros.h"



#ifndef F_CPU
#define F_CPU 4000000UL         //3686400
#endif

#define UART_BAUD_RATE 9600

#define DEBUG 1





int main(void)
{




    /*
    * Intialize UART library, pass baudrate and AVR cpu clock
    * with macro
    * UART_BAUD_SELECT() (normal speed mode)
    * of
    * UART_BAUD_SELECT_DOUBLE_SPEED() (double speed mode)
    */

  //  uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );

    /*
    * now enable interrupt, since UART library is interrupt controlled
    */


    //DEBUGOUTPUT("test");

    sei();
    //uart_puts_P("uart initiert ");
    /*
    * transmit string to uart
    * the string is buffered by the uart library is a circular buffer
    * and one character at a time is transmitted to the UART using interrupts.
    * uart_puts() blocks if it can not write the whole string to the circular
    * buffer
    */




           einstellungen_1wire();

           ein_1wire();



           char blabla = 'a';

           putc_1wire(blabla);






    while(1)                    //statemachine
        {

        };

    return 0;
}
