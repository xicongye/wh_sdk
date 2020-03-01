/*************************************************************************************
*
*   PROJECT:    SDJ2102
*
*   FILENAME:   gpio.c  
*
*   FUNCTION:   implement the interface of gpio
*
*   AUTHOR:     liaoll
*
*   DATE:       2017/08/15
*
*   ISFINISH:   NO
*
*   STATUS:     
        1.  2017/08/20 simulation success
*************************************************************************************/
/* Includes --------------------------------------------------------*/
#include "platform.h"
#include "csr.h"

/* Private define --------------------------------------------------*/
/* Private macro ---------------------------------------------------*/
/* Private variables -----------------------------------------------*/
/* Extern variables ------------------------------------------------*/
/* Private function prototypes -------------------------------------*/
/* Private functions -----------------------------------------------*/
/********************************************************************
* Function Name :   gpio_output_enable
* Description   :   enable GPIO output functioin
* Input         :   gpio_class: GPIOA or GPIOB or GPIOC or GPIOD
* Output        :   none
* Return        :   none
********************************************************************/
void gpio_output_enable(unsigned int gpio_class)
{
    GPIO_REG(GPIO_CTRL_OFFSET) |= 0x1 << (gpio_class >> 3);
}

/********************************************************************
* Function Name :   gpio_function
* Description   :   enable GPIO input/output function
* Input         :   gpio_class: GPIOA or GPIOB or GPIOC or GPIOD
*               :   function: 0: Input, 1: Output
* Output        :   none
* Return        :   none
********************************************************************/
void gpio_function(char gpio_class ,char function)
{
    GPIO_REG(GPIO_CTRL_OFFSET) = ((GPIO_REG(GPIO_CTRL_OFFSET)&0x00)|(function << gpio_class));
}

/********************************************************************
* Function Name :   gpio_input_enable
* Description   :   enable GPIO input function
* Input         :   gpio_class: GPIOA or GPIOB or GPIOC or GPIOD
* Output        :   none
* Return        :   none
********************************************************************/
void gpio_input_enable(unsigned int gpio_class)
{
    GPIO_REG(GPIO_CTRL_OFFSET) &= ~(0x1 << (gpio_class >> 3));
}

/********************************************************************
* Function Name :   gpio_set
* Description   :   GPIO set bit
* Input         :   gpio_class: GPIOA or GPIOB or GPIOC or GPIOD
*                   gpio_pin: gpio_pin0 ~ gpio_pin7
* Output        :   none
* Return        :   none
********************************************************************/
void gpio_set(unsigned int gpio_class, unsigned int gpio_pin)
{
    GPIO_REG((GPIO_DATA_OFFSET + (unsigned long)(gpio_class >> 3))) |= gpio_pin;
}


/********************************************************************
* Function Name :   gpio_reset
* Description   :   GPIO reset bit
* Input         :   gpio_class: GPIOA or GPIOB or GPIOC or GPIOD
*                   gpio_pin: gpio_pin0 ~ gpio_pin7
* Output        :   none
* Return        :   none
********************************************************************/
void gpio_reset(unsigned int gpio_class, unsigned int gpio_pin)
{
    GPIO_REG((GPIO_DATA_OFFSET + (unsigned long)(gpio_class >> 3))) &= ~(gpio_pin) ;
}

/********************************************************************
* Function Name :   gpio_read_bit
* Description   :   read GPIO pin
* Input         :   gpio_class: GPIOA or GPIOB or GPIOC or GPIOD
*                   gpio_pin: gpio_pin0 ~ gpio_pin7
* Output        :   none
* Return        :   gpio bit
********************************************************************/
unsigned int gpio_read_bit(unsigned int gpio_class,unsigned int gpio_pin)
{
    return ((GPIO_REG((GPIO_DATA_OFFSET + (unsigned long)(gpio_class >> 3))) & (gpio_pin)) != 0);
}

/********************************************************************
* Function Name :   gpio_read_byte
* Description   :   read a byte from the whole GPIO group
* Input         :   gpio_class: GPIOA or GPIOB or GPIOC or GPIOD
* Output        :   none
* Return        :   a byte from the whole GPIO group
********************************************************************/
unsigned int gpio_read_byte(unsigned int gpio_class)
{
    return (GPIO_REG((GPIO_DATA_OFFSET + (unsigned long)(gpio_class >> 3))));
}

/********************************************************************
* Function Name :   gpio_write_byte
* Description   :   write a byte to the whole GPIO group
* Input         :   gpio_class: GPIOA or GPIOB or GPIOC or GPIOD
*                   value: the byte you want to write
* Output        :   none
* Return        :   none
********************************************************************/
void gpio_write_byte(unsigned int gpio_class,unsigned int value)
{
    GPIO_REG((GPIO_DATA_OFFSET + (unsigned long)(gpio_class >> 3))) = 
         (GPIO_REG((GPIO_DATA_OFFSET + (unsigned long)(gpio_class >> 3))) & ~(0xff)) | (value) ;
}
 
