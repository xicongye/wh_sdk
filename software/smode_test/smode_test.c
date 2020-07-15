/*********************************************************************************
*
*       PROJECT:        WH32_DDR 
* 
*       FILENAME:       make_some_noise.c 
* 
*       FUNCTION:       make_some_noise driver 
* 
*       AUTHOR:         yexc 
* 
*       DATE:           Thu Jul 11 11:24:47 CST 2019 
* 
*       ISFINISH:       NO 
* 
*       STATUS:  
*********************************************************************************/
#include "platform.h"
#include <stdlib.h>
void jump_in_and_jump_out(void);
void smode_trap_entry(void);
void handle_sint_soft(void);
void handle_sint_time(void);
void handle_sint_ext(void);
unsigned int smode_handle_trap(uintptr_t  scause, uintptr_t epc);

#define SMODE_SOFT_INT
//#define SMODE_TIME_INT


int main(void)
{
    int i = 0;
    write_csr(satp, 0x00);
    write_csr(mideleg, MIP_SSIP | MIP_STIP | MIP_SEIP);
//    global_int_init();
//    memzero((void*)(PLIC_CTRL_ADDR+PLIC_SENABLE_OFFSET),PLIC_ENABLE_SIZE);

#ifdef SMODE_TIME_INT
    set_csr(mip, MIP_STIP);
#endif


    pmp_config(0,   0x10000000, 0,   0,     0,    0,  0,  0);
    //       index    |         |    |      |     |   |   |
    //               addr       |    |      |     |   |   |
    //                         mask  |      |     |   |   |
    //                              lock   mode   r   x   w

   pmp_config(1,   0x50000000, 0,   1, PMP_TOR,  1,  1,  1);
    //       index    |        |    |      |     |   |   |
    //               addr      |    |      |     |   |   |
    //                        mask  |      |     |   |   |
    //                             lock   mode   r   x   w

    privilege_drop_to_mode(PRV_S, jump_in_and_jump_out, 0);
}

void jump_in_and_jump_out(void)
{
  write_csr(stvec, &smode_trap_entry);
  set_csr(sstatus, SSTATUS_SIE);

#ifdef SMODE_SOFT_INT
  set_csr(sie, SIE_SSIE);
  set_csr(sip, SIP_SSIP);
#endif

#ifdef SMODE_TIME_INT
  set_csr(sie, SIE_STIE);
#endif

  while(1);
}

unsigned int smode_handle_trap(uintptr_t  scause, uintptr_t epc)
{
    unsigned int temp;

    if(scause & SCAUSE_INT)             // interrupt
    {   
        temp = scause & SCAUSE_ECODE;
        if(temp == SCAUSE_SINT_EXT)         // plic interrupts
            handle_sint_ext();
        else if(temp == SCAUSE_SINT_TIMER)  // timer interrupt
            handle_sint_time();
        else if(temp == SCAUSE_SINT_SOFT)   // software interrupt
            handle_sint_soft();
    }   
    else                                // exception
        switch(scause)
        {
           case CAUSE_MISALIGNED_FETCH    : exit(0); break;      // Instruction address misaligned
           case CAUSE_FETCH_ACCESS        : exit(1); break;      // Instruction access fault
           case CAUSE_ILLEGAL_INSTRUCTION : exit(2); break;      // Illegal instruction
           case CAUSE_BREAKPOINT          : exit(3); break;      // Breakpoint
           case CAUSE_MISALIGNED_LOAD     : exit(4); break;      // Load address misaligned
           case CAUSE_LOAD_ACCESS         : exit(5); break;      // Load access fault
           case CAUSE_MISALIGNED_STORE    : exit(6); break;      // Store/AMO address misaligned
           case CAUSE_STORE_ACCESS        : exit(7); break;      // Store/AMO access fault
           case CAUSE_USER_ECALL          : exit(8); break;      // Environment call from U-mode
           case CAUSE_SUPERVISOR_ECALL    : exit(9); break;      // Environment call from S-mode
           case CAUSE_MACHINE_ECALL       : exit(11); break;     // Environment call from M-mode
           case CAUSE_FETCH_PAGE_FAULT    : exit(12); break;     // Instruction page fault
           case CAUSE_LOAD_PAGE_FAULT     : exit(13); break;     // Load page fault
           case CAUSE_STORE_PAGE_FAULT    : exit(15); break;     // Store/AMO page fault
           default: break;
        }  
                  
    return epc; 
}


void handle_sint_soft(void)
{
  clear_csr(sip, SIP_SSIP);
  printf("I'm handling S-Mode software interrupt.\r\n");
}

void handle_sint_time(void)
{
  printf("I'm handling S-Mode timer interrupt.\r\n");
  while(1);
}


void handle_sint_ext(void)
{
  printf("I'm handling S-Mode PLIC interrupt.\r\n");
  while(1);
}



