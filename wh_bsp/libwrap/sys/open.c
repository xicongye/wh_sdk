/* See LICENSE of license details. */

#include <errno.h>
#include "stub.h"

int __wrap__open(const char* name, int flags, int mode)
{
  return _stub(ENOENT);
}
