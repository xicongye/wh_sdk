#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include "platform.h"
#undef putchar
#define SYS_write 64
extern volatile uint64_t tohost;
extern volatile uint64_t fromhost;

#ifdef ON_SPIKE
static uintptr_t syscall(uintptr_t which, uint64_t arg0, uint64_t arg1, uint64_t arg2)
{
  volatile uint64_t magic_mem[8] __attribute__((aligned(64)));
  magic_mem[0] = which;
  magic_mem[1] = arg0;
  magic_mem[2] = arg1;
  magic_mem[3] = arg2;
  __sync_synchronize();

  tohost = (uintptr_t)magic_mem;
  while (fromhost == 0)
    ;
  fromhost = 0;

  __sync_synchronize();
  return magic_mem[0];
}
#endif

int putchar(int ch)
{
#if defined (ON_SPIKE)
  static __thread char buf[64] __attribute__((aligned(64)));
  static __thread int buflen = 0;

  buf[buflen++] = ch;

  if (ch == '\n' || buflen == sizeof(buf))
  {
    syscall(SYS_write, 1, (uintptr_t)buf, buflen);
    buflen = 0;
  }
#elif defined (ON_VCS) 
   uint8_t * ch_ptr = (uint8_t*)(0x41000000);

   *ch_ptr = (uint8_t)(ch);
   asm("nop");
   asm("nop");
   asm("nop");
#elif defined (ON_BOARD)
   uart_putchar(ch);
#endif

  return 0;
}
