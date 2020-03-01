/* See LICENSE of license details. */

#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

#include "platform.h"
#include "stub.h"

ssize_t __wrap__write(int fd, const void* ptr, size_t len)
{
  const uint8_t * current = (const char *)ptr;

  if (isatty(fd)) {
    for (size_t jj = 0; jj < len; jj++) {
	putchar(current[jj]);
    }
    return len;
  }

  return _stub(EBADF);
}
