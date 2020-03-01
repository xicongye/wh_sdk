/********************************************************************
*
*   PROJECT:    SDJ2102
*
*   FILENAME:   plic.h
*
*   FUNCTION:   define the interface for the platform level
*               interrupt
*
*   AUTHOR:     liaoll
*
*   DATE:       2017/08/04
*
*   VERSION:    v0.1
*
*   IS_FINISH:  NO
*********************************************************************/
/* Define to prevent recursive inclusion --------------------------*/
#ifndef SDJ2102_PLIC_H
#define SDJ2102_PLIC_H

/* Exported constants ---------------------------------------------*/
/* Includes -------------------------------------------------------*/
#include "platform.h"

/* Exported macro -------------------------------------------------*/
/* interrupt priority: 4Byte for each interrupr source */
//#define PLIC_PRIORITY_OFFSET      _CONNECT(0x0004,UL)
#define PLIC_PRIORITY_OFFSET        _CONNECT(0x0000,UL)
#define PLIC_PRIORITY_SIZE          PLIC_NUM<<2

/*interrupt pending array: 1 bits for each interrupt source */
#define PLIC_PENDING_OFFSET         _CONNECT(0x1000,UL)

/* interrupt enable: 1 bits for each interrupt source   */
#define PLIC_ENABLE_OFFSET          _CONNECT(0x2000,UL)
#define PLIC_ENABLE_SIZE            (PLIC_NUM>>3)+1

/* priority threshold */
#define PLIC_THRESHOLD_OFFSET       _CONNECT(0x200000,UL)
#define PLIC_CLAIM_OFFSET           _CONNECT(0x200004,UL)


/* Exported type --------------------------------------------------*/
typedef void (*global_int_handler)(void);

/* Exported variables ---------------------------------------------*/
extern global_int_handler global_THF[PLIC_NUM];

/* Exported functions ---------------------------------------------*/
/* global interrupt interface */
void memzero(void *base_addr,unsigned int size);
void global_int_init();
void global_int_enable(int id);
void global_int_disable(int id);
void global_int_priority(int id,int priority);
void global_int_threshold(int priority);
void global_int_bind_handler(int id, void (*handle_function)());

#endif /*SDJ2102_PLIC_H*/
