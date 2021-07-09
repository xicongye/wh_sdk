/*******************************************************************
*
*       PROJECT:        W01
*
*       FILENAME:       cpu.h
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SDJ2102_CPU_H
#define SDJ2102_CPU_H

/* Includes ------------------------------------------------------------------*/
#include "platform.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
unsigned long long get_cyclecount(void);
unsigned long long get_cpu_frequency(void);
unsigned long long get_rtc_frequency(void);

#endif /* SDJ2102_CPU_H */

