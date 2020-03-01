/************************************************
*
*   FILE_NAME:  platform.h
*
*   FUNCTION :  define the address of some device 
*   AUTHOR  :   liaoll
*
*   DATE    :   2017/08/01
************************************************/

#ifndef SDJ2102_PLATFORM_H
#define SDJ2102 PLATFORM_H
#include "stdio.h"
#include "stdint.h"

#include "bits.h"
#include "csr.h"
#include "mmu.h"
#include "core/core.h"
#include "device/device.h"

#ifdef __ASSEMBLER__
#define _CONNECT(X,Y)   X
#define _ATTACH(T,X)    X
#else
#define _CONNECT(X,Y)   X##Y
#define _ATTACH(T,X)    ((T)(X))
#endif /*!__ASSEMBLER__*/

/************************************************
*   memory map
**************************************************/
#define CLINT_CTRL_ADDR         CLINT_CTRL_BASE
#define PLIC_CTRL_ADDR          PLIC_CTRL_BASE
#define GPIO_CTRL_ADDR          GPIO_CTRL_BASE
#define I2C_CTRL_ADDR           I2C_CTRL_BASE
#define UART_CTRL_ADDR          UART_CTRL_BASE
#define UART2_CTRL_ADDR         UART2_CTRL_BASE
#define USB11_CTRL_ADDR         USB11_CTRL_BASE
#define SPI_CTRL_ADDR           SPI_CTRL_BASE
#define ETIMER1_CTRL_ADDR       ETIMER1_CTRL_BASE
#define ETIMER2_CTRL_ADDR       ETIMER2_CTRL_BASE
#define CAN_CTRL_ADDR           CAN_CTRL_BASE
#define QSPI_CTRL_ADDR          QSPI_CTRL_BASE
#define CGU_CTRL_ADDR           CGU_CTRL_BASE
#define VGA_CTRL_ADDR           VGA_CTRL_BASE

#define ETHMAC_CTRL_ADDR        ETHMAC_CTRL_BASE
#define ETHMAC_TX_BD            ETHMAC_TX_BD_BASE
#define ETHMAC_RX_BD            ETHMAC_RX_BD_BASE

/*************************************************
* address access function macro
**************************************************/

#define _REG32(base,offset)     (*((volatile int *)(base+offset))) 
#define _REG8(base,offset)      (*((volatile char*)(base+offset)))
#define _REG16(base,offset)     (*((volatile short*)(base+offset)))
// address access function
#define CLINT_REG(offset)       _REG32(CLINT_CTRL_ADDR,offset)
#define PLIC_REG(offset)        _REG32(PLIC_CTRL_ADDR,offset)
#define GPIO_REG(offset)        _REG8(GPIO_CTRL_ADDR,offset)
#define I2C_REG(offset)         _REG8(I2C_CTRL_ADDR,offset)
#define UART_REG(offset)        _REG8(UART_CTRL_ADDR,offset)
#define UART2_REG(offset)       _REG8(UART2_CTRL_ADDR,offset)
#define CGU_REG(offset)         _REG32(CGU_CTRL_ADDR,offset)
#define SPI_REG(offset)         _REG8(SPI_CTRL_ADDR,offset)
#define ETIMER1_REG(offset)     _REG8(ETIMER1_CTRL_ADDR,offset)
#define ETIMER2_REG(offset)     _REG8(ETIMER2_CTRL_ADDR,offset)
#define CAN_REG(offset)         _REG8(CAN_CTRL_ADDR,offset)
#define VGA_REG(offset)         _REG32(VGA_CTRL_ADDR,offset)

// bit operation function
#define SET_BITS(reg,mask,value){\
    if((value) == 0){\
        (reg) &= ~(mask);}\
    else{\
        (reg) |= (mask); }}

#define READ_BITS(reg,mask)  ( (unsigned char)(reg & mask) ? 1 :0 )


/*************************************************
* integer type define
**************************************************/
typedef   signed            char int8_t;
typedef   signed short      int int16_t;
//typedef   signed           int int32_t;

typedef unsigned            char uint8_t;
typedef unsigned short      int uint16_t;
//typedef unsigned           int uint32_t;


#endif /* SDJ2102_PLATFORM_H */
