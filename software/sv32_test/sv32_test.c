/*********************************************************************************
*
*       PROJECT:        WH32_DDR 
* 
*       FILENAME:       sv32_test.c 
* 
*       FUNCTION:       sv32_test driver 
* 
*       AUTHOR:         liaoll
* 
*       DATE:           Mon Jul 15 16:35:57 CST 2019 
* 
*       ISFINISH:       NO 
* 
*       STATUS:  
*********************************************************************************/
#include "platform.h"

void loop(void);
void pass(void);
void error(void);
volatile void handle_mtvec(void);
int write_mem(int sel,int* vaddr);
volatile int read_mem(int sel,int* vaddr);
volatile void deal_virtual(void);

int main(void)
{
    printf("\r\n");
    printf("TEST BEGIN!\r\n");
    printf("Start to test the function of sv32 system.\r\n");

    asm("mv	t4,%0"::"r"(handle_mtvec));
    asm("csrw	mtvec, t4");
    asm("csrwi	medeleg,0");
    asm("csrwi	mideleg,0");

    void * datavAddrList[1024];
    int * deal_virtual_vaddr = (int*) sv32_addr_map(2, (void*)deal_virtual, 1, 1, 1, 0, 1);
    int * read_mem_vaddr = (int *) sv32_addr_map(2, (void*)read_mem,     1, 1, 1, 0, 1);
    int * write_mem_vaddr = (int *) sv32_addr_map(2, (void*)write_mem,    1, 1, 1, 0, 1);
    int * paddr = (int*)0x40023188;
    volatile int i;
    sv32_enable();
    pmp_config(0,0x70000000,0,0,PMP_TOR,1,1,1);
    for(i = 0 ; i < 4 ; i++)
    {
       datavAddrList[i] = sv32_addr_map(     2,   (void*)paddr,      1, 1, 1, 0, 1);
       paddr = paddr + 1024 ;
    }	

    //data enter S mode
    mem_privilege_drop_to_mode(1,1);

    for(i = 0 ; i < 3 ; i++)
    {
       write_mem(0,datavAddrList[i]);
    }

    //flush all dcache block
    dcache_flush_all();	

    for(i = 0 ; i < 3 ; i++)
    {
       int vaddr = (int)datavAddrList[i];
       asm("sfence.vma %0" : : "r" (vaddr) : "memory");
       read_mem(0,datavAddrList[i]);
    }

    asm("mv t4,%0"::"r"(datavAddrList[1]));
    asm("mv t5,%0"::"r"(write_mem_vaddr));
    asm("mv t6,%0"::"r"(read_mem_vaddr));

    //instruction & data enter S mode
    privilege_drop_to_mode(1,(privilege_entry_point_t)deal_virtual_vaddr,0);

    while(1);

    return 0;
}

void loop(void)
{
    printf("TEST END!\r\n");
    printf("\r\n");
    while(1);
}

void pass(void)
{
    printf("TEST PASS!\r\n");
    asm ("li gp, 1");
    loop();
}

void error(void)
{
    printf("TEST FAIL!\r\n");
    asm ("li gp, 0");
    loop();
}

volatile void handle_mtvec(void)
{
  switch(read_csr(mcause))
  {
    case CAUSE_MISALIGNED_FETCH:    printf("Exception reason:Instruction address misaligned!\r\n"); break;
    case CAUSE_FETCH_ACCESS:        printf("Exception reason:Instruction access fault!\r\n");       break;
    case CAUSE_ILLEGAL_INSTRUCTION: printf("Exception reason:Illegal instruction!\r\n");            break;
    case CAUSE_BREAKPOINT:          printf("Exception reason:Breakpoint!\r\n");                     break;
    case CAUSE_MISALIGNED_LOAD:     printf("Exception reason:Load address misaligned!\r\n");        break;
    case CAUSE_LOAD_ACCESS:         printf("Exception reason:Load access fault!\r\n");              break;
    case CAUSE_MISALIGNED_STORE:    printf("Exception reason:Store/AMO address misaligned!\r\n");   break;
    case CAUSE_STORE_ACCESS:        printf("Exception reason:Store/AMO access fault!\r\n");         break;
    case CAUSE_USER_ECALL:          printf("Exception reason:Environment call from U-mode!\r\n");   break;
    case CAUSE_SUPERVISOR_ECALL:
          {
            printf("Environment call from S-mode!Hardware exits S-mode!\r\n");
            asm("csrr t5, mtval");
            asm("csrr t6, mepc");
            pass();
          } 
          break;
    case CAUSE_MACHINE_ECALL:       printf("Exception reason:Environment call from M-mode!\r\n");   break;
    case CAUSE_FETCH_PAGE_FAULT:    printf("Exception reason:Instruction page fault!\r\n");         break;
    case CAUSE_LOAD_PAGE_FAULT:     printf("Exception reason:Load page fault!\r\n");                break;
    case CAUSE_STORE_PAGE_FAULT:    printf("Exception reason:Store/AMO page fault!\r\n");           break;
    default: break;
   }

   error();
}

int write_mem(int sel,int* vaddr)
{
   int i;

   for(i = 0; i < 256; i++)
   {
       if(sel)
          vaddr[i] = i*2 + 1;
       else
          vaddr[i] = i*2 -1;
   }

   return 0;
}

volatile int read_mem(int sel,int* vaddr)
{
   int i;

   for(i = 0; i < 256; i++)
   {
       if(sel)
       {
          if(vaddr[i] != (i*2 + 1))
            error();
       }
       else
       {
          if(vaddr[i] != (i*2 -1))
            error();
       }
   }

   return 0;
}

volatile void deal_virtual(void)
{
        asm ("li a0,1");
        asm ("mv a1,t4");
        asm ("jalr ra,t5");	
	asm ("sfence.vma zero, t4");
        asm ("li a0,1");
        asm ("mv a1,t4");
        asm ("jalr ra,t6");
        asm ("ecall");
}



