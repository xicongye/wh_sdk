/****************************************************
 * 
 * PROJECT:	WH
 *
 * FILENAME:	pmu.h
 *
 * FUNCTION:	define API of Performance Monitor Unit
 *
 * DATE:	2019-12-10
 *
 * RREVISION
 *
 ****************************************************/

#ifndef SDJ2102_PMU_H
#define SDJ2102_PMU_H

#include "platform.h"

#define COUNTER_EN(MODE) (#MODE##counteren)
//if MODE is S mode or U mode, MODE = ""
#define HPM_EVENT(MODE,IDX) (#MODE##hpmevent###IDX)
#define HPM_COUNTER(MODE,IDX) (#MODE##hpmcounter###IDX)

#define M_MODE 3 
#define S_MODE 1
#define U_MODE 0

#define PMU_EVENT_CLASS_BITS 8
#define PMU_EVENT_CLASS_MASK ((1 << PMU_EVENT_CLASS_BITS) - 1)
#define PMU_EVENT_MASK  ~PMU_EVENT_CLASS_MASK

//Performance Event Class
#define PMU_INST_COMMIT_EVENT 0
#define PMU_ARCH_EVENT 1
#define PMU_MEM_SYS_EVENT 2

//Performance Events
//Implemented Instruction Commit Events
#define PMU_INST_EVENT_XCPT 		(1 << 8)
#define PMU_INST_EVENT_INT_LOAD 	(1 << 9)
#define PMU_INST_EVENT_INT_STORE 	(1 << 10)
#define PMU_INST_EVENT_AMO 		(1 << 11)
#define PMU_INST_EVENT_SYSTEM		(1 << 12)
#define PMU_INST_EVENT_INT_ARITH	(1 << 13)
#define PMU_INST_EVENT_BRANCH		(1 << 14)
#define PMU_INST_EVENT_JAL		(1 << 15)
#define PMU_INST_EVENT_JALR		(1 << 16)
#define PMU_INST_EVENT_INT_MUL		(1 << 17)
#define PMU_INST_EVENT_INT_DIV		(1 << 18)
#define PMU_INST_EVENT_FLOAT_LOAD	(1 << 19)
#define PMU_INST_EVENT_FLOAT_STORE	(1 << 20)
#define PMU_INST_EVENT_FLOAT_ADD	(1 << 21)
#define PMU_INST_EVENT_FLOAT_MUL	(1 << 22)
#define PMU_INST_EVENT_FLOAT_MADD	(1 << 23)
#define PMU_INST_EVENT_FLOAT_SQUARE	(1 << 24)
#define PMU_INST_EVENT_OTHER_FLOAT	(1 << 25)

//Implemented Architecture Events
#define PMU_ARCH_EVENT_LOAD_USE		(1 << 8)
#define PMU_ARCH_EVENT_LONG_LATENCY	(1 << 9)
#define PMU_ARCH_EVENT_CSR_LATENCY	(1 << 10)
#define PMU_ARCH_EVENT_ICACHE_BUSY	(1 << 11)
#define PMU_ARCH_EVENT_DCACHE_BUSY	(1 << 12)
#define PMU_ARCH_EVENT_BR_MISPRED	(1 << 13)
#define PMU_ARCH_EVENT_BRJM_MISPRED	(1 << 14)
#define PMU_ARCH_EVENT_FLUSH_PIPE_CSR	(1 << 15)
#define PMU_ARCH_EVENT_FLUSH_PIPE_OTHER (1 << 16)
#define PMU_ARCH_EVENT_INT_MULT_ILOCK	(1 << 17)
#define PMU_ARCH_EVENT_FP_ILOCK		(1 << 18)

//Implement Memory System Event
#define PMU_MEM_EVENT_ICACHE_MISS	(1 << 8)
#define PMU_MEM_EVENT_DCACHE_MISS	(1 << 9)
#define PMU_MEM_EVENT_DCACHE_WB		(1 << 10)
#define PMU_MEM_EVENT_ITLB_MISS  	(1 << 11)
#define PMU_MEM_EVENT_DTLB_MISS		(1 << 12)

#define CSR_OP_WRITE 0
#define CSR_OP_READ 1
#define CSR_OP_SET 2
#define CSR_OP_CLR 3

void PMU_CounterEnable(int Priv, int Idx);
void PMU_CounterDisable(int Priv, int Idx);
void PMU_SetEventMonitor(int Idx, int EventClass, int Event);
void PMU_ClearEventMonitor(int Idx);
void PMU_ClearAllEventMonitor(void);
uint64_t PMU_ReadCounter(int Priv, int Idx);
int PMU_EnableAllCounter(int Priv);
int PMU_DisableAllCounter(int Priv);
void PMU_SetupAllEvent(void);
void PMU_GetAllCounter(int Priv, uint64_t * counterPtr);
void PMU_PrintReport(uint64_t * pre, uint64_t * now);
void PMU_StartRecord(void);
void PMU_EndRecord(void);

#endif

