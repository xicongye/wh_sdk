/*********************************************************************************
*
*       PROJECT:        WH32_DDR 
* 
*       FILENAME:       pmp_test.c 
* 
*       FUNCTION:       pmp_test driver 
* 
*       AUTHOR:         yexc 
* 
*       DATE:           Fri May 31 09:32:52 CST 2019 
* 
*       ISFINISH:       NO 
* 
*       STATUS:  
*********************************************************************************/
#include "platform.h"
#include <stdio.h>

unsigned int * mem_ptr = (unsigned int *)(0x42000000);

int main(void)
{
    printf("PMP TEST\r\n");

    PMPConfig(0,   0x42000000, 0,   0,     0,    0,  0,  0); 
    //       index    |        |    |      |     |   |   |
    //               addr      |    |      |     |   |   |
    //                        mask  |      |     |   |   |
    //                             lock   mode   r   x   w

    PMPConfig(1,   0x43000000, 0,   1,    TOR,   1,  1,  0);
    //       index    |        |    |      |     |   |   |
    //               addr      |    |      |     |   |   |
    //                        mask  |      |     |   |   |
    //                             lock   mode   r   x   w

    printf("Attempting to write to protected address\r\n");
    *mem_ptr = 6;
}
