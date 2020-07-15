/*************************************************************************
*
*   PROJECT:    WH
*
*   FILENAME:   pmp.c
*
*   FUNCTION:   implement the interface of PMP(Physical Memory Protection)
*
*   AUTHOR:     liaoll      
*
*   DATE:       2019-05-29
*
*   ISFINISH:   NO
*************************************************************************/
/* Includes --------------------------------------------------------*/
#include "platform.h"
/* Private define --------------------------------------------------*/
/* Private macro ---------------------------------------------------*/
/* Private variables -----------------------------------------------*/
/* Extern variables ------------------------------------------------*/
/* Private function prototypes -------------------------------------*/
/* Private functions -----------------------------------------------*/
/********************************************************************
* Function Name :   pmp_config
* Description   :   configure pmp registers
* Input         :   - index: PMP register index
*               :   - addr: PMP address
*               :   - align_mask: address aligned mask (only for NAPOT mode)
*               :   - lock: PMPCFG.L 0/1
*               :   - mode: PMPCFG.A PMP_OFF / PMP_TOR / PMP_NA4 / PMP_NAPOT
*               :   - r: read privilege
*               :   - w: write privilege
*               :   - x: execute privilege
* Output        :   none
* Return        :   none
********************************************************************/
void pmp_config(uint32_t index, uintptr_t addr, uintptr_t align_mask, uint32_t lock, uint32_t mode, uint32_t r, uint32_t x, uint32_t w)
{
   // 8-byte NAPOT: align_mask = 0x7,  addr must be aligned to 8-bytes
   //16-byte NAPOT: align_mask = 0xf,  addr must be aligned to 16-bytes
   //32-byte NAPOT: align_mask = 0x1f, addr must be aligned to 32-bytes
   // so on
   uint32_t i = index / 4;
   uint32_t j = index % 4;
   uint32_t cfg = ((lock & PMP_CFG_LOCK_MASK) << PMP_CFG_LOCK_BIT) | \
                  ((mode & PMP_CFG_AREA_MASK) << PMP_CFG_AREA_BIT) | \
                  ((r & PMP_CFG_READ_MASK) << PMP_CFG_READ_BIT) | \
                  ((x & PMP_CFG_EXE_MASK) << PMP_CFG_EXE_BIT) | \
                  ((w & PMP_CFG_WRITE_MASK) << PMP_CFG_WRITE_BIT) ;

   uint32_t pmp_cfg = cfg << (j*8);
   uint32_t pmp_addr = (mode > PMP_TOR) ? (addr | align_mask >>1) >> 2 : (addr >> 2);
   uint32_t mask = ~(0xff << (j*8));

   switch(index){
          case 0  : write_csr(pmpaddr0, pmp_addr);  break;
          case 1  : write_csr(pmpaddr1, pmp_addr);  break;
          case 2  : write_csr(pmpaddr2, pmp_addr);  break;
          case 3  : write_csr(pmpaddr3, pmp_addr);  break;
          case 4  : write_csr(pmpaddr4, pmp_addr);  break;
          case 5  : write_csr(pmpaddr5, pmp_addr);  break;
          case 6  : write_csr(pmpaddr6, pmp_addr);  break;
          case 7  : write_csr(pmpaddr7, pmp_addr);  break;
          case 8  : write_csr(pmpaddr8, pmp_addr);  break;
          case 9  : write_csr(pmpaddr9, pmp_addr);  break;
          case 10 : write_csr(pmpaddr10, pmp_addr); break;
          case 11 : write_csr(pmpaddr11, pmp_addr); break;
          case 12 : write_csr(pmpaddr12, pmp_addr); break;
          case 13 : write_csr(pmpaddr13, pmp_addr); break;
          case 14 : write_csr(pmpaddr14, pmp_addr); break;
          case 15 : write_csr(pmpaddr15, pmp_addr); break;
          default : break;
      }

   switch(i){
        case 0:
                asm volatile ("csrr t0,pmpcfg0");
                asm volatile ("and t0,t0,%0" :: "r"(mask));
                asm volatile ("or  t0,t0,%0" :: "r"(pmp_cfg));
                asm volatile ("csrrw x0,pmpcfg0,t0");
                break;
        case 1:
                asm volatile ("csrr t0,pmpcfg1");
                asm volatile ("and t0,t0,%0" :: "r"(mask));
                asm volatile ("or  t0,t0,%0" :: "r"(pmp_cfg));
                asm volatile ("csrrw x0,pmpcfg1,t0");
                break;
        case 2:
                asm volatile ("csrr t0,pmpcfg2");
                asm volatile ("and t0,t0,%0" :: "r"(mask));
                asm volatile ("or  t0,t0,%0" :: "r"(pmp_cfg));
                asm volatile ("csrrw x0,pmpcfg2,t0");
                break;
        case 3:
                asm volatile ("csrr t0,pmpcfg3");
                asm volatile ("and t0,t0,%0" :: "r"(mask));
                asm volatile ("or  t0,t0,%0" :: "r"(pmp_cfg));
                asm volatile ("csrrw x0,pmpcfg3,t0");
                break;
        default:
                break;
   }
}                 
                  
                  
