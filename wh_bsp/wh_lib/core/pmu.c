/****************************************************
 * 
 * PROJECT:     WH
 *
 * FILENAME:    pmu.c
 *
 * FUNCTION:    implement API of Performance Monitor Unit
 *
 * DATE:        2019-12-10
 *
 * RREVISION
 *
 *****************************************************/
#include "platform.h"
#include "stdio.h"

uint64_t val_pre[32] = {0};
uint64_t val_new[32] = {0};

void pmu_counter_enable(int Priv, int Idx) {
  int value = 1 << Idx;
  if (Priv == M_MODE)
   set_csr(mcounteren,value);
  else
   set_csr(scounteren,value);
  return;
}


void pmu_counter_disable(int Priv, int Idx) {
  int value = 1 << Idx;
  if (Priv == M_MODE)
    clear_csr(mcounteren,value);
  else
    clear_csr(scounteren,value);
  return;
}

void pmu_set_event_monitor(int Idx, int EventClass, int Event) {
  int value = EventClass & PMU_EVENT_CLASS_MASK | Event & PMU_EVENT_MASK;
  switch (Idx) {
    case 0x03: write_csr(mhpmevent3,value);break;
    case 0x04: write_csr(mhpmevent4,value);break;
    case 0x05: write_csr(mhpmevent5,value);break;
    case 0x06: write_csr(mhpmevent6,value);break;
    case 0x07: write_csr(mhpmevent7,value);break;
    case 0x08: write_csr(mhpmevent8,value);break;
    case 0x09: write_csr(mhpmevent9,value);break;
    case 0x0a: write_csr(mhpmevent10,value);break;
    case 0x0b: write_csr(mhpmevent11,value);break;
    case 0x0c: write_csr(mhpmevent12,value);break;
    case 0x0d: write_csr(mhpmevent13,value);break;
    case 0x0e: write_csr(mhpmevent14,value);break;
    case 0x0f: write_csr(mhpmevent15,value);break;
    case 0x10: write_csr(mhpmevent16,value);break;
    case 0x11: write_csr(mhpmevent17,value);break;
    case 0x12: write_csr(mhpmevent18,value);break;
    case 0x13: write_csr(mhpmevent19,value);break;
    case 0x14: write_csr(mhpmevent20,value);break;
    case 0x15: write_csr(mhpmevent21,value);break;
    case 0x16: write_csr(mhpmevent22,value);break;
    case 0x17: write_csr(mhpmevent23,value);break;
    case 0x18: write_csr(mhpmevent24,value);break;
    case 0x19: write_csr(mhpmevent25,value);break;
    case 0x1a: write_csr(mhpmevent26,value);break;
    case 0x1b: write_csr(mhpmevent27,value);break;
    case 0x1c: write_csr(mhpmevent28,value);break;
    case 0x1d: write_csr(mhpmevent29,value);break;
    case 0x1e: write_csr(mhpmevent30,value);break;
    case 0x1f: write_csr(mhpmevent31,value);break;
    default: break;
  }
}

void pmu_clear_event_monitor(int Idx) {
  switch (Idx) {
    case 0x03: write_csr(mhpmevent3,0);break;
    case 0x04: write_csr(mhpmevent4,0);break;
    case 0x05: write_csr(mhpmevent5,0);break;
    case 0x06: write_csr(mhpmevent6,0);break;
    case 0x07: write_csr(mhpmevent7,0);break;
    case 0x08: write_csr(mhpmevent8,0);break;
    case 0x09: write_csr(mhpmevent9,0);break;
    case 0x0a: write_csr(mhpmevent10,0);break;
    case 0x0b: write_csr(mhpmevent11,0);break;
    case 0x0c: write_csr(mhpmevent12,0);break;
    case 0x0d: write_csr(mhpmevent13,0);break;
    case 0x0e: write_csr(mhpmevent14,0);break;
    case 0x0f: write_csr(mhpmevent15,0);break;
    case 0x10: write_csr(mhpmevent16,0);break;
    case 0x11: write_csr(mhpmevent17,0);break;
    case 0x12: write_csr(mhpmevent18,0);break;
    case 0x13: write_csr(mhpmevent19,0);break;
    case 0x14: write_csr(mhpmevent20,0);break;
    case 0x15: write_csr(mhpmevent21,0);break;
    case 0x16: write_csr(mhpmevent22,0);break;
    case 0x17: write_csr(mhpmevent23,0);break;
    case 0x18: write_csr(mhpmevent24,0);break;
    case 0x19: write_csr(mhpmevent25,0);break;
    case 0x1a: write_csr(mhpmevent26,0);break;
    case 0x1b: write_csr(mhpmevent27,0);break;
    case 0x1c: write_csr(mhpmevent28,0);break;
    case 0x1d: write_csr(mhpmevent29,0);break;
    case 0x1e: write_csr(mhpmevent30,0);break;
    case 0x1f: write_csr(mhpmevent31,0);break;
    default: break;
  }
}


