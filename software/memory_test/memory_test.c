/*********************************************************************************
*
*       PROJECT:        WH32_DDR 
* 
*       FILENAME:       memory.c 
* 
*       FUNCTION:       memory driver 
* 
*       AUTHOR:         yexc 
* 
*       DATE:           Wed Aug 21 16:14:21 CST 2019 
* 
*       ISFINISH:       NO 
* 
*       STATUS:  
*********************************************************************************/
#include "platform.h"
#include "sections.h"

int main(void)
{
   volatile unsigned int * MEM_BASE = (volatile unsigned int *)(_heap_end);
   volatile unsigned int * ptr;
   volatile unsigned int sum = 0;
   volatile unsigned int loop = 0;

   printf("Leave %p ~ %p alone\r\n", _mem_base, MEM_BASE);
   printf("-------TEST START-----------------------\r\n");
   for(loop = 0; loop < 63; loop++) 
   {
     ptr = MEM_BASE + loop * 1024 * 1024;
     printf("Start test: %p ~ %p\r\n", ptr, ptr + 1024*1024);
     sum = 0;
     for(volatile unsigned int i = 0; i < 1024*1024; i++)
     {
        sum += i;
        *(ptr + i) = sum;
     }

     asm("fence.i");

     for(volatile unsigned int i = 0; i < 1024*1024; i++)
     {
        unsigned int even,odd;
        even = (i%2 == 0) ? i : i+1;
        odd  = (i%2 == 0) ? i+1 : i ;
        if(ptr[i] != ((odd)*(even/2)))
        {
          printf("%p\t index:%u,should:%u,actual:%u\n", ptr + i,i,((odd)*(even/2)),ptr[i]);
          printf("Program exit\r\n");
          return 0;
        }
     }
     printf("%p ~ %p is OK, Next 4 MiB\r\n", ptr, ptr + 1024*1024);
   }

   printf("-------TEST DONE-----------------------\r\n");
   printf("Memory range: %p ~ %p is OK, total size: %dMB\r\n", MEM_BASE, ptr + 1024*1024, loop*4);

   return 0;
}


