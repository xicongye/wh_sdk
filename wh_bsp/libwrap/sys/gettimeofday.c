#include <errno.h>
#include <sys/time.h>
#include "platform.h"

int _gettimeofday(struct timeval *tp, void *tzp)
{
    unsigned long long mcc, timebase;

    mcc = get_cyclecount();
    timebase = get_cpu_frequency();
    tp->tv_sec = mcc / timebase;
    tp->tv_usec = mcc % timebase * 1000000 / timebase;

    return 0;
}

