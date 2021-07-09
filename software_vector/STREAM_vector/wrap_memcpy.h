#ifndef TEST_WRAP_MEMCPY
#define TEST_WRAP_MEMCPY
 
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "csr.h"

void *rvv_memcpy(void * aa, const void *  bb, size_t n);
void *__wrap_memcpy(void *str1, const void *str2, size_t n);


#endif