void pmu_clear_all_event_monitor(void) {
    asm volatile( "csrw mhpmevent3, zero");
    asm volatile( "csrw mhpmevent4, zero");
    asm volatile( "csrw mhpmevent5, zero");
    asm volatile( "csrw mhpmevent6, zero");
    asm volatile( "csrw mhpmevent7, zero");
    asm volatile( "csrw mhpmevent8, zero");
    asm volatile( "csrw mhpmevent9, zero");
    asm volatile( "csrw mhpmevent10, zero");
    asm volatile( "csrw mhpmevent11, zero");
    asm volatile( "csrw mhpmevent12, zero");
    asm volatile( "csrw mhpmevent13, zero");
    asm volatile( "csrw mhpmevent14, zero");
    asm volatile( "csrw mhpmevent15, zero");
    asm volatile( "csrw mhpmevent16, zero");
    asm volatile( "csrw mhpmevent17, zero");
    asm volatile( "csrw mhpmevent18, zero");
    asm volatile( "csrw mhpmevent19, zero");
    asm volatile( "csrw mhpmevent20, zero");
    asm volatile( "csrw mhpmevent21, zero");
    asm volatile( "csrw mhpmevent22, zero");
    asm volatile( "csrw mhpmevent23, zero");
    asm volatile( "csrw mhpmevent24, zero");
    asm volatile( "csrw mhpmevent25, zero");
    asm volatile( "csrw mhpmevent26, zero");
    asm volatile( "csrw mhpmevent27, zero");
    asm volatile( "csrw mhpmevent28, zero");
    asm volatile( "csrw mhpmevent29, zero");
    asm volatile( "csrw mhpmevent30, zero");
    asm volatile( "csrw mhpmevent31, zero");
}

