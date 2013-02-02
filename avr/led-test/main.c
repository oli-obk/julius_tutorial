
#include <avr/io.h>
#include <util/delay-basic.h>

#define GETREG(REG_NAME, REG_BIT) (REG_NAME & (1 << REG_BIT))
#define CLRREG(REG_NAME, REG_BIT) (REG_NAME &= ~(1 << REG_BIT))
#define SETREG(REG_NAME, REG_BIT) (REG_NAME |= (1 << REG_BIT))


int main()	{


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

return 0;
}
