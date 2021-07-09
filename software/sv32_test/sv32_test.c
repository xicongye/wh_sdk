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

#define LEN 1024

void error(void);
void write_mem(int sel,int * vaddr);
int read_mem(int sel,int* vaddr);
void deal_virtual(void);

int main(void)
{
    sv32_enable();

    pmp_config(0,   0x70000000, 0,   0, PMP_TOR,   1,  1,  1);
    //       index    |         |    |        |     |   |   |
    //               addr       |    |        |     |   |   |
    //                         mask  |        |     |   |   |
    //                              lock     mode   r   x   w

    int data[LEN];
    int * read_mem_vaddr = (int *) sv32_addr_map(2,(void*)read_mem,1,1,1,0,1);
    int * write_mem_vaddr = (int *) sv32_addr_map(2,(void*)write_mem,1,1,1,0,1);
    int * deal_virtual_vaddr = (int*) sv32_addr_map(2,(void*)deal_virtual,1,1,1,0,1);
    int * vaddr = (int *) sv32_addr_map(2,(void*)data,1,1,1,0,1);
    int paddr = (((int)data >> PADDR_PPN0_BIT)  + 1)<<PADDR_PPN0_BIT;

    sv32_addr_map(2,(void*)(paddr),1,1,1,0,1);
    mem_privilege_drop_to_mode(1,1);
    write_mem(0,vaddr);
    read_mem(0,vaddr);

    asm("mv t4,%0"::"r"(vaddr));
    asm("mv t5,%0"::"r"(write_mem_vaddr));
    asm("mv t6,%0"::"r"(read_mem_vaddr));
    privilege_drop_to_mode(1,deal_virtual_vaddr,0);

    return 0;
}


void error(void)
{
    while(1);
}

void write_mem(int sel,int * vaddr)
{
    for(int i = 0; i < LEN; i++)
        if(sel)
           vaddr[i] = i;
        else
           vaddr[i] = 1024-i;
}

int read_mem(int sel,int* vaddr)
{
    for(int i = 0; i < LEN; i++)
        if(sel)
        {
           if(vaddr[i] != i)
               error();
        }
        else
        {
           if(vaddr[i] != (1024-i))
               error();	
        }
}

void deal_virtual(void)
{
    asm ("li a0,1");
    asm ("mv a1,t4");
    asm ("jalr ra,t5");
    asm ("li a0,1");
    asm ("mv a1,t4");
    asm ("jalr ra,t6");
    while(1);	
}


