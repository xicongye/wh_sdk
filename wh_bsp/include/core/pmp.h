/********************************************************************
*
*   PROJECT:    WH32
*
*   FILENAME:   pmp.h
*
*   FUNCTION:   define the register field of PMP register and interface
*
*   AUTHOR:     liaoll
*
*   DATE:       2019-05-29
*
*   VERSION:    v0.1
*
*   IS_FINISH:  NO
*********************************************************************/

/* Define to prevent recursive inclusion --------------------------*/
#ifndef LS_PMP_H
#define LS_PMP_H

/* Includes -------------------------------------------------------*/
/* Exported constants ---------------------------------------------*/
/* Exported macro -------------------------------------------------*/
#define PMP_OFF 0
#define PMP_TOR 1
#define PMP_NA4 2
#define PMP_NAPOT 3

#define PMP_CFG_LOCK_BIT 7
#define PMP_CFG_LOCK_MASK 0x1
#define PMP_CFG_AREA_BIT 3
#define PMP_CFG_AREA_MASK 0x3
#define PMP_CFG_EXE_BIT 2
#define PMP_CFG_EXE_MASK 0x1
#define PMP_CFG_WRITE_BIT 1
#define PMP_CFG_WRITE_MASK 0x1
#define PMP_CFG_READ_BIT 0
#define PMP_CFG_READ_MASK 0x1

/* Exported functions ---------------------------------------------*/
void pmp_config(uint32_t index, uintptr_t addr, uintptr_t align_mask, uint32_t lock, uint32_t mode, uint32_t r, uint32_t x, uint32_t w);

#endif /*LS_PMP_H*/


