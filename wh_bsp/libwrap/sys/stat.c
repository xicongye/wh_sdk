/* See LICENSE of license details. */

#include <errno.h>
#include <sys/stat.h>
#include "stub.h"

int __wrap__stat(const char* file, struct stat* st)
{
  return _stub(EACCES);
}
