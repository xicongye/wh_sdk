/*******************************************************************************************
*
*	PROJECT:	SDJ2102	
*
*	FILENAME:	csr.h
*
*	FUNCTION:	define bits of some control and status register and some operation  
*			of operate control and status register
*
*	AUTHOR:		liaoll
*
*	DATE:		2017/08/02
*
*	VERSION:	v0.1
*
*********************************************************************************************/

#ifndef SDJ2102_CSR_H
#define SDJ2102_CSR_H

/* machine status register */
#define MSTATUS_UIE	(1U<<0)
#define MSTATUS_SIE	(1U<<1)
#define MSTATUS_MIE	(1U<<3)
#define MSTATUS_UPIE	(1U<<4)
#define MSTATUS_SPIE	(1U<<5)
#define MSTATUS_MPIE	(1U<<7)
#define MSTATUS_SPP	(1U<<8)
#define MSTATUS_MPP	(3U<<11)
#define MSTATUS_FS	(3U<<13)
#define MSTATUS_XS	(3U<<15)
#define MSTATUS_MPRV    (1U<<17)
#define MSTATUS_SUM	(1U<<18)
#define MSTATUS_MXR	(1U<<19)
#define MSTATUS_TVM	(1U<<20)
#define MSTATUS_TW	(1U<<21)
#define MSTATUS_TSR	(1U<<22)
#define MSTATUS_VS      (3U<<23) //VPU Enable Filed
#define MSTATUS_DD      (1U<<25) //DCache Disable Bit 
#define MSTATUS_VM	(32768U<<24)
#define MSTATUS_SD	(1U<<31)

/*m-mode interrupt enable register*/
#define MIE_USIE        (1U << 0)  //u-mode software interrupt enable
#define MIE_SSIE        (1U << 1)  //s-mode software interrupt enable
#define MIE_MSIE 	(1U << 3)  //m-mode software interrupt enable
#define MIE_UTIE        (1U << 4)  //u-mode timer interrupt enable
#define MIE_STIE        (1U << 5)  //s-mode timer interrupt enable
#define MIE_MTIE	(1U << 7)  //m-mode timer interrupt enable
#define MIE_UEIE        (1U << 8)  //u-mode external interrupt enable
#define MIE_SEIE        (1U << 9)  //s-mode external interrupt enable
#define MIE_MEIE	(1U << 11) //m-mode external interrupt enable

/*m-mode mip register*/
#define MIP_USIP            0x00000001
#define MIP_SSIP            0x00000002
#define MIP_MSIP            0x00000008
#define MIP_UTIP            0x00000010
#define MIP_STIP            0x00000020
#define MIP_MTIP            0x00000080
#define MIP_UEIP            0x00000100
#define MIP_SEIP            0x00000200
#define MIP_MEIP            0x00000800

/*m-mode cause register*/
#if __riscv_xlen == 32
#define MCAUSE_INT		0x80000000
#define MCAUSE_ECODE		0x7FFFFFFF
#else
#define MCAUSE_INT		0x8000000000000000UL
#define MCAUSE_ECODE		0x00000000000003FFUL
#endif
//exception code
#define MCAUSE_UINT_SOFT        0       // u-mode software interrupt
#define MCAUSE_SINT_SOFT        1       // s-mode software interrupt
#define MCAUSE_MINT_SOFT	3	// m-mode software interrupt
#define MCAUSE_UINT_TIMER       4       // u-mode timer interrupt
#define MCAUSE_SINT_TIMER       5       // s-mode timer interrupt
#define MCAUSE_MINT_TIMER	7	// m-mode timer interrupt
#define MCAUSE_UINT_EXT		8	// u-mode external interrupt
#define MCAUSE_SINT_EXT		9	// s-mode external interrupt
#define MCAUSE_MINT_EXT		11	// m-mode external interrupt
#define MCAUSE_MINT_LOCAL(id)	(((id)>=16) && ((id)<=31))	//local_interrupt

