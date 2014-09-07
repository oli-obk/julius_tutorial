#include <avr/pgmspace.h>
#include <util/delay.h>
#include <inttypes.h>
#include <avr/io.h>
#include "macros.h"
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdbool.h>



#define BUFSIZE 16


// Funktionen fuer Einstellungen

void pinINPUT()
{
    SETREG(PORTD, PD2);
    CLRREG(DDRD, PD2);
}

void pinOUTPUT()
{
    SETREG(PORTD, PD2);
    SETREG(DDRD, PD2);
};

void extINT_steigend()
{
    // Resgister setzen Interrupt bei steigender Flanke an INT0 auszuloesen

    SETREG(MCUCR, ISC00);
    SETREG(MCUCR, ISC01);
// Iterrupt fuer INT0 aktivieren
    SETREG(GICR, INT0);

};

void extINT_fallend()
{
    // Resgister setzen Interrupt bei fallender Flanke an INT0 auszuloesen

    SETREG(MCUCR, ISC00);
    SETREG(MCUCR, ISC01);
// Iterrupt fuer INT0 aktivieren
    SETREG(GICR, INT0);

};

void extINT_aus()
{
    CLRREG(GICR, INT0);
}

void timer_settings()
{
//Einstellungen fuer timer0
//CTC Modus
    SETREG(TCCR0, WGM01);
//kein Vorteiler
    SETREG(TCCR0, CS00);
//INterrupt fuer CTC aktivieren
    SETREG(TIMSK, OCIE0);

};

void timer_int_aus()
{
    CLRREG(TIMSK, OCIE0);
};


// funktionen fuer read/write
//read


int read_bit;

int set_read_bit_to_1()
{
    if (TCNT0 > 12, TCNT0 < 30)
        {
            read_bit = 1;
        }
};

//fifo

volatile unsigned char fifo[BUFSIZE];
volatile unsigned rd=0, wr=0;       /* read and write positions */
volatile unsigned int bitstelle_fifo=0;
volatile unsigned int bitstelle_fifo_fifo_read=0;


// write bit to fifo

void write_bit_to_fifo()
{

    bit_write(read_bit, fifo[wr], BIT(bitstelle_fifo) );


    if (bitstelle_fifo == 7)
        {
            wr = (wr + 1) % BUFSIZE;
        }

    bitstelle_fifo = ( bitstelle_fifo + 1) % 8;

    read_bit = 0;
};

// write a byte into FIFO

void write_byte_to_fifo(char *c)
{
    fifo[wr] = *c;
    wr = (wr + 1) % BUFSIZE;
};

// read bit from fifo

int read_bit_from_fifo()
{

    int i = bit_get(fifo[rd], bitstelle_fifo_fifo_read);

    if (bitstelle_fifo_fifo_read == 7)
        {
            rd = (rd +1) % BUFSIZE;
        }

    bitstelle_fifo_fifo_read = ( bitstelle_fifo_fifo_read +1) % 8;

    return i;

}


/* read bytes from FIFO */
char read_byte_from_fifo()
{
    if (rd != wr)
        {
            char c = fifo[rd];
            rd = (rd + 1) % BUFSIZE;
            return c ;
        }
    else
        {
            return NULL;
        }
};



//write


int write_bit;


struct state
{
    int next_state;
    void (*pinstate)();                 //pointer zu funktion um pin einstellungen vor zu nehmen
    int TIMERCOUNT;             //timer einstellung
    void ((*Timer_action)());             //pointer fuer funktion die bei timer interupt ausgefuehrt werden soll
    int  Timer_action_parameter;        //optionaler parameter fuer Funktion Timer_action
    void (*ext_interupt)();             //pointer fuer funktion um externen interrupt einzustellen
    void ((*ext_i_action)());             //pointer fuer funktion bei externem interrupt
    int  Ext_i_action_parameter;        //optionaler parameter fuer ext i action Funktion
    bool bus_blockiert;             //bus blockiert? fuer schreib zugriff
};

void nichts() {};


// state machine
//aktueller Zustand
int state_count;
//naechster zustand fuer write
int write_state;

// prototypen fuer Zustands aufruf

void state_call_write();

void call_next_state();

void alternativ_state_call();

void check_timer();

void state_call_read();

void back_to_idle_state();

struct state Bus_states[13];

