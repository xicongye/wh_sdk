/*************************************************************************
*
*   PROJECT:    WH
*
*   FILENAME:   pmp.c
*
*   FUNCTION:   implement the interface of PMP(Physical Memory Protection)
*
*
*   AUTHOR:     liaoll      
*
*   DATE:       2019-05-29
*
*   ISFINISH:   NO
*************************************************************************/
#include "platform.h"
//Function:PMPConfig 
//	Config the PMP Register
//Parameter:
//	index: PMP register index
//	addr:  PMP addr
//	align_mask: address aligned mask (just for NAPOT mode)
//	lock: PMPCFG.L 0/1
//	mode: PMPCFG.A OFF / TOR / NA4 / NAPOT
//	r: read privilege
//	w: write privilege
//	x: execute privilege 
void PMPConfig(int index,unsigned int addr,unsigned int align_mask,unsigned int lock,unsigned int mode,unsigned int r,unsigned int x,unsigned int w)
{
   int i = index/4;
   int j = index%4;
   unsigned int cfg = ((lock & PMP_CFG_LOCK_MASK) << PMP_CFG_LOCK_BIT) | \
                      ((mode & PMP_CFG_AREA_MASK) << PMP_CFG_AREA_BIT) | \
                      ((r & PMP_CFG_READ_MASK) << PMP_CFG_READ_BIT) | \
                      ((x & PMP_CFG_EXE_MASK) << PMP_CFG_EXE_BIT) | \
                      ((w & PMP_CFG_WRITE_MASK) << PMP_CFG_WRITE_BIT) ;

   unsigned int pmp_cfg = cfg << (j*8);
   unsigned int pmp_addr = (mode > TOR) ? (addr | align_mask >>1) >> 2 :
                           (addr >> 2) ;
   unsigned int mask = ~(0xff << (j*8)) ;

   switch(index){
        case 0 :
                asm volatile ("csrrw x0,0x3b0,%0"::"r"(pmp_addr));
                break;
        case 1 :
                asm volatile ("csrrw x0,0x3b1,%0"::"r"(pmp_addr));
                break;
        case 2 :
                asm volatile ("csrrw x0,0x3b2,%0"::"r"(pmp_addr));
                break;
        case 3 :
                asm volatile ("csrrw x0,0x3b3,%0"::"r"(pmp_addr));
                break;
        case 4 :
                asm volatile ("csrrw x0,0x3b4,%0"::"r"(pmp_addr));
                break;
        case 5 :
                asm volatile ("csrrw x0,0x3b5,%0"::"r"(pmp_addr));
                break;
        case 6 :
                asm volatile ("csrrw x0,0x3b6,%0"::"r"(pmp_addr));
                break;
        case 7 :
                asm volatile ("csrrw x0,0x3b7,%0"::"r"(pmp_addr));
                break;
        case 8 :
                asm volatile ("csrrw x0,0x3b8,%0"::"r"(pmp_addr));
                break;
        case 9 :
                asm volatile ("csrrw x0,0x3b9,%0"::"r"(pmp_addr));
                break;
        case 10:
                asm volatile ("csrrw x0,0x3ba,%0"::"r"(pmp_addr));
                break;
        case 11:
                asm volatile ("csrrw x0,0x3bb,%0"::"r"(pmp_addr));
                break;
        case 12:
                asm volatile ("csrrw x0,0x3bc,%0"::"r"(pmp_addr));
                break;
        case 13:
                asm volatile ("csrrw x0,0x3bd,%0"::"r"(pmp_addr));
                break;
        case 14:
                asm volatile ("csrrw x0,0x3be,%0"::"r"(pmp_addr));
                break;
        case 15:
                asm volatile ("csrrw x0,0x3bf,%0"::"r"(pmp_addr));
                break;
        default:
                asm volatile ("csrrw x0,0x3b0,%0"::"r"(pmp_addr));
                break;
      }

   switch(i){
        case 0:
                asm volatile ("csrr t0,0x3a0");
                asm volatile ("and t0,t0,%0" :: "r"(mask));
                asm volatile ("or  t0,t0,%0" :: "r"(pmp_cfg));
                asm volatile ("csrrw x0,0x3a0,t0");
                break;
        case 1:
                asm volatile ("csrr t0,0x3a1");
                asm volatile ("and t0,t0,%0" :: "r"(mask));
                asm volatile ("or  t0,t0,%0" :: "r"(pmp_cfg));
                asm volatile ("csrrw x0,0x3a0,t0");
                break;
        case 2:
                asm volatile ("csrr t0,0x3a2");
                asm volatile ("and t0,t0,%0" :: "r"(mask));
                asm volatile ("or  t0,t0,%0" :: "r"(pmp_cfg));
                asm volatile ("csrrw x0,0x3a0,t0");
                break;
        case 3:
                asm volatile ("csrr t0,0x3a3");
                asm volatile ("and t0,t0,%0" :: "r"(mask));
                asm volatile ("or  t0,t0,%0" :: "r"(pmp_cfg));
                asm volatile ("csrrw x0,0x3a0,t0");
                break;
        default:
                break;
   }

      return ;
}