/*s-mode status register*/
#define SSTATUS_UIE         0x00000001
#define SSTATUS_SIE         0x00000002
#define SSTATUS_UPIE        0x00000010
#define SSTATUS_SPIE        0x00000020
#define SSTATUS_SPP         0x00000100
#define SSTATUS_FS          0x00006000
#define SSTATUS_XS          0x00018000
#define SSTATUS_SUM         0x00040000
#define SSTATUS_MXR         0x00080000
#define SSTATUS32_SD        0x80000000

/*s-mode sie register*/
#define SIE_USIE            (1U << 0)  //u-mode software interrupt enable
#define SIE_SSIE            (1U << 1)  //s-mode software interrupt enable
#define SIE_UTIE            (1U << 4)  //u-mode timer interrupt enable
#define SIE_STIE            (1U << 5)  //s-mode timer interrupt enable
#define SIE_UEIE            (1U << 8)  //u-mode extern interrupt enable
#define SIE_SEIE            (1U << 9)  //s-mode extern interrupt enable

/*s-mode sip register*/
#define SIP_USIP            (1U << 0)
#define SIP_SSIP            (1U << 1)
#define SIP_UTIP            (1U << 4)
#define SIP_STIP            (1U << 5)
#define SIP_UEIP            (1U << 8)
#define SIP_SEIP            (1U << 9)

/*s-mode cause register*/
#if __riscv_xlen == 32
#define SCAUSE_INT              0x80000000
#define SCAUSE_ECODE            0x7FFFFFFF
#else
#define SCAUSE_INT		0x8000000000000000UL
#define SCAUSE_ECODE		0x00000000000003FFUL
#endif
#define SCAUSE_UINT_SOFT        0 
#define SCAUSE_SINT_SOFT        1     
#define SCAUSE_UINT_TIMER       4 
#define SCAUSE_SINT_TIMER       5     
#define SCAUSE_UINT_EXT         8 
#define SCAUSE_SINT_EXT         9      

#define PRV_M 3
#define PRV_S 1
#define PRV_U 0

#define INSERT_FIELD(val, which, fieldval) (((val) & ~(which)) | ((fieldval) * ((which) & ~((which)-1))))

/*operate csr*/
#ifdef __GNUC__

#define read_csr(reg) ({ unsigned long __tmp; \
	asm volatile ("csrr %0, " #reg : "=r"(__tmp));\
	__tmp;})

#define write_csr(reg,val) ({\
	if(__builtin_constant_p(val) && (unsigned long)(val)<32)\
		asm volatile ("csrw " #reg ",%0" :: "i" (val));\
	else \
		asm volatile ("csrw " #reg ",%0" :: "r" (val));})

#define swap_csr(reg,val) ({ unsigned long __tmp; \
	if (__builtin_constant_p(val) && (unsigned long)(val)<32)\
		asm volatile ("csrrw %0, " #reg ",%1" : "=r"(__tmp) : "i"(val));\
	else \
		asm volatile ("csrrw %0, " #reg ",%1" : "=r"(__tmp) : "r"(val)); })

#define set_csr(reg,bit) ({ unsigned long __tmp; \
	if (__builtin_constant_p(bit) && (unsigned long)(bit)<32)\
		asm volatile ("csrrs %0, " #reg ", %1" : "=r"(__tmp) : "i"(bit));\
	else \
		asm volatile ("csrrs %0, " #reg ", %1" : "=r"(__tmp) : "r"(bit));})

#define clear_csr(reg,bit) ({ unsigned long __tmp; \
	if (__builtin_constant_p(bit) && (unsigned long)(bit)<32)\
		asm volatile ("csrrc %0, " #reg ",%1" : "=r"(__tmp) : "i"(bit));\
	else \
		asm volatile ("csrrc %0, " #reg ",%1" : "=r"(__tmp) : "r"(bit));\
	__tmp;})


#endif /* !__GNUC*/


#endif  /* SDJ2102_CSR_H */
