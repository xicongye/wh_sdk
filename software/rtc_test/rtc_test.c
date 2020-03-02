/*********************************************************************************
*
*       PROJECT:        WH32_DDR 
* 
*       FILENAME:       rtc_test.c 
* 
*       FUNCTION:       rtc_test driver 
* 
*       AUTHOR:         yexc 
* 
*       DATE:           Tue Jul 16 09:46:41 CST 2019 
* 
*       ISFINISH:       NO 
* 
*       STATUS:  
*********************************************************************************/
#include "platform.h"

void RTC_IRQ_Handler(void);
int main(void)
{
        asm(
         "li t0, 3<<23\n"
         "csrs mstatus, t0\n"
         "li a0, -1\n"
         "vsetvli a1, a0, e32, m8\n"
         "li a3, 0x40001000\n"
         );

    printf("M-Mode timer interrupt test Start.\r\n");
    //int_init();
    timer_int_init();
    timer_int_enable();
    timer_int_bind_handler(RTC_IRQ_Handler);
    set_timer_cmp(1000000);
    int_enable();
    write_csr(mideleg, 0x00);
    while(1)
    {
      asm("vlbff.v v8, (a3)");
      //asm("vadd.vv v8, v0, v8");
    }
}

void RTC_IRQ_Handler()
{
    static int num = 0;
    printf("I'm here %d times\r\n", num++);
    set_timer_cmp(get_timer_val() + 1000000);
}

