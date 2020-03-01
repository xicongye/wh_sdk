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

//  if (read_csr(misa) & (1 << ('F' - 'A'))) { // if F extension is present
//    write_csr(mstatus, MSTATUS_FS); // allow FPU instructions without trapping
//    write_csr(fcsr, 0); // initialize rounding mode, undefined at reset
//  }
  #endif
}

void _fini(void)
{
}

