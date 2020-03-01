/*******************************************************************
*
*       PROJECT:        W01
*
*       FILENAME:       cgu.h
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SDJ2102_CGU_H
#define SDJ2102_CGU_H

/* Includes ------------------------------------------------------------------*/
#include "platform.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/**************************************************************************
*                       device register memory map
***************************************************************************/
#define CGUFD           0x00        // Clock Generator Unit Frequency Divide Register
#define CGUCR           0x04        // Clock Generator Unit Control Register

/**************************************************************************
*                       register bit mask for CGUCR
***************************************************************************/
#define UARTEN          0x0001      // UART Clock Enable bit
#define IICEN           0x0002      // IIC Clock Enable bit
#define SPIEN           0x0004      // SPI Clock Enable bit
#define ADCEN           0x0008      // ADC Clock Enable bit, but ADC module not finished yet
#define DACEN           0x0010      // DAC Clock Enable bit, but DAC module not finished yet
#define SWCEN           0x0020      // SWC Clock Enable bit, but SWC module not finished yet
#define IDEL            0x0100      // IDEL Mode Enable bit, but IDEL Mode Function not finished yet
#define STOP            0x0200      // STOP Mode Enable bit, but STOP Mode Function not finished yet

/**************************************************************************
*                       frequency define
***************************************************************************/
#define FREQ_48MHz      0x01
#define FREQ_24MHz      0x03


/* External variables --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void cgu_set_cpu_freq(int freq);
void cgu_set_system_freq(int freq);
void cgu_uart_enable(void);
void cgu_iic_enable(void);
void cgu_spi_enable(void);
void cgu_test(void);

#endif /* SDJ2102_CGU_H */




