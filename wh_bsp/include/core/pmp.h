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
#ifndef LS_PMP_H
#define LS_PMP_H

#define OFF 0
#define TOR 1
#define NA4 2
#define NAPOT 3

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

void PMPConfig(int index,unsigned int addr,unsigned int align_mask,unsigned int lock,unsigned int mode,unsigned int r,unsigned int x,unsigned int w);


#endif
