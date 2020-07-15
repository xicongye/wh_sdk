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

int num = 0;

int main(void)
{
    printf("M-Mode timer interrupt test Start.\r\n");
    int_init();
    timer_int_init();
    timer_int_enable();
    timer_int_bind_handler(RTC_IRQ_Handler);
    set_timer_cmp(get_timer_val() + 1500000);
    int_enable();
    write_csr(mideleg, 0x00);
    while(num < 10)
        continue;

    timer_int_disable();
    int_disable();
    set_timer_cmp(get_timer_val() + 0xffffffff);
    //clear_csr(mip, MIP_MTIP);
    printf("TEST DONE!\n");

    return 0;
}

void RTC_IRQ_Handler()
{
    printf("I'm here %d times\r\n", num++);
    set_timer_cmp(get_timer_val() + 1500000);
}

