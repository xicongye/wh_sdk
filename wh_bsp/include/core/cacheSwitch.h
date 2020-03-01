/*******************************************************************
 * *
 * *       PROJECT:        W01
 * *
 * *       FILENAME:       cacheSwitch.h 
 * *
 * *       FUNCTION:       define the interface of cache switch 
 * *
 * *       AUTHOR:         liaoll
 * *
 * *       DATE:           2018/03/21
 * *
 * *       IS_FINISH:      NO
 * *
 * ********************************************************************/

/* Define to prevent recursive inclusion -----------------------------*/

#ifndef SDJ2102_CACHESWITCH_H
#define SDJ2102_CACHESWITCH_H

void dcache_enable(void);
void dcache_disable(void);
int dcache_flush_block(int regs0);
void dcache_flush_all(void);

#endif /*SDJ2102_CACHESWITCH_H*/
