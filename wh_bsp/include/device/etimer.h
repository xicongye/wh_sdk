/*******************************************************************
*
*       PROJECT:        W01
*
*       FILENAME:       etimer.h
*
*       FUNCTION:       ETIMER header file
*
*       AUTHOR:         yexc
*
*       DATE:           2018/11/09
*
*       IS_FINISH:      NO
*
********************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SDJ2102_ETIMER_H
#define SDJ2102_ETIMER_H

/* Includes ------------------------------------------------------------------*/
#include "platform.h"

/* Exported constants --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define ETIMER_CR         0x0
#define CntNumLDR         0x2
#define CntNuHDR          0x3

#define ETIMER_INTSRC     0x4

#define CNTVAILDR         0x8
#define CNTVAIHDR         0x9
#define CCVAILDR          0xa
#define CCVAIHDR          0xb

#define PWMTIMVAIDR       0xc
#define PWMTIMVAIHDR      0xd
#define PWMTIMNUMLDR      0xe
#define PWMTIMNUMHDR      0xf

#define PLUSNUMLDR        0x10
#define PLUSNUMHDR        0x11
#define CYCLNUMLDR        0x12
#define CYCLNUMHDR        0x13 

/* Exported functions ------------------------------------------------------- */
void etimer_pwm_mode(int cnt,int val,int count);
void etimer_timer_mode(int cnt);
void etimer_count_mode(int cnt);
void etimer_event_mode(int cnt,char clk_edge_mode);
void etimer_pwmtest_mode(int cnt,int val,int count);

void etimer2_pwm_mode(int cnt,int val,int count);
void etimer2_timer_mode(int cnt);
void etimer2_count_mode(int cnt);
void etimer2_event_mode(int cnt,char clk_edge_mode);
void etimer2_pwmtest_mode(int cnt,int val,int count);

#endif



