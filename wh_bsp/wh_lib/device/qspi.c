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
#include "platform.h"

void flash_init(volatile QSPI_REG_P flash_reg,int clk_div_param)
{
    flash_reg -> FlashDivide = clk_div_param ;
    return ;
}

void flash_int_enable(volatile QSPI_REG_P flash_reg)
{
    flash_reg -> FlashCtrl  |= FLASH_CTRL_IE;
    return; 
}
void flash_int_disable(volatile QSPI_REG_P flash_reg)
{
    flash_reg -> FlashCtrl &= ~FLASH_CTRL_IE;
    return ;
}

void flash_flush(volatile QSPI_REG_P flash_reg,unsigned int flush_flag,unsigned int addr)
{
    switch(flush_flag)
    {
        case FLUSH_CHIP:
            flash_reg -> FlashCtrl |= FLASH_CTRL_CER;
            break;
        case FLUSH_BLOCK_32K: 
            flash_reg -> FlashAddr = addr;
            flash_reg -> FlashCtrl |= FLASH_CTRL_BER32;
            break;
        case FLUSH_BLOCK_64K:
                        flash_reg -> FlashAddr = addr;
            flash_reg -> FlashCtrl |= FLASH_CTRL_BER64;
            break;
        case FLUSH_SECTOR:
                        flash_reg -> FlashAddr = addr;
            flash_reg -> FlashCtrl |= FLASH_CTRL_SER;
            break;
        default:
            ;
    }
    
    return ;
}
void flash_wrcsr(volatile QSPI_REG_P flash_reg,unsigned int csr_data,unsigned int csr_flag)
{
        flash_reg->FlashState = (unsigned char)(flash_reg->FlashState & ~FALSH_STATE_CSR | \
                                (csr_flag << 4) & FALSH_STATE_CSR \
                                );
    if(flash_reg -> FlashState & FLASH_STATE_CTRL_MODE)
        flash_reg->FlashData = csr_data;
    else
        flash_reg->FlashCSR = (char) csr_data ;
    flash_reg->FlashCtrl |= FLASH_CTRL_WRCSR; 

}
unsigned int flash_rdcsr(volatile QSPI_REG_P flash_reg,unsigned int csr_flag)
{
    volatile char ch;
    flash_reg -> FlashCtrl |= FLASH_CTRL_RDCSR;
    do
    {
        ch = flash_reg->FlashState;
    }while(!(ch & FLASH_STATE_RD_FINISH));
    if(flash_reg -> FlashState & FLASH_STATE_CTRL_MODE)
        return flash_reg -> FlashData;
    else
        return (int)flash_reg -> FlashCSR;
}

void flash_enter_qpi(volatile QSPI_REG_P flash_reg)
{
    flash_reg -> FlashCtrl |= FLASH_CTRL_EQPI;
    return ;
}
void flash_exit_qpi(volatile QSPI_REG_P flash_reg)
{
    flash_reg -> FlashCtrl |= FLASH_CTRL_QPIDI;
    return ;
}
void flash_enter_dpi(volatile QSPI_REG_P flash_reg)
{
    flash_reg -> FlashCtrl |= FLASH_CTRL_EDPI;
    return;

}
void flash_exit_dpi(volatile QSPI_REG_P flash_reg)
{
    flash_reg->FlashCtrl |= FLASH_CTRL_DPIDI;
    return;
}
void flash_enter_pmode(volatile QSPI_REG_P flash_reg)
{
    flash_reg->FlashCtrl |= FLASH_CTRL_MODE;
    return ;
}
void flash_exit_pmode(volatile QSPI_REG_P flash_reg)
{
    flash_reg -> FlashCtrl &= (~FLASH_CTRL_MODE) ;
    return ;

}
int flash_program_op(volatile QSPI_REG_P flash_reg,unsigned char op_flag,unsigned char inst,unsigned int addr,unsigned int data)
{
    volatile char ch;
    ch = flash_reg->FlashState; 
    if(!(ch & FLASH_STATE_CTRL_MODE))
        flash_enter_pmode(flash_reg);
    if(op_flag == OP_READ)
        flash_reg->FlashCtrl |= FLASH_CTRL_FLUSH ;
    flash_reg->FlashAddr = inst << 24 | addr ;
    flash_reg->FlashData = data ;
    flash_reg->FlashCtrl = FLASH_CTRL_ST;
    if(op_flag == OP_READ)
    {
        do{
            ch = flash_reg->FlashState;
        }
        while (!(ch & FLASH_STATE_RD_FINISH));
        return flash_reg -> FlashData ;
    }
    else
        return 0;   
}