uint64_t pmu_read_counter(int Priv, int Idx) {
  unsigned long lo;
  unsigned long hi;

  if(Priv == M_MODE) {
    switch(Idx) {
    case 0x00:  
      asm("csrr %0, mcycle" : "=r"(lo)); 
    #if __riscv_xlen == 32 
      asm("csrr %0, mcycleh" : "=r"(hi));
    #endif
      break; 
    case 0x01:
      asm("csrr %0, time" : "=r"(lo));
    #if __riscv_xlen == 32 
      asm ("csrr %0, timeh" : "=r"(hi));
    #endif
      break;	  
    case 0x02:
      asm("csrr %0, minstret" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, minstreth" : "=r"(hi));
    #endif 
      break;
    case 0x03:
      asm("csrr %0, mhpmcounter3" : "=r"(lo));
    #if __riscv_xlen == 32 
      asm("csrr %0, mhpmcounter3h" : "=r"(hi));
    #endif
      break;
    case 0x04:
      asm("csrr %0, mhpmcounter4" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, mhpmcounter4h" : "=r"(hi));
    #endif
      break;
    case 0x05:
      asm("csrr %0, mhpmcounter5" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, mhpmcounter5h" : "=r"(hi));
    #endif
      break;
    case 0x06:
      asm("csrr %0, mhpmcounter6" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, mhpmcounter6h" : "=r"(hi));
    #endif
      break; 
    case 0x07:
      asm("csrr %0, mhpmcounter7" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, mhpmcounter7h" : "=r"(hi));
    #endif
      break;
    case 0x08:
      asm("csrr %0, mhpmcounter8" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, mhpmcounter8h" : "=r"(hi));
    #endif
      break;
    case 0x09:
      asm("csrr %0, mhpmcounter9" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, mhpmcounter9h" : "=r"(hi));
    #endif
      break;
    case 0x0a:
      asm("csrr %0, mhpmcounter10" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, mhpmcounter10h" : "=r"(hi));
    #endif
      break;
    case 0x0b:
      asm("csrr %0, mhpmcounter11" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, mhpmcounter11h" : "=r"(hi));
    #endif
      break;
    case 0x0c:
      asm("csrr %0, mhpmcounter12" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, mhpmcounter12h" : "=r"(hi));
    #endif
      break;
    case 0x0d:
      asm("csrr %0, mhpmcounter13" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, mhpmcounter13h" : "=r"(hi));
    #endif
      break;
    case 0x0e:
      asm("csrr %0, mhpmcounter14" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, mhpmcounter14h" : "=r"(hi));
    #endif
      break;
    case 0x0f:
      asm("csrr %0, mhpmcounter15" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, mhpmcounter15h" : "=r"(hi));
    #endif
      break;
    case 0x10:
      asm("csrr %0, mhpmcounter16" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, mhpmcounter16h" : "=r"(hi));
    #endif
      break;
    case 0x11:
      asm("csrr %0, mhpmcounter17" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, mhpmcounter17h" : "=r"(hi));
    #endif
      break;
    case 0x12:
      asm("csrr %0, mhpmcounter18" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, mhpmcounter18h" : "=r"(hi));
    #endif
      break;
    case 0x13:
      asm("csrr %0, mhpmcounter19" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, mhpmcounter19h" : "=r"(hi));
    #endif
      break;
    case 0x14:
      asm("csrr %0, mhpmcounter20" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, mhpmcounter20h" : "=r"(hi));
    #endif
      break;
    case 0x15:
      asm("csrr %0, mhpmcounter21" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, mhpmcounter21h" : "=r"(hi));
    #endif
      break;
    case 0x16:
      asm("csrr %0, mhpmcounter22" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, mhpmcounter22h" : "=r"(hi));
    #endif
      break;
    case 0x17:
      asm("csrr %0, mhpmcounter23" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, mhpmcounter23h" : "=r"(hi));
    #endif
      break;
    case 0x18:
      asm("csrr %0, mhpmcounter24" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, mhpmcounter24h" : "=r"(hi));
    #endif
      break;
    case 0x19:
      asm("csrr %0, mhpmcounter25" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, mhpmcounter25h" : "=r"(hi));
    #endif
      break;
    case 0x1a:
      asm("csrr %0, mhpmcounter26" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, mhpmcounter26h" : "=r"(hi));
    #endif
      break;
    case 0x1b:
      asm("csrr %0, mhpmcounter27" : "=r"(lo));
    #if __riscv_xlen == 32
     asm("csrr %0, mhpmcounter27h" : "=r"(hi));
    #endif
     break;
    case 0x1c:
      asm("csrr %0, mhpmcounter28" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, mhpmcounter28h" : "=r"(hi));
    #endif
      break;
    case 0x1d:
      asm("csrr %0, mhpmcounter29" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, mhpmcounter29h" : "=r"(hi));
    #endif
      break;
    case 0x1e:
      asm("csrr %0, mhpmcounter30" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, mhpmcounter30h" : "=r"(hi));
    #endif
      break;
    case 0x1f:
      asm("csrr %0, mhpmcounter31" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, mhpmcounter31h" : "=r"(hi));
    #endif
      break;
    default: break;
    }
  } else {
  switch (Idx) {
    case 0x00:
      asm("csrr %0, cycle" : "=r"(lo));
    #if __riscv_xlen== 32 
      asm("csrr %0, cycleh" : "=r"(hi));
    #endif
      break;
    case 0x01:
      asm("csrr %0, time" : "=r"(lo));
    #if __riscv_xlen == 32 
      asm ("csrr %0, timeh" : "=r"(hi));
    #endif
      break;
    case 0x02:
      asm("csrr %0, instret" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, instreth" : "=r"(hi));
    #endif
      break;
    case 0x03:
      asm("csrr %0, hpmcounter3" : "=r"(lo));
    #if __riscv_xlen == 32 
      asm("csrr %0, hpmcounter3h" : "=r"(hi));
    #endif
      break;
    case 0x04:
      asm("csrr %0, hpmcounter4" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, hpmcounter4h" : "=r"(hi));
    #endif
      break;
    case 0x05:
      asm("csrr %0, hpmcounter5" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, hpmcounter5h" : "=r"(hi));
    #endif
      break;
    case 0x06:
      asm("csrr %0, hpmcounter6" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, hpmcounter6h" : "=r"(hi));
    #endif
      break;
    case 0x07:
      asm("csrr %0, hpmcounter7" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, hpmcounter7h" : "=r"(hi));
    #endif
      break;
    case 0x08:
      asm("csrr %0, hpmcounter8" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, hpmcounter8h" : "=r"(hi));
    #endif
      break;
    case 0x09:
      asm("csrr %0, hpmcounter9" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, hpmcounter9h" : "=r"(hi));
    #endif
      break;
    case 0x0a:
      asm("csrr %0, hpmcounter10" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, hpmcounter10h" : "=r"(hi));
    #endif
      break;
    case 0x0b:
      asm("csrr %0, hpmcounter11" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, hpmcounter11h" : "=r"(hi));
    #endif
      break;
    case 0x0c:
      asm("csrr %0, hpmcounter12" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, hpmcounter12h" : "=r"(hi));
    #endif
      break;
    case 0x0d:
      asm("csrr %0, hpmcounter13" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, hpmcounter13h" : "=r"(hi));
    #endif
      break;
    case 0x0e:
      asm("csrr %0, hpmcounter14" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, hpmcounter14h" : "=r"(hi));
    #endif
      break;
    case 0x0f:
      asm("csrr %0, hpmcounter15" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, hpmcounter15h" : "=r"(hi));
    #endif
      break;
    case 0x10:
      asm("csrr %0, hpmcounter16" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, hpmcounter16h" : "=r"(hi));
    #endif
      break;
    case 0x11:
      asm("csrr %0, hpmcounter17" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, hpmcounter17h" : "=r"(hi));
    #endif
      break;
    case 0x12:
      asm("csrr %0, hpmcounter18" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, hpmcounter18h" : "=r"(hi));
    #endif
      break;
    case 0x13:
      asm("csrr %0, hpmcounter19" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, hpmcounter19h" : "=r"(hi));
    #endif
      break;
    case 0x14:
      asm("csrr %0, hpmcounter20" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, hpmcounter20h" : "=r"(hi));
    #endif
      break;
    case 0x15:
      asm("csrr %0, hpmcounter21" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, hpmcounter21h" : "=r"(hi));
    #endif
      break;
    case 0x16:
      asm("csrr %0, hpmcounter22" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, hpmcounter22h" : "=r"(hi));
    #endif
      break;
    case 0x17:
      asm("csrr %0, hpmcounter23" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, hpmcounter23h" : "=r"(hi));
    #endif
      break;
    case 0x18:
      asm("csrr %0, hpmcounter24" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, hpmcounter24h" : "=r"(hi));
    #endif
      break;
    case 0x19: 
      asm("csrr %0, hpmcounter25" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, hpmcounter25h" : "=r"(hi));
    #endif
      break;
    case 0x1a:
      asm("csrr %0, hpmcounter26" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, hpmcounter26h" : "=r"(hi));
    #endif
      break;
    case 0x1b:
      asm("csrr %0, hpmcounter27" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, hpmcounter27h" : "=r"(hi));
    #endif
      break;
    case 0x1c:
      asm("csrr %0, hpmcounter28" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, hpmcounter28h" : "=r"(hi));
    #endif
      break;
    case 0x1d:
      asm("csrr %0, hpmcounter29" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, hpmcounter29h" : "=r"(hi));
    #endif
      break;
    case 0x1e:
      asm("csrr %0, hpmcounter30" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, hpmcounter30h" : "=r"(hi));
    #endif
      break;
    case 0x1f:
      asm("csrr %0, hpmcounter31" : "=r"(lo));
    #if __riscv_xlen == 32
      asm("csrr %0, hpmcounter31h" : "=r"(hi));
    #endif
      break;
    default:
      break;
    }
  }
  #if __riscv_xlen == 32
  return (uint64_t)(hi) << 32 | lo;
  #else
  return lo;
  #endif
}


int pmu_enable_all_counter(int Priv)
{
  if (Priv == M_MODE)
   write_csr(mcounteren, -1);
  else
   write_csr(scounteren, -1);
}

int pmu_disable_all_counter(int Priv)
{
  if (Priv == M_MODE)
   write_csr(mcounteren, 0);
  else
   write_csr(scounteren, 0);
}

void pmu_setup_all_event(void)
{
    // drop PMU_INST_EVENT_XCPT/PMU_INST_EVENT_SYSTEM
    pmu_set_event_monitor(3, PMU_INST_COMMIT_EVENT, PMU_INST_EVENT_INT_LOAD);
    pmu_set_event_monitor(4, PMU_INST_COMMIT_EVENT, PMU_INST_EVENT_INT_STORE        );
    pmu_set_event_monitor(5, PMU_INST_COMMIT_EVENT, PMU_INST_EVENT_AMO              );
    pmu_set_event_monitor(6, PMU_INST_COMMIT_EVENT, PMU_INST_EVENT_INT_ARITH        );
    pmu_set_event_monitor(7, PMU_INST_COMMIT_EVENT, PMU_INST_EVENT_BRANCH           );
    pmu_set_event_monitor(8, PMU_INST_COMMIT_EVENT, PMU_INST_EVENT_JAL              );
    pmu_set_event_monitor(9, PMU_INST_COMMIT_EVENT, PMU_INST_EVENT_JALR             );
    pmu_set_event_monitor(10, PMU_INST_COMMIT_EVENT, PMU_INST_EVENT_INT_MUL          );
    pmu_set_event_monitor(11, PMU_INST_COMMIT_EVENT, PMU_INST_EVENT_INT_DIV          );
    pmu_set_event_monitor(12, PMU_INST_COMMIT_EVENT, PMU_INST_EVENT_FLOAT_LOAD       );
    pmu_set_event_monitor(13, PMU_INST_COMMIT_EVENT, PMU_INST_EVENT_FLOAT_STORE      );
    pmu_set_event_monitor(14, PMU_INST_COMMIT_EVENT, PMU_INST_EVENT_FLOAT_ADD        );
    pmu_set_event_monitor(15, PMU_INST_COMMIT_EVENT, PMU_INST_EVENT_FLOAT_MUL        );
    pmu_set_event_monitor(16, PMU_INST_COMMIT_EVENT, PMU_INST_EVENT_FLOAT_MADD       );
    pmu_set_event_monitor(17, PMU_INST_COMMIT_EVENT, PMU_INST_EVENT_FLOAT_SQUARE     );
    pmu_set_event_monitor(18, PMU_INST_COMMIT_EVENT, PMU_INST_EVENT_OTHER_FLOAT      );

    // drop PMU_ARCH_EVENT_FLUSH_PIPE_CSR
    pmu_set_event_monitor(19, PMU_ARCH_EVENT, PMU_ARCH_EVENT_LOAD_USE);
    pmu_set_event_monitor(20, PMU_ARCH_EVENT, PMU_ARCH_EVENT_LONG_LATENCY     );
    pmu_set_event_monitor(21, PMU_ARCH_EVENT, PMU_ARCH_EVENT_CSR_LATENCY      );
    pmu_set_event_monitor(22, PMU_ARCH_EVENT, PMU_ARCH_EVENT_ICACHE_BUSY      );
    pmu_set_event_monitor(23, PMU_ARCH_EVENT, PMU_ARCH_EVENT_DCACHE_BUSY      );
    pmu_set_event_monitor(24, PMU_ARCH_EVENT, PMU_ARCH_EVENT_BR_MISPRED       );
    pmu_set_event_monitor(25, PMU_ARCH_EVENT, PMU_ARCH_EVENT_BRJM_MISPRED     );
    pmu_set_event_monitor(26, PMU_ARCH_EVENT, PMU_ARCH_EVENT_FLUSH_PIPE_OTHER );
    pmu_set_event_monitor(27, PMU_ARCH_EVENT, PMU_ARCH_EVENT_INT_MULT_ILOCK   );
    pmu_set_event_monitor(28, PMU_ARCH_EVENT, PMU_ARCH_EVENT_FP_ILOCK         );

    // drop PMU_MEM_EVENT_ITLB_MISS/PMU_MEM_EVENT_DTLB_MISS
    pmu_set_event_monitor(29, PMU_MEM_SYS_EVENT, PMU_MEM_EVENT_ICACHE_MISS);
    pmu_set_event_monitor(30, PMU_MEM_SYS_EVENT, PMU_MEM_EVENT_DCACHE_MISS       );
    pmu_set_event_monitor(31, PMU_MEM_SYS_EVENT, PMU_MEM_EVENT_DCACHE_WB         );
}

void pmu_get_all_counter(int Priv, uint64_t * counterPtr)
{
    for(int i = 0; i < 32; i++)
      *counterPtr++ = pmu_read_counter(Priv, i);
}

void pmu_print_report(uint64_t * pre, uint64_t * now)
{
    uint64_t counterVal[32];
    for(int i = 0; i < 32; i++)
      counterVal[i] = *now++ - *pre++;

    printf("-----------------------------------------------------------------------\n");
    printf("cycle :         cycye counts                   :  %llu\n", counterVal[0]);
    printf("time:           time counts                    :  %llu\n", counterVal[1]);
    printf("instret:        instruction retired            :  %llu\n", counterVal[2]);
    printf("hpmcounter3:    PMU_INST_EVENT_INT_LOAD        :  %llu\n", counterVal[3]);
    printf("hpmcounter4:    PMU_INST_EVENT_INT_STORE       :  %llu\n", counterVal[4]); 
    printf("hpmcounter5:    PMU_INST_EVENT_AMO             :  %llu\n", counterVal[5]); 
    printf("hpmcounter6:    PMU_INST_EVENT_INT_ARITH       :  %llu\n", counterVal[6]); 
    printf("hpmcounter7:    PMU_INST_EVENT_BRANCH          :  %llu\n", counterVal[7]); 
    printf("hpmcounter8:    PMU_INST_EVENT_JAL             :  %llu\n", counterVal[8]); 
    printf("hpmcounter9:    PMU_INST_EVENT_JALR            :  %llu\n", counterVal[9]); 
    printf("hpmcounter10:   PMU_INST_EVENT_INT_MUL         :  %llu\n", counterVal[10]); 
    printf("hpmcounter11:   PMU_INST_EVENT_INT_DIV         :  %llu\n", counterVal[11]); 
    printf("hpmcounter12:   PMU_INST_EVENT_FLOAT_LOAD      :  %llu\n", counterVal[12]); 
    printf("hpmcounter13:   PMU_INST_EVENT_FLOAT_STORE     :  %llu\n", counterVal[13]); 
    printf("hpmcounter14:   PMU_INST_EVENT_FLOAT_ADD       :  %llu\n", counterVal[14]); 
    printf("hpmcounter15:   PMU_INST_EVENT_FLOAT_MUL       :  %llu\n", counterVal[15]); 
    printf("hpmcounter16:   PMU_INST_EVENT_FLOAT_MADD      :  %llu\n", counterVal[16]); 
    printf("hpmcounter17:   PMU_INST_EVENT_FLOAT_SQUARE    :  %llu\n", counterVal[17]); 
    printf("hpmcounter18:   PMU_INST_EVENT_OTHER_FLOAT     :  %llu\n", counterVal[18]); 
    printf("hpmcounter19:   PMU_ARCH_EVENT_LOAD_US         :  %llu\n", counterVal[19]);
    printf("hpmcounter20:   PMU_ARCH_EVENT_LONG_LATENCY    :  %llu\n", counterVal[20]); 
    printf("hpmcounter21:   PMU_ARCH_EVENT_CSR_LATENCY     :  %llu\n", counterVal[21]); 
    printf("hpmcounter22:   PMU_ARCH_EVENT_ICACHE_BUSY     :  %llu\n", counterVal[22]); 
    printf("hpmcounter23:   PMU_ARCH_EVENT_DCACHE_BUSY     :  %llu\n", counterVal[23]); 
    printf("hpmcounter24:   PMU_ARCH_EVENT_BR_MISPRED      :  %llu\n", counterVal[24]); 
    printf("hpmcounter25:   PMU_ARCH_EVENT_BRJM_MISPRED    :  %llu\n", counterVal[25]); 
    printf("hpmcounter26:   PMU_ARCH_EVENT_FLUSH_PIPE_OTHER:  %llu\n", counterVal[26]); 
    printf("hpmcounter27:   PMU_ARCH_EVENT_INT_MULT_ILOCK  :  %llu\n", counterVal[27]); 
    printf("hpmcounter28:   PMU_ARCH_EVENT_FP_ILOCK        :  %llu\n", counterVal[28]); 
    printf("hpmcounter29:   PMU_MEM_EVENT_ICACHE_MISS      :  %llu\n", counterVal[29]);
    printf("hpmcounter30:   PMU_MEM_EVENT_DCACHE_MISS      :  %llu\n", counterVal[30]); 
    printf("hpmcounter31:   PMU_MEM_EVENT_DCACHE_WB        :  %llu\n", counterVal[31]);
    printf("-----------------------------------------------------------------------\n");
}


void pmu_start_record(void)
{
    pmu_setup_all_event();

    asm volatile("csrr %0, mcycle"   : "=r"(val_pre[0]));
    asm volatile("csrr %0, time"     : "=r"(val_pre[1]));
    asm volatile("csrr %0, minstret" : "=r"(val_pre[2]));
    asm volatile("csrr %0, mhpmcounter3" : "=r"(val_pre[3]));
    asm volatile("csrr %0, mhpmcounter4" : "=r"(val_pre[4]));
    asm volatile("csrr %0, mhpmcounter5" : "=r"(val_pre[5]));
    asm volatile("csrr %0, mhpmcounter6" : "=r"(val_pre[6]));
    asm volatile("csrr %0, mhpmcounter7" : "=r"(val_pre[7]));
    asm volatile("csrr %0, mhpmcounter8" : "=r"(val_pre[8]));
    asm volatile("csrr %0, mhpmcounter9" : "=r"(val_pre[9]));
    asm volatile("csrr %0, mhpmcounter10" : "=r"(val_pre[10]));
    asm volatile("csrr %0, mhpmcounter11" : "=r"(val_pre[11]));
    asm volatile("csrr %0, mhpmcounter12" : "=r"(val_pre[12]));
    asm volatile("csrr %0, mhpmcounter13" : "=r"(val_pre[13]));
    asm volatile("csrr %0, mhpmcounter14" : "=r"(val_pre[14]));
    asm volatile("csrr %0, mhpmcounter15" : "=r"(val_pre[15]));
    asm volatile("csrr %0, mhpmcounter16" : "=r"(val_pre[16]));
    asm volatile("csrr %0, mhpmcounter17" : "=r"(val_pre[17]));
    asm volatile("csrr %0, mhpmcounter18" : "=r"(val_pre[18]));
    asm volatile("csrr %0, mhpmcounter19" : "=r"(val_pre[19]));
    asm volatile("csrr %0, mhpmcounter20" : "=r"(val_pre[20]));
    asm volatile("csrr %0, mhpmcounter21" : "=r"(val_pre[21]));
    asm volatile("csrr %0, mhpmcounter22" : "=r"(val_pre[22]));
    asm volatile("csrr %0, mhpmcounter23" : "=r"(val_pre[23]));
    asm volatile("csrr %0, mhpmcounter24" : "=r"(val_pre[24]));
    asm volatile("csrr %0, mhpmcounter25" : "=r"(val_pre[25]));
    asm volatile("csrr %0, mhpmcounter26" : "=r"(val_pre[26]));
    asm volatile("csrr %0, mhpmcounter27" : "=r"(val_pre[27]));
    asm volatile("csrr %0, mhpmcounter28" : "=r"(val_pre[28]));
    asm volatile("csrr %0, mhpmcounter29" : "=r"(val_pre[29]));
    asm volatile("csrr %0, mhpmcounter30" : "=r"(val_pre[30]));
    asm volatile("csrr %0, mhpmcounter31" : "=r"(val_pre[31]));

    asm volatile("csrr %0, mhpmcounter4" : "=r"(val_pre[4]));
    asm volatile("csrr %0, mhpmcounter6" : "=r"(val_pre[6]));
    asm volatile("csrr %0, minstret" : "=r"(val_pre[2]));
 }

void pmu_end_record(void)
{
    asm volatile( "csrw mhpmevent3, zero");
    asm volatile( "csrw mhpmevent4, zero");
    asm volatile( "csrw mhpmevent5, zero");
    asm volatile( "csrw mhpmevent6, zero");
    asm volatile( "csrw mhpmevent7, zero");
    asm volatile( "csrw mhpmevent8, zero");
    asm volatile( "csrw mhpmevent9, zero");
    asm volatile( "csrw mhpmevent10, zero");
    asm volatile( "csrw mhpmevent11, zero");
    asm volatile( "csrw mhpmevent12, zero");
    asm volatile( "csrw mhpmevent13, zero");
    asm volatile( "csrw mhpmevent14, zero");
    asm volatile( "csrw mhpmevent15, zero");
    asm volatile( "csrw mhpmevent16, zero");
    asm volatile( "csrw mhpmevent17, zero");
    asm volatile( "csrw mhpmevent18, zero");
    asm volatile( "csrw mhpmevent19, zero");
    asm volatile( "csrw mhpmevent20, zero");
    asm volatile( "csrw mhpmevent21, zero");
    asm volatile( "csrw mhpmevent22, zero");
    asm volatile( "csrw mhpmevent23, zero");
    asm volatile( "csrw mhpmevent24, zero");
    asm volatile( "csrw mhpmevent25, zero");
    asm volatile( "csrw mhpmevent26, zero");
    asm volatile( "csrw mhpmevent27, zero");
    asm volatile( "csrw mhpmevent28, zero");
    asm volatile( "csrw mhpmevent29, zero");
    asm volatile( "csrw mhpmevent30, zero");
    asm volatile( "csrw mhpmevent31, zero");

    asm volatile("csrr %0, mcycle"   : "=r"(val_new[0]));
    asm volatile("csrr %0, time"     : "=r"(val_new[1]));
    asm volatile("csrr %0, minstret" : "=r"(val_new[2]));
    asm volatile("csrr %0, mhpmcounter3" : "=r"(val_new[3]));
    asm volatile("csrr %0, mhpmcounter4" : "=r"(val_new[4]));
    asm volatile("csrr %0, mhpmcounter5" : "=r"(val_new[5]));
    asm volatile("csrr %0, mhpmcounter6" : "=r"(val_new[6]));
    asm volatile("csrr %0, mhpmcounter7" : "=r"(val_new[7]));
    asm volatile("csrr %0, mhpmcounter8" : "=r"(val_new[8]));
    asm volatile("csrr %0, mhpmcounter9" : "=r"(val_new[9]));
    asm volatile("csrr %0, mhpmcounter10" : "=r"(val_new[10]));
    asm volatile("csrr %0, mhpmcounter11" : "=r"(val_new[11]));
    asm volatile("csrr %0, mhpmcounter12" : "=r"(val_new[12]));
    asm volatile("csrr %0, mhpmcounter13" : "=r"(val_new[13]));
    asm volatile("csrr %0, mhpmcounter14" : "=r"(val_new[14]));
    asm volatile("csrr %0, mhpmcounter15" : "=r"(val_new[15]));
    asm volatile("csrr %0, mhpmcounter16" : "=r"(val_new[16]));
    asm volatile("csrr %0, mhpmcounter17" : "=r"(val_new[17]));
    asm volatile("csrr %0, mhpmcounter18" : "=r"(val_new[18]));
    asm volatile("csrr %0, mhpmcounter19" : "=r"(val_new[19]));
    asm volatile("csrr %0, mhpmcounter20" : "=r"(val_new[20]));
    asm volatile("csrr %0, mhpmcounter21" : "=r"(val_new[21]));
    asm volatile("csrr %0, mhpmcounter22" : "=r"(val_new[22]));
    asm volatile("csrr %0, mhpmcounter23" : "=r"(val_new[23]));
    asm volatile("csrr %0, mhpmcounter24" : "=r"(val_new[24]));
    asm volatile("csrr %0, mhpmcounter25" : "=r"(val_new[25]));
    asm volatile("csrr %0, mhpmcounter26" : "=r"(val_new[26]));
    asm volatile("csrr %0, mhpmcounter27" : "=r"(val_new[27]));
    asm volatile("csrr %0, mhpmcounter28" : "=r"(val_new[28]));
    asm volatile("csrr %0, mhpmcounter29" : "=r"(val_new[29]));
    asm volatile("csrr %0, mhpmcounter30" : "=r"(val_new[30]));
    asm volatile("csrr %0, mhpmcounter31" : "=r"(val_new[31]));
    pmu_print_report(val_pre, val_new);
}


