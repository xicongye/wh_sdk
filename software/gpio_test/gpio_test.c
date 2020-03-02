#include "platform.h"
#include "csr.h"
/* This source code has been tested 
 *  2018.1.30
 *  @yexc
 */

void main_delay(void)
{   
    // Must be "volatile" type if GCC use -O3 option
    volatile unsigned int i, j;

    for(i = 0; i < 50; i++)
        for(j = 0; j < 12000; j++)
            ;
}

int main(void)
{
    gpio_output_enable(GPIOA);
    while(1)
    {
        gpio_write_byte(GPIOA, 0x0e);
#ifdef ON_BOARD
        main_delay();
#endif
        gpio_write_byte(GPIOA, 0x0d);
#ifdef ON_BOARD
        main_delay();
#endif
        gpio_write_byte(GPIOA, 0x0b);
#ifdef ON_BOARD
        main_delay();
#endif
        gpio_write_byte(GPIOA, 0x07);
#ifdef ON_BOARD
        main_delay();
#endif
    }
    return 0;
}

int secondary_main(void)
{
    gpio_output_enable(GPIOB);
    while(1)
    {
        gpio_write_byte(GPIOB, 0x0e);
#ifdef ON_BOARD
        main_delay();
#endif
        gpio_write_byte(GPIOB, 0x0d);
#ifdef ON_BOARD
        main_delay();
#endif
        gpio_write_byte(GPIOB, 0x0b);
#ifdef ON_BOARD
        main_delay();
#endif
        gpio_write_byte(GPIOB, 0x07);
#ifdef ON_BOARD
        main_delay();
#endif
    }
    return 0;
}


