/*
 */

#include <avr/io.h>
#include <string.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "uart.h"
#include <inttypes.h>
#define GETREG(REG_NAME, REG_BIT) (REG_NAME & (1 << REG_BIT))
#define CLRREG(REG_NAME, REG_BIT) (REG_NAME &= ~(1 << REG_BIT))
#define SETREG(REG_NAME, REG_BIT) (REG_NAME |= (1 << REG_BIT))
#define CNGREG(REG_NAME, REG_BIT) (REG_NAME ^= (1 << REG_BIT))

#ifndef F_CPU
#define F_CPU 16000000         //3686400
#endif

#define UART_BAUD_RATE 9600





int main(void)
{

    // Insert code

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

    char c;

    while(1)
    {
        c = uart_getc();
        if (c & UART_NO_DATA )
        {
            /*
             * no data available from UART
             */
        }
        else
        {
            /*
             * new data available from UART
             * check for Frame or Overrun error
             */
            if ( c & UART_FRAME_ERROR )
            {
                /* Framing Error detected, i.e no stop bit detected */
                uart_puts_P("UART Frame Error: ");
            }
            if ( c & UART_OVERRUN_ERROR )
            {
                /*
                 * Overrun, a character already present in the UART UDR register was
                 * not read by the interrupt handler defore the next character arrived,
                 * one or more received characters have been dropped
                 */
                uart_puts_P("UART Overrun Error: ");
            }
            if ( c & UART_BUFFER_OVERFLOW )
            {
                /*
                 * We are not reading the receive buffer fast enough,
                 * one or more received characters have been dropped
                 */
                uart_puts_P("Buffer overflow error: ");
            }
            /* check if transcived is an command
             */

             void getnumbers(char* arr, int num)
             {

             }

            //commandos welche ueber uart ausgefuehrt werden
            int dial(void)
            {
                char telefonnummer[25];
                getnumbers(telefonnummer, 24);
                SETREG(DDRD, PD5);

                while(1)
                    {
                    //warten wenn noch gewaehlt wird
                    while(get_dtmfdone()){
                    ;
                    }
                    //waehlen
                    dtmf_out(telefonnummer);
                    }
            };
            int opendoor(void)
            {
                void;
            };


            int lock(void)
            {
                void;
            };


            int unlock(void)
            {
                void;
            };


            struct UART_KOMMANDOS
            {
                char *comandname;
                int (*comandFunction)(void);
            };
            struct UART_KOMMANDOS FunctionTable[10] =
             {
                 {"dial", &dial},
                 {"opendoor", &opendoor},
                 {"lock", &lock},
                 {"unlock", &unlock}
                };



                // buffer und counter fuer eingabe
                char uart_input_buffer[25] = {};
                char uart_input_breaker[] = {'\n', '\r'};


                int uart_input_counter = 0;

                //uart eingabe checken

                //eingabe auf breaker checken, wenn nicht zeichen in buffer schreiben
                if ( c != uart_input_breaker[0] && c != uart_input_breaker[1] && uart_input_counter < 25 )
                {
                    c = uart_input_buffer[uart_input_counter];
                    ++uart_input_counter;
                }

                //bei breaker, buffer mit kommando array vergleichen

                else {
                    int uibc = 0;
                    if ( c == uart_input_breaker[uibc] )
                    {
                        ++uibc;
                        if ( uibc == 2 )
                        {
                            uibc = 0;
                            uart_input_counter = 0;
                            int i;
                            for ( i = 0; i < (sizeof(FunctionTable) / sizeof(*FunctionTable)); i++)
                            {
                                if(strcmp(FunctionTable[i].comandname,uart_input_buffer)==0)
                                {
                                    FunctionTable[i].comandFunction();
                                    break;
                                }



                            }
                        }
                    }
                }



            }




            while(1)
                ;

            return 0;
        }
}
