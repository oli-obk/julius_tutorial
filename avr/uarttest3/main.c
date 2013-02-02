#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <uart.h>
#include <uart.c>
#include <inttypes.h>
#define GETREG(REG_NAME, REG_BIT) (REG_NAME & (1 << REG_BIT))
#define CLRREG(REG_NAME, REG_BIT) (REG_NAME &= ~(1 << REG_BIT))
#define SETREG(REG_NAME, REG_BIT) (REG_NAME |= (1 << REG_BIT))
#define CNGREG(REG_NAME, REG_BIT) (REG_NAME ^= (1 << REG_BIT))


#ifndef F_CPU
#define F_CPU 8000000         //3686400
#endif

#define UART_BAUD_RATE 9600

void turnledon(void)

{
    SETREG(DDRA, PA1);
    SETREG(PORTA, PA1);
}

void turnledoff(void)
{
    CLRREG(DDRA, PA1);
    CLRREG(PORTA, PA1);
}

uint16_t readADC(uint8_t channel)
{
    uint8_t i;
    uint16_t result = 0;

    // Den ADC aktivieren und Teilungsfaktor auf 64 stellen
    ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1);

    // Kanal des Multiplexers waehlen
    // Interne Referenzspannung verwenden (also 2,56 V)
    ADMUX = channel  | (1<<REFS0);
    // | (1<<REFS1)
    // Den ADC initialisieren und einen sog. Dummyreadout machen
    ADCSRA |= (1<<ADSC);
    while(ADCSRA & (1<<ADSC));

    // Jetzt 3x die analoge Spannung and Kanal channel auslesen
    // und dann Durchschnittswert ausrechnen.
    for(i=0; i<3; i++)
    {
        // Eine Wandlung
        ADCSRA |= (1<<ADSC);
        // Auf Ergebnis warten...
        while(ADCSRA & (1<<ADSC));

        result += ADCW;
    }

    // ADC wieder deaktivieren
    ADCSRA &= ~(1<<ADEN);

    result /= 3;

    return result;
}

uint16_t g_OhmToTemp[] =
{
    26640,
    19330,
    14210,
    10520,
    7885,
    5944,
    4530,
    3474,
    2693,
    2097,
    1648,
    1301,
    830,
    669,
    542,
    442,
    362,
    298,
    247,
    205,
    171,
    144,
    121,
    102,
    87,
    74,
    64,
    55
};

int main()
{

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

    int comandcount = 0;

    char comandtest [] = "test";
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
           /* if ( c == 'p')
            {
                uint32_t result = readADC(0);
                uint32_t skalierung = 200;
                const uint32_t widerstand = 100*skalierung;
                uint32_t volt = result;
                uint32_t temp_widerstand = 1024*widerstand/volt - widerstand;
                temp_widerstand /= skalierung/10;

                int i ;
                for ( i = 1; i < sizeof(g_OhmToTemp)/sizeof(uint16_t); i++)
                {
                    if (g_OhmToTemp[i]>temp_widerstand) continue;
                    char buffer [15];
                    buffer[0] = '\n';
                    buffer[1] = '\r';
                    uint16_t val = (temp_widerstand-g_OhmToTemp[i]);
                    val*=5;
                    val/=(g_OhmToTemp[i-1]-g_OhmToTemp[i]);
                    itoa (i*5-40-val,buffer+2,10);
                    uart_puts(buffer);
                    break;
                }



            }
            */
            if ( c == comandtest [comandcount] )
            {
                comandcount++;
            }

            if ( comandcount == 4 )
            {
                turnledon();

            }
            SETREG(DDRC, PC1);
            SETREG(PORTC, PC1);
            CLRREG(DDRD, PD6);
            SETREG(DDRD, PD6);
            if ( PIND & (1<<PIND6))
            {
                turnledon();
            }
            else
            {

                turnledoff();
            }
            SETREG(PORTD, PD5);
            SETREG(DDRD, PD5);
            //set ctc mode

            //SETREG(TCCR1A, COM1A1);
            //SETREG(TCCR1A, COM1B1);

            SETREG(TCCR1A, COM1A0);
            SETREG(TCCR1B, WGM12);
            //set prescaler
            SETREG(TCCR1B, CS12);
            SETREG(TCCR1B, CS10);

            //compare register
         //   int freq

            OCR1A = 420;
               //freqgen;

        }

    }

    return 0;


}
