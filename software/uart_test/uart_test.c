/*******************************************************************
*
*       PROJECT:        W01
*
*       FILENAME:       uart_test.c
*
*       FUNCTION:       UART test demo
*
*       AUTHOR:         yexc
*
*       DATE:           2018/01/30
*
*       IS_FINISH:      YES
*
********************************************************************/
/* Includes --------------------------------------------------------*/
#include "platform.h"

/* Private define --------------------------------------------------*/
/* Private macro ---------------------------------------------------*/
/* Private variables -----------------------------------------------*/
/* Extern variables ------------------------------------------------*/
/* Private function prototypes -------------------------------------*/
/* Private functions -----------------------------------------------*/
/********************************************************************
* Function Name :   UART_IRQ_Handler
* Description   :   UART interrupt handler function
* Input         :   none
* Output        :   none
* Return        :   0
********************************************************************/
void UART_IRQ_Handler(void)
{
    uint8_t ch;

    ch = uart_getchar();
    UART_REG(UART_IS) &= ~UART_IS_FIFO_NE;
    uart_putchar(ch);
}

/********************************************************************
* Function Name :   main
* Description   :   main routine
* Input         :   none
* Output        :   none
* Return        :   0
********************************************************************/
int main(void)
{
    // initialize all interrupts
    int_init();

    // enable global interrupt
    global_int_enable(1);

    // set priority
    global_int_priority(1, 2);

    // bind handler function
    global_int_bind_handler(1, UART_IRQ_Handler);

    // enable global interrupts
    set_csr(mie, MIE_MEIE);

    // enable all interrupts
    int_enable();

    uart_init(115200);

    uart_set_IE(UART_IE_FIFO_NE);

    //uart_puts("Please input character...\r\n");
    uart_putchar('a');
    uart_puts("Please input character...\r\n");

    while(1)
        continue;
    return 0;

}



