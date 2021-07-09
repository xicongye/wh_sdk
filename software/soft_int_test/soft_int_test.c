/*********************************************************************************
*
*       PROJECT:        WH32_DDR 
* 
*       FILENAME:       soft_int_test.c 
* 
*       FUNCTION:       soft_int_test driver 
* 
*       AUTHOR:         yexc 
* 
*       DATE:           Tue Jul 16 09:50:29 CST 2019 
* 
*       ISFINISH:       NO 
* 
*       STATUS:  
*********************************************************************************/
#include "platform.h"

void SOFT_IRQ_Handler() 
{
    static int num = 0;
    printf("I'm here %d times\r\n", num++);
    soft_int_stop();
}

int main(void)
{
    int test_case = 0;

    clear_csr(mip, MIP_MTIP);
    printf("M-Mode software interrupt test Start.\r\n");
    //int_init();
    soft_int_enable();
    soft_int_bind_handler(SOFT_IRQ_Handler);
    write_csr(mideleg, 0x00);
    int_enable();

    while(test_case++ < 10)
    {
      soft_int_start();
      for(volatile int i = 0; i < 10000; i++)
         for(volatile int j = 0; j < 500; j++)
           continue;
    }

    soft_int_disable();
    int_disable();
    printf("TEST DONE!\n");

    return 0;
}
