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
    printf("M-Mode timer interrupt test Start.\r\n");
    int_init();
    timer_int_init();
    timer_int_enable();
    timer_int_bind_handler(RTC_IRQ_Handler);
    set_timer_cmp(50);
    int_enable();
    //write_csr(mideleg, 0x00);
    while(1)
        continue;
}

void RTC_IRQ_Handler()
{
    static int num = 0;
    printf("I'm here %d times\r\n", num++);
    set_timer_cmp(get_timer_val() + 32768);
}

