/*******************************************************************
*
*       PROJECT:        W01
*
*       FILENAME:       spi.c
*
*       FUNCTION:       SPI driver
*
*       AUTHOR:         yexc
*
*       DATE:           2018/11/02
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
* Function Name         :       oled_power_enable
* Description           :       OLED power enable
* Input                 :       - gpio_class - 
*                               - gpio_pin -
* Output                :       none
* Return                :       none
********************************************************************/
void oled_power_enable(unsigned char gpio_class,unsigned char gpio_pin)
{
    GPIO_REG(GPIO_CTRL_ADDRA) = ((GPIO_REG(GPIO_CTRL_ADDRA) & 0x00) | (0x00 << (gpio_class >> 3)));
    GPIO_REG(GPIO_DATA_ADDRA) = ((GPIO_REG(GPIO_DATA_ADDRA) & 0x00) | gpio_pin);
}


/********************************************************************
* Function Name         :       spi_dr_l
* Description           :       set SPI low byte
* Input                 :       - datal - 
* Output                :       none
* Return                :       none
********************************************************************/
void spi_dr_l(unsigned char datal)
{
    SPI_REG(SPI_DATA_L) = datal;
}


/********************************************************************
* Function Name         :       spi_dr_h
* Description           :       set SPI high byte
* Input                 :       - datah - 
* Output                :       none
* Return                :       none
********************************************************************/
void spi_dr_h(unsigned char datah)
{
    SPI_REG(SPI_DATA_H) = datah;
}

/********************************************************************
* Function Name         :       spi_data_ctr
* Description           :       ------
* Input                 :       - pin7 - 
* Output                :       none
* Return                :       none
********************************************************************/
void spi_data_ctr(unsigned char pin7)
{
    /* ##########################################
    send_data_model _to_oled
    pin7=0x80 (send_data)
    pin7=0x00 (send_order)
    ##########################################*/
    GPIO_REG(GPIO_CTRL_ADDRA) |= 0x4;
    GPIO_REG(GPIO_DATA_ADDRA) = ( (GPIO_REG(GPIO_DATA_ADDRA)&0x00)|pin7 );
    // For JBoss
    //gpio_output_enable(GPIOC);
    //gpio_write_byte(GPIOC, pin7);
}




/********************************************************************
* Function Name         :       spi_init
* Description           :       ------
* Input                 :       - cr - 
*                       :       - sr -
* Output                :       none
* Return                :       none
********************************************************************/
void spi_init(unsigned char cr, unsigned char sr)
{
    /*##########################################
    bit_fre:
        data_bit=0xdatabit_0
        frequency=0x0_frequency ( 48/((frequency+1)*2) )
    data_sr:
        0x0_xxxx
        [2]_1_start  0_stop
        spi_struct
    ##########################################*/
    volatile spit * p = (spit *)(SPI_ADDRA);
    p->spi_cr = cr;
    p->spi_sr = sr;
}



/********************************************************************
* Function Name         :       spi_send_byte
* Description           :       ------
* Input                 :       - datah - 
*                       :       - datal -
* Output                :       none
* Return                :       none
********************************************************************/
void spi_send_byte(unsigned char datah, unsigned char datal)
{
    /*#########################################
        spi_send 16bit data
    ##########################################*/
    volatile spit * p = (spit *)(SPI_ADDRA);
    p->spi_dh = datah;
    p->spi_dl = datal;
    p->spi_sr = ((p->spi_sr) | 0x04);//start
    spi_delay(1);
    while(((p->spi_sr) | 0xfb) == 0xff);
} 



/********************************************************************
* Function Name         :       spi_receive_data
* Description           :       ------
* Input                 :       - 
* Output                :       none
* Return                :       none
********************************************************************/
short int spi_receive_data(void)
{
    /*#########################################
        receive 16 bit;
    ##########################################*/
    volatile spit *p = (spit *)(SPI_ADDRA);
    volatile int dout = 0;
    volatile int douth = 0;
    volatile int doutl = 0;
    p->spi_sr = ((p->spi_sr) | 0x04);//start
    while(((p->spi_sr) | 0xfb) == 0xff);
    douth = p->spi_dh;
    doutl = p->spi_dl;
    dout = (douth << 8) | doutl;

    return dout;
}


/********************************************************************
* Function Name         :       spi_delay
* Description           :       ------
* Input                 :       - n - 
* Output                :       none
* Return                :       none
********************************************************************/
void spi_delay(volatile int n)
{
    volatile int i;

    while(n--)
        for(i=0;i<100;i++);
}


