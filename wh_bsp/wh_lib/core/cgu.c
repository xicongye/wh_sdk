/*******************************************************************
*
*       PROJECT:        W01
*
*       FILENAME:       cgu.c
*
*       FUNCTION:       Clock Generator Unit driver
*
*       AUTHOR:         yexc
*
*       DATE:           2018/03/21
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
* Function Name :   cgu_set_cpu_freq
* Description   :   set CPU clock frequency
* Input         :   - freq -
* Output        :   none
* Return        :   none
********************************************************************/
void cgu_set_cpu_freq(int freq)
{
    CGU_REG(CGUFD) = freq;
}


/********************************************************************
* Function Name :   cgu_set_system_freq
* Description   :   set system clock frequency
* Input         :   - freq -
* Output        :   none
* Return        :   none
********************************************************************/
void cgu_set_system_freq(int freq)
{
    CGU_REG(CGUFD) = freq << 8;
}


/********************************************************************
* Function Name :   cgu_uart_enable
* Description   :   enable uart module
* Input         :   none
* Output        :   none
* Return        :   none
********************************************************************/
void cgu_uart_enable(void)
{
    volatile unsigned int RegValue = CGU_REG(CGUCR) & (~UARTEN);
    CGU_REG(CGUCR) = RegValue | UARTEN;
}


/********************************************************************
* Function Name :   cgu_iic_enable
* Description   :   enable iic module
* Input         :   none
* Output        :   none
* Return        :   none
********************************************************************/
void cgu_iic_enable(void)
{
    volatile unsigned int RegValue = CGU_REG(CGUCR) & (~IICEN);
    CGU_REG(CGUCR) = RegValue | IICEN;
}



/********************************************************************
* Function Name :   cgu_spi_enable
* Description   :   enable spi module
* Input         :   none
* Output        :   none
* Return        :   none
********************************************************************/
void cgu_spi_enable(void)
{
    volatile unsigned int RegValue = CGU_REG(CGUCR) & (~SPIEN);
    CGU_REG(CGUCR) = RegValue | SPIEN;
}



/********************************************************************
* Function Name     :   cgu_read_cpu_freq   
* Description       :   read CPU frequency
* Input         :   none
* Output        :   none
* Return        :   none
********************************************************************/
void cgu_read_cpu_freq(void)
{

}




/********************************************************************
* Function Name :   cgu_test
* Description   :   cgu driver test
* Input         :   none
* Output        :   none
* Return        :   none
********************************************************************/
void cgu_test(void)
{
    cgu_set_cpu_freq(FREQ_24MHz);
    cgu_set_system_freq(FREQ_24MHz);
    //uart_delay(3);
    cgu_set_cpu_freq(FREQ_48MHz);
    cgu_set_system_freq(FREQ_48MHz);
}




