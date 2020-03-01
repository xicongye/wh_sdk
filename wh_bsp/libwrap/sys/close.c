/* See LICENSE of license details. */

#include <errno.h>
#include "stub.h"

int __wrap__close(int fd)
{
  return _stub(EBADF);
}
