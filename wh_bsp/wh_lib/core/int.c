/************************************************************************************
*
*   PROJECT:    SDJ2102
*
*   FILE_NAME:  int.c
*
*   FUNCTION:   int handle function
*
*   AUTHOR:     liaoll
*
*   DATE:       2017/08/04
*
*   IS_FINISH:  NO
**************************************************************************************/
/* Includes --------------------------------------------------------*/
#include "csr.h"
#include "platform.h"
#include <stdlib.h>

/* Extern prototypes -----------------------------------------------*/
extern void trap_entry();
extern void handle_mint_ext();
extern void handle_mint_time();
extern void handle_mint_local(unsigned int id);
extern void handle_mint_soft();

/* Private define --------------------------------------------------*/
/* Private macro ---------------------------------------------------*/
/* Private variables -----------------------------------------------*/
/* Extern variables ------------------------------------------------*/
/* Private function prototypes -------------------------------------*/
/* Private functions -----------------------------------------------*/
/********************************************************************
* Function Name :   handle_trap
* Description   :   handle trap function
* Input         :   macuse and epc are CSR register @trap_entry.S
* Output        :   none
* Return        :   epc -- CSR register
********************************************************************/
int  handle_trap(uintptr_t  mcause, uintptr_t epc)
{
    unsigned int temp;

    if(mcause & MCAUSE_INT)             // interrupt
    {
        temp = mcause & MCAUSE_ECODE;
        if(temp == MCAUSE_MINT_EXT)         // plic interrupts
            handle_mint_ext();
        else if(temp == MCAUSE_MINT_TIMER)  // machine timer interrupt
            handle_mint_time();
        else if(MCAUSE_MINT_LOCAL(temp))    // local interrupts
            handle_mint_local(temp-16);
        else if(temp == MCAUSE_MINT_SOFT)   // machine software interrupt
            handle_mint_soft();
    }
    else                                // exception
        switch(mcause)
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


/********************************************************************
* Function Name :   int_init
* Description   :   initialize all interrupt
* Input         :   none
* Output        :   none
* Return        :   none
********************************************************************/
void int_init(void)
{
    
    local_int_init();
    global_int_init();
    timer_int_init();
    write_csr(mtvec, &trap_entry);
    
}   


/********************************************************************
* Function Name :   int_enable
* Description   :   enable interrupt
* Input         :   none
* Output        :   none
* Return        :   none
********************************************************************/
void int_enable(void)
{
    set_csr(mstatus,MSTATUS_MIE);
}


/********************************************************************
* Function Name :   int_disable
* Description   :   disable interrupt
* Input         :   none
* Output        :   none
* Return        :   none
********************************************************************/
void int_disable(void)
{
    clear_csr(mstatus,MSTATUS_MIE);
}







