
#include <avr/io.h>

#define GETREG(REG_NAME, REG_BIT) (REG_NAME & (1 << REG_BIT))
#define CLRREG(REG_NAME, REG_BIT) (REG_NAME &= ~(1 << REG_BIT))
#define SETREG(REG_NAME, REG_BIT) (REG_NAME |= (1 << REG_BIT))
#define CNGREG(REG_NAME, REG_BIT) (REG_NAME ^= (1 << REG_BIT))

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <util/delay.h>

int main()	{


SETREG(DDRA, PA0);


// DDRA |= 1 << PA0;

while (1)
{
CNGREG(PORTA, PA0)
//PORTA ^= 1 << PA0;
_delay_ms(100);
}



return 0;
}
