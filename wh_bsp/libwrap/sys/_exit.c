/* See LICENSE of license details. */

#include <unistd.h>
#include "platform.h"
extern void write_hex(int fd, unsigned long int hex);
#ifdef ON_SPIKE
extern uint64_t tohost;
#endif

void __wrap__exit(int code)
{
  const char message[] = "\nProgram has exited with code:";

  write(STDERR_FILENO, message, sizeof(message) - 1);
  write_hex(STDERR_FILENO, code);
  write(STDERR_FILENO, "\n", 1);

#ifdef ON_SPIKE
  tohost = 1;
#endif

  for (;;);
}
