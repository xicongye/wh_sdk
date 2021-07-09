#include "wrap_memcpy.h"

#define unlikely(X) __builtin_expect (!!(X), 0)

void *
rvv_memcpy(void * aa, const void *  bb, size_t n)
{
  #define BODY(a, b, t) { \
    t tt = *b; \
    a++, b++; \
    *(a - 1) = tt; \
  }

  char *a = (char *)aa;
  const char *b = (const char *)bb;
  char *end = a + n;
  uintptr_t msk = sizeof (long) - 1;
  if (unlikely ((((uintptr_t)a & msk) != ((uintptr_t)b & msk))
               || n < sizeof (long)))
    {   
small:
      if (__builtin_expect (a < end, 1)) 
        while (a < end)
          BODY (a, b, char);
      return aa; 
    }   

  if (unlikely (((uintptr_t)a & msk) != 0)) 
    while ((uintptr_t)a & msk)
      BODY (a, b, char);

  long *la = (long *)a;
  const long *lb = (const long *)b;
  long *lend = (long *)((uintptr_t)end & ~msk);

  if (unlikely (la < (lend - 8)))
    {   
      while (la < (lend - 8))
        {
#if __riscv_vector
          asm volatile (
             "li t1, 8\n"
             "vsetvli t0, t1, e64, m8\n"
             "vle64.v v0, (%0)\n"
             "vse64.v v0, (%1)\n"
             :
             : "r" (lb), "r" (la)
             : "t0", "t1"
          );

          lb += 8;
          la += 8;

          asm volatile (
             "li t1, 1\n"
             "vsetvli t0, t1, e64\n"
             "vle64.v v0, (%0)\n"
             "vse64.v v0, (%1)\n"
             :
             : "r" (lb), "r" (la)
             : "t0", "t1"
          );

          lb += 1;
          la += 1;
#else
          long b0 = *lb++;
          long b1 = *lb++;
          long b2 = *lb++;
          long b3 = *lb++;
          long b4 = *lb++;
          long b5 = *lb++;
          long b6 = *lb++;
          long b7 = *lb++;
          long b8 = *lb++;
          *la++ = b0;
          *la++ = b1;
          *la++ = b2;
          *la++ = b3;
          *la++ = b4;
          *la++ = b5;
          *la++ = b6;
          *la++ = b7;
          *la++ = b8;
#endif
        }
    }

  while (la < lend)
    BODY (la, lb, long);

  a = (char *)la;
  b = (const char *)lb;
  if (unlikely (a < end))
    goto small;
  return aa;
}

