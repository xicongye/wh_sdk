/********************************************************************
*
*   PROJECT:    WH
*
*   FILENAME:   privilege.h
*
*   FUNCTION:   API for manipulating the privilege mode of a RISC-V system
*
*   AUTHOR:     yexc
*
*   DATE:       2019/07/16
*
*   VERSION:    v0.1
*
*   IS_FINISH:  NO
*********************************************************************/
/* Define to prevent recursive inclusion --------------------------*/
#ifndef SDJ2102_PRIV_H
#define SDJ2102_PRIV_H

/* Exported constants ---------------------------------------------*/
/* Includes -------------------------------------------------------*/
#include "platform.h"

/* Exported variables ---------------------------------------------*/
/* Exported macro -------------------------------------------------*/
/* Exported type --------------------------------------------------*/
typedef void (*privilege_entry_point_t)();
/* Exported functions ---------------------------------------------*/
void privilege_drop_to_mode(int privilege_mode, privilege_entry_point_t entry_point, int relocate_sp_flag);
void mem_privilege_drop_to_mode(int privilege_mode, int relocate_sp_flag);
/*
#define  privilege_drop_to_mode(privilege_mode, entry_point) { \
    unsigned long _mstatus = read_csr(mstatus); \
    unsigned long satp = read_csr(satp); \
    void * sp_val; \
    void * s0_val; \
    _mstatus = INSERT_FIELD(_mstatus, MSTATUS_MPP, privilege_mode); \
    _mstatus = INSERT_FIELD(_mstatus, MSTATUS_MPIE, 0); \
    write_csr(mstatus, _mstatus); \
    write_csr(mepc, entry_point); \
    if((satp >> SATP_MODE_BIT) & SATP_MODE_MASK) { \
      asm volatile("mv %0,sp":"=r"(sp_val)); \
      asm volatile("mv %0,s0":"=r"(s0_val)); \
      sp_val = addrMap_sv32(2,sp_val,1,1,1,0,1); \
      s0_val = (void *) (((unsigned int )s0_val & PAGE_OFFSET_MASK ) | (((unsigned int )sp_val >> VADDR_VPN0_BIT ) << VADDR_VPN0_BIT)); \
      asm volatile("mv sp,%0"::"r"(sp_val)); \
      asm volatile("mv s0,%0"::"r"(s0_val)); \
    } \
    asm volatile("fence.i"); \
    asm volatile ("mret"); \
}
*/

#endif /*SDJ2102_PRIV_H*/
