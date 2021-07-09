/* See LICENSE of license details. */

#include <errno.h>
#include <sys/time.h>
#include "stub.h"

#include <sys/times.h>
extern int _gettimeofday(struct timeval *, void *);
extern unsigned long long get_rtc_frequency(void);

clock_t __wrap__times(struct tms* buf)
{
    // when called for the first time, initialize t0
    static struct timeval t0; 
    if (t0.tv_sec == 0 && t0.tv_usec == 0)
        _gettimeofday (&t0, 0); 

    struct timeval t;                                                                        
    _gettimeofday (&t, 0); 

    unsigned long long timebase = get_rtc_frequency();

    long long utime = (t.tv_sec - t0.tv_sec) * 1000000 + (t.tv_usec - t0.tv_usec);
    buf->tms_utime = utime * timebase / 1000000;
    buf->tms_stime = buf->tms_cstime = buf->tms_cutime = 0;
    return 0;
}
