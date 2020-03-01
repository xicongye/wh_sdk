/* See LICENSE of license details. */

#include <errno.h>
#include "stub.h"

int __wrap__kill(int pid, int sig)
{
  return _stub(EINVAL);
}
