/* See LICENSE of license details. */

#include <errno.h>
#include "stub.h"

int __wrap__link(const char *old_name, const char *new_name)
{
  return _stub(EMLINK);
}