void setup_Bus_states()
{
    struct state Bus_states[] =
{
// Next State||PinSETTINGS|Timer count||TimerIQR|| TimerIQR PARAM||EXTintSettings||EXTintIQR||Bus Block

//Listen-states
//idle                  0
    { 1, pinINPUT, 80, timer_int_aus, 0, extINT_fallend, call_next_state, 0, false } ,
//check reset?          1
    { 2, pinINPUT, 500, back_to_idle_state, 0, extINT_steigend, check_timer, 400, true },
//pause-> sync          2
    { 3, pinINPUT, 10,  call_next_state, 0,   extINT_aus,  nichts, 0,        true },
//sync                  3
    { 4, pinOUTPUT, 60, call_next_state, 0,   extINT_aus,  nichts,  0,          true },
//read                  4
    { 5, pinINPUT, 60, state_call_read, 0, extINT_steigend, set_read_bit_to_1, 0, true },
//pause -> read         5
    { 4, pinINPUT, 10, call_next_state, 0, extINT_aus, nichts, 0, true },

//write-states
//reset                 6
    { 7, pinOUTPUT, 480, call_next_state, 0,  extINT_aus, nichts, 0, true   },
//pause-> presence_check          7
    { 8, pinOUTPUT, 10, call_next_state, 0, extINT_aus, nichts, 0, true  },
//presence_check           8
    { 6, pinINPUT, 80, alternativ_state_call, 6, extINT_steigend, check_timer, 50, true},
//pause->write             9
    { 0, pinINPUT, 10, call_next_state, 0, extINT_aus, nichts, 0, true},
//write 0                   10
    { 9, pinOUTPUT, 60, state_call_write, 0, extINT_aus, nichts, 0, true},
// write 1.1                11
    { 12, pinOUTPUT, 15, call_next_state, 0, extINT_aus, nichts, 0, true    },
// write 1.2                12
    { 9, pinINPUT, 45, state_call_write, 0, extINT_aus, nichts, 0, true   },


};

}


void set_state_settings()
{
    // Pinzustand aendern
    Bus_states[state_count].pinstate();
    // timer vergleichsregister setzen
    OCR0 = Bus_states[state_count].TIMERCOUNT;
    //extINT einstellen
    Bus_states[state_count].ext_interupt();

}


void alternativ_state_call()
{
// Zustand setzen
    state_count = Bus_states[state_count].Timer_action_parameter;

    set_state_settings();

};


// wrapper für write um write state auf fifo zu holen
void state_call_write()
{
    call_next_state();

    if(rd != wr)
        {


            if( read_bit_from_fifo())
                {
                    Bus_states[9].next_state = 11;
                }
            else
                {
                    Bus_states[9].next_state = 10;
                }
        }
    else
        {
            write_state = 0;
        }
};

void state_call_read(){
    call_next_state();
    write_bit_to_fifo();

};



void call_next_state()
{
// Zustand aus tabelle auslesen
    state_count = Bus_states[state_count].next_state;

    set_state_settings();
};


void check_timer()
{
    if (TCNT0 < Bus_states[state_count].Ext_i_action_parameter )
        {
            alternativ_state_call();
        }
    else
        {
            if ( state_count = 8)
                {
                    if( read_bit_from_fifo())
                        {
                            Bus_states[state_count].next_state = 11;
                        }
                    else
                        {
                            Bus_states[state_count].next_state = 10;
                        }

                }
            call_next_state();
        }
}

void back_to_idle_state()
{
    state_count = 0;
    set_state_settings();
}


// Interrupt Service Routine

//external interrupt 0
ISR(INT0_vect)
{
    Bus_states[state_count].ext_i_action();
}
//timer0 interrupt
ISR(TIMER0_COMP_vect)
{
    Bus_states[state_count].Timer_action();
}



/******************                       bus Functionen **********************/


void einstellungen_1wire()
{
    setup_Bus_states();

    state_count = 0;

    timer_settings();

}

void ein_1wire()
{
    set_state_settings();
}

void aus_1wire()
{
    state_count = 0;
    extINT_aus();
    timer_int_aus();
    set_state_settings();
}



char (getc_1wire)()
{
    return read_byte_from_fifo();
}


void putc_1wire(char c)
{
    if( Bus_states[state_count].bus_blockiert == false)
        {
            write_byte_to_fifo(c);

            state_count = 6;

            set_state_settings();
        }
    else
        {
            return NULL;
        }

}


void putc_str_1wire(char* string)
{
    if(Bus_states[state_count].bus_blockiert == false)
        {


            for(int i=0 ; string[i] = !0 ; i++ )
                {
                    write_byte_to_fifo(string[i]);
                    if ( Bus_states[state_count].bus_blockiert == false)
                        {
                            state_count = 6;

                            set_state_settings();
                        }

                }
        }
    else
        {
            return NULL;
        }

}
