/* See LICENSE of license details. */

#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>

#include "platform.h"
#include "stub.h"

ssize_t __wrap__read(int fd, void* ptr, size_t len)
{
  return _stub(EBADF);
}

