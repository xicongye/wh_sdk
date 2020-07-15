#include "csr.h"
.section .text
.global relocated_sp_s0
.type relocated_sp_s0 , @function
relocated_sp_s0:
//store ra
  mv t2,ra
//call sv32_addr_map
  li a0, 2
  li a2, 1
  li a3, 1
  li a4, 1
  li a5, 0
  li a6, 1
//Map sp
  mv a1,sp
#if __riscv_xlen == 32
  call sv32_addr_map
#endif
  mv t0,a0
//Map s0
  li a0, 2
  li a2, 1
  li a3, 1
  li a4, 1
  li a5, 0
  li a6, 1
  mv a1,s0
#if __riscv_xlen == 32
  call sv32_addr_map
#endif
  mv t1,a0
//set 
  mv sp,t0
  mv s0,t1
  mv ra,t2
  ret

.global privilege_drop_to_mode
.type privilege_drop_to_mode, @function 
# a0 -> privilege_mode
# a1 -> entry_point
# a2 -> enable
privilege_drop_to_mode:
   csrr a4, mstatus   # a4 = mstatus
   li a5, MSTATUS_MPP
   not a5, a5         # a5 = ~MSTATUS_MPP
   and a4, a4, a5
   slli a0, a0, 11    # a0 <<= 11
   or a4, a4, a0      # set MSTAUS_MPP

   li a3, MSTATUS_MPRV
   not a3, a3
   and a4, a4, a3      # clear MSTATUS_MPRV

   csrw mstatus, a4   # mstatus = a4
   csrw mepc, a1      # mepc = a1
   beqz a2,1f
   mv t4,ra
   call relocated_sp_s0 
   mv ra,t4
1:
   mret


.global mem_privilege_drop_to_mode
.type mem_privilege_drop_to_mode, @function 
# a0 -> privilege_mode
mem_privilege_drop_to_mode:
   mv t5,a0
   beqz a1,1f
   mv t4,ra 
   call relocated_sp_s0
   mv ra,t4
1:
   mv a0,t5
   csrr a4, mstatus   # a4 = mstatus
   li a5, MSTATUS_MPP
   not a5, a5         # a5 = ~MSTATUS_MPP
   and a4, a4, a5
   slli a0, a0, 11    # a0 <<= 11
   or a4, a4, a0      # set MSTATUS_MPP
   li a3, MSTATUS_MPRV
   or a4, a4, a3      # set MSTATUS_MPRV
   csrw mstatus, a4   # mstatus = a4
   ret

