/*******************************************************************
*
*       PROJECT:        W01
*
*       FILENAME:       spi.h
*
*       FUNCTION:       SPI header file
*
*       AUTHOR:         yexc
*
*       DATE:           2018/11/02
*
*       IS_FINISH:      NO
*
********************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SDJ2102_SPI_H
#define SDJ2102_SPI_H

/* Includes ------------------------------------------------------------------*/
#include "platform.h"

/* Exported constants --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define GPIO_B                  0x8

#define GPIO_DATA_ADDRA         0x2
#define GPIO_CTRL_ADDRA         0x4

#define SPI_CR                  0x0
#define SPI_SR                  0x1
#define SPI_DATA_L              0x2
#define SPI_DATA_H              0x3
#define SPI_ADDRA               SPI_CTRL_ADDR

/* Exported types ------------------------------------------------------------*/
typedef struct spi_init{
       char spi_cr;
       char spi_sr;
       char spi_dl;
       char spi_dh;
}spit;


/* Exported functions ------------------------------------------------------- */
void oled_power_enable(unsigned char gpio_class, unsigned char gpio_pin);
void spi_dr_l(unsigned char datal);
void spi_dr_h(unsigned char datah);
void spi_data_ctr(unsigned char pin7);
void spi_init(unsigned char cr, unsigned char sr);
void spi_send_byte(unsigned char datah, unsigned char datal);
void spi_delay(int n);
short int spi_receive_data(void);
void oled_thread_trg(void);

#endif

