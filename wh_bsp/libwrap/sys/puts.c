/* See LICENSE of license details. */

#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

#include "platform.h"
#include "stub.h"

int __wrap_puts(const char *s)
{
   while(*s != '\0')
     putchar(*s++);
   putchar('\n');

  return 0;
}
