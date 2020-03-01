/*******************************************************************
*
*       PROJECT:        W01
*
*       FILENAME:       cpu.c
*
*       FUNCTION:       cpu feature
*
*       AUTHOR:         yexc
*
*       DATE:           2019/11/30
*
*       IS_FINISH:      NO
*
********************************************************************/
/* Includes --------------------------------------------------------*/
#include "csr.h"
#include "platform.h"

/* Private define --------------------------------------------------*/
/* Private macro ---------------------------------------------------*/
/* Private variables -----------------------------------------------*/
/* Extern variables ------------------------------------------------*/
/* Private function prototypes -------------------------------------*/
/* Private functions -----------------------------------------------*/
/********************************************************************
* Function Name :   get_cpu_frequency
* Description   :   get cpu current frequency
* Input         :   none
* Output        :   none
* Return        :   current frequency
********************************************************************/
unsigned long long get_cpu_frequency(void)
{
    return (unsigned long long)(CORE_FREQ);
}


/********************************************************************
* Function Name :   get_cyclecount
* Description   :   get mcycle counter value
* Input         :   none
* Output        :   none
* Return        :   mcycle counter value
********************************************************************/
unsigned long long get_cyclecount(void)
{
    unsigned long long val = 0;
#if __riscv_xlen == 32
    unsigned long hi, hi1, lo; 

    asm volatile ("csrr %0, mcycleh" : "=r"(hi));
    asm volatile ("csrr %0, mcycle" : "=r"(lo));
    asm volatile ("csrr %0, mcycleh" : "=r"(hi1));
    if (hi == hi1) {
        val = ((unsigned long long)hi << 32) | lo; 
    }   
#else
    asm volatile ("csrr %0, mcycle" : "=r"(val));
#endif
    return val;
}

