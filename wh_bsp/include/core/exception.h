/*******************************************************************************
*
*   PROJECT:    SDJ2102
*
*   FILENAME:   exception.h 
*
*   FUNCTION:   list the any possible exception in sdj2102 core
*
*   AUTHOR:     liaoll
*
*   DATE:       2017/09/05
*
*   ISFINISH:   NO
*******************************************************************************/

#ifndef SDJ2102_EXCEPTION_H
/*more infomation seed the document: The RISC-V Instruction Set Manual Volumn II: Privileged Architecture*/
#define I_ADDR_MISALIGNED   0 // instrcution address misaligned
#define I_ACCE_FAULT        1 // instrcution access fault
#define I_INSTRUCTION       2 // illegal instruction
#define BREAKPOINT          3 // breakpoint
#define L_ACCE_FAULT        5 // load access fault
#define A_ADDR_MISALIGNED   6 // AMO address misaligned
#define S_ACCE_FAULT        7 // Store/AMO access fault
#define E_CALL              8 // Environment call
#define I_PAGE_FAULT        12// Instrcution page fault
#define L_PAGE_FAULT        13// load page fault
#define S_PAGE_FAULT        15// Store/AMO page fault


#define CAUSE_MISALIGNED_FETCH          0x0  // Instruction address misaligned
#define CAUSE_FETCH_ACCESS              0x1  // Instruction access fault
#define CAUSE_ILLEGAL_INSTRUCTION       0x2  // Illegal instruction
#define CAUSE_BREAKPOINT                0x3  // Breakpoint
#define CAUSE_MISALIGNED_LOAD           0x4  // Load address misaligned
#define CAUSE_LOAD_ACCESS               0x5  // Load access fault
#define CAUSE_MISALIGNED_STORE          0x6  // Store/AMO address misaligned
#define CAUSE_STORE_ACCESS              0x7  // Store/AMO access fault
#define CAUSE_USER_ECALL                0x8  // Environment call from U-mode
#define CAUSE_SUPERVISOR_ECALL          0x9  // Environment call from S-mode
#define CAUSE_MACHINE_ECALL             0xb  // Environment call from M-mode
#define CAUSE_FETCH_PAGE_FAULT          0xc  // Instruction page fault
#define CAUSE_LOAD_PAGE_FAULT           0xd  // Load page fault
#define CAUSE_STORE_PAGE_FAULT          0xf  // Store/AMO page fault

#endif //SDJ2102_EXCEPTION_H
