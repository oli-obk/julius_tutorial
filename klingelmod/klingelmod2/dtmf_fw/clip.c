
#include <stdlib.h>
#include "uart.c"

char aus[6] = "";

void init_clip(void){
	//compareausgang zu ICP weiterleiten
	ACSR = (1<<ACIC);
	//Entprellung, steigende Flanke, CLK/64
	TCCR1B = (1<<ICNC1) | (1<<ICES1) | (1<CS11) | (1<<CS10);
	//Inputevent ISR
	TIMSK |= (1<<TICIE1);
	uart_init(25);
}

ISR (TIMER1_CAPT_vect){
	TCNT1 = 0;
	
	if ((ICR1<12500) && (ICR1>4166)){
		utoa(ICR1, (char*)&aus, 10);
		uart_puts((char*)&aus);
		uart_putc(0);
	}
	
	
	if (PINB & (1<<PB5)){
		PORTB &= ~(1<<PB5);
	} else {
		PORTB |= (1<<PB5);
	}
} 

//comp setzen für wartezeit nach klingeln wann fsk kommt

//ana Comp an ICP, für genaue messdaten und wenig isr