#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include "platform.h"

extern void trap_entry();

void _init(void) __attribute__((constructor));
void _init(void)
{
#ifndef NO_INIT
   #ifdef ON_BOARD
    uart_init(115200);
   #endif
 write_csr(mtvec, &trap_entry);
#endif
}

void _fini(void)
{

}

