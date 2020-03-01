/* See LICENSE of license details. */

#include <errno.h>
#include "stub.h"

int __wrap__fork(void)
{
  return _stub(EAGAIN);
}
