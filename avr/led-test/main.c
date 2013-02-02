
#include <avr/io.h>
<<<<<<< HEAD
=======
#include <util/delay-basic.h>
>>>>>>> 335426c5df42ca4ae6485e7e69e047a6ed41480a

#define GETREG(REG_NAME, REG_BIT) (REG_NAME & (1 << REG_BIT))
#define CLRREG(REG_NAME, REG_BIT) (REG_NAME &= ~(1 << REG_BIT))
#define SETREG(REG_NAME, REG_BIT) (REG_NAME |= (1 << REG_BIT))

<<<<<<< HEAD
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <util/delay.h>
=======
>>>>>>> 335426c5df42ca4ae6485e7e69e047a6ed41480a

int main()	{


<<<<<<< HEAD
DDRA |= 1 << PA0;

while (1)
{
PORTA ^= 1 << PA0;
_delay_ms(1000);
}


=======
init i;
i = 1;
for (i = 1)
{
SETREG(PORTA, 0);
SETREG(DDRA, 0);

__delay_ms(10000);

CLRREG(PORTA, 0);
CLRREG(DDRA, 0);

__delay_ms(10000);
}
>>>>>>> 335426c5df42ca4ae6485e7e69e047a6ed41480a

return 0;
}
