/* See LICENSE of license details. */

#include <errno.h>
#include "stub.h"

int __wrap__wait(int* status)
{
  return _stub(ECHILD);
}
