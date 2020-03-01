/* See LICENSE of license details. */

#include <stddef.h>

extern char metal_segment_heap_target_start;
extern char metal_segment_heap_target_end;
static char *brk = &metal_segment_heap_target_start;

int
_brk(void *addr)
{
  brk = addr;
  return 0;
}

char *
__wrap__sbrk(ptrdiff_t incr)
{
  char *old = brk;

  /* If __heap_size == 0, we can't allocate memory on the heap */
  if(&metal_segment_heap_target_start == &metal_segment_heap_target_end) {
    return NULL;
  }

  /* Don't move the break past the end of the heap */
  if ((brk + incr) < &metal_segment_heap_target_end) {
    brk += incr;
  } else {
    brk = &metal_segment_heap_target_end;
  }

  return old;
}  
