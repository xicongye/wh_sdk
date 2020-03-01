/*********************************************************************
*
*       PROJECT:        WH
*
*       FILENAME:       qspi.h
*
*       FUNCTION:       define some interface for the qspi controller
*       
*       AUTHOR:         liaoll
*       
*       DATE:           2018-10-12
***************************************************************/
#ifndef WH_QSPI_H
#define WH_QSPI_H

//#include "device/qspi_instruction.h"
////////////////////////////////////////
//Agenda
/* Agenda ---------------------------------------------------------*/
/* Register Struction ---------------------------------------------*/
/* Bit Field Of Reg -----------------------------------------------*/
/* Interface ------------------------------------------------------*/

///////////////////////////////////////////////
// Register Struction 
//define the macro of the struct type name to make modify easy
#define QSPI_REG flash_register
#define QSPI_REG_P flash_register_p
typedef struct qspi_register
{
    unsigned int FlashDivide;
    unsigned short FlashCtrl;
    unsigned char FlashCSR;
    unsigned char FlashState;
    unsigned int FlashAddr;
    unsigned int FlashData;
} QSPI_REG,*QSPI_REG_P;

////////////////////////////////////////////////
//Bit Field Of Reg

//FlashCtrl Reg
#define FLASH_CTRL_EDPI   (unsigned short)( 1<<0 )
#define FLASH_CTRL_DPIDI  (unsigned short)( 1<<1 )
#define FLASH_CTRL_EQPI   (unsigned short)( 1<<2 )
#define FLASH_CTRL_QPIDI  (unsigned short)( 1<<3 )
#define FLASH_CTRL_CER    (unsigned short)( 1<<4 )
#define FLASH_CTRL_BER32  (unsigned short)( 1<<5 )
#define FLASH_CTRL_BER64  (unsigned short)( 1<<6 )
#define FLASH_CTRL_SER    (unsigned short)( 1<<7 )
#define FLASH_CTRL_RDCSR  (unsigned short)( 1<<8 )
#define FLASH_CTRL_WRCSR  (unsigned short)( 1<<9 )
#define FLASH_CTRL_WREN   (unsigned short)( 1<<11)
#define FLASH_CTRL_FLUSH  (unsigned short)( 1<<12)
#define FLASH_CTRL_IE     (unsigned short)( 1<<13)
#define FLASH_CTRL_ST     (unsigned short)( 1<<14)
#define FLASH_CTRL_MODE   (unsigned short)( 1<<15)
    

//FlashState
#define FLASH_STATE_CAUSE       (unsigned char) (3 << 1)
#define FLASH_STATE_RD_FINISH   (unsigned char) (1 << 2)
#define FLASH_STATE_CTRL_MODE   (unsigned char) (1 << 3)
#define FALSH_STATE_CSR         (unsigned char) (3 << 4)
#define FLASH_STATE_FLASH_MODE  (unsigned char) (3 << 6)


#define FLASH_STATE_FLASH_MODE_QPI (unsigned char) (0 << 6)
#define FLASH_STATE_FLASH_MODE_SPI (unsigned char) (1 << 6)
#define FLASH_STATE_FLASH_MODE_DPI (unsigned char) (2 << 6)
#ifdef N25Q128 
#define FLASH_STATE_CSR_SR   (unsigned char) (0<<4)
#define FLASH_STATE_CSR_LR   (unsigned char) (1<<4)
#define FLASH_STATE_CSR_FSR  (unsigned char) (2<<4)
#define FLASH_STATE_CSR_VECR (unsigned char) (3<<4)
#endif
#ifdef IS25LP128
#define FLASH_STATE_CSR_SR (unsigned char) (0<<4)
#define FLASH_STATE_CSR_FR (unsigned char) (1<<4)
#endif

#define FLASH_STATE_CAUSE_NONE (unsigned char )0
#define FLASH_STATE_CAUSE_ILLEGAL (unsigned char )1
#define FLASH_STATE_CAUSE_WRDI (unsigned char )2
#define FLASH_STATE_CAUSE_NOTSUPPORT (unsigned char)3

#define OP_READ (unsigned char)0
#define OP_WRITE (unsigned char)1
#define OP_OTHER (unsigned char)2

///////////////////////////////////////////////////////////
//Interface 
//Flush flag 
#define FLUSH_CHIP 0
#define FLUSH_BLOCK_32K 1
#define FLUSH_BLOCK_64K 2
#define FLUSH_SECTOR 3
#define CSR_VECR 3
char flash_get_env_info(volatile QSPI_REG_P flash_reg);
void flash_init(volatile QSPI_REG_P flash_reg,int clk_div_param);
void flash_int_enable(volatile QSPI_REG_P flash_reg);
void flash_int_disable(volatile QSPI_REG_P flash_reg);
void flash_flush(volatile QSPI_REG_P flash_reg, unsigned int flush_flag,unsigned int addr);
void flash_wrcsr(volatile QSPI_REG_P flash_reg,unsigned int csr_data, unsigned int csr_flag);
unsigned int flash_rdcsr(volatile QSPI_REG_P flash_reg,unsigned int csr_flag);
void flash_enter_qpi(volatile QSPI_REG_P flash_reg);
void flash_exit_qpi(volatile QSPI_REG_P flash_reg);
void flash_enter_dpi(volatile QSPI_REG_P flash_reg);
void flash_exit_dpi(volatile QSPI_REG_P flash_reg);
void flash_enter_pmode(volatile QSPI_REG_P flash_reg);
void flash_exit_pmode(volatile QSPI_REG_P flash_reg);
int  flash_program_op(volatile QSPI_REG_P flash_reg,unsigned char op_flag,unsigned char inst,unsigned int addr,unsigned int data);


#endif



