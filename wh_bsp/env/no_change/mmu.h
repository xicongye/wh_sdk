/***************************************************************************************************
*
*   PROJECT:    SDJ2102
*
*   FILENAME:   mmu.h
*
*   FUNCTION:   define some important macro
*
*   AUTHOR:     yexc
*
*   DATE:       2019/04/04
*
*   ISFINISH:   YES
****************************************************************************************************/
#ifndef SDJ2102_MMU_H
#define SDJ2102_MMU_H

#define CORE_FREQ               CLK_FRQ  
#define MMIO_ADDR               MMIO_BASE
#define PLIC_NUM                INT_NUM

#define CLINT_CTRL_BASE         (CLINT_BASE)
#define PLIC_CTRL_BASE          (PLIC_BASE) 

#define GPIO_CTRL_BASE          (MMIO_ADDR+0x00)
#define I2C_CTRL_BASE           (MMIO_ADDR+0x60)
#define UART_CTRL_BASE          (MMIO_ADDR+0x10)
#define UART2_CTRL_BASE         (MMIO_ADDR+0xC0)
#define USB11_CTRL_BASE         (MMIO_ADDR+0x20)
#define SPI_CTRL_BASE           (MMIO_ADDR+0x18)
#define ETIMER1_CTRL_BASE       (MMIO_ADDR+0x80)
#define ETIMER2_CTRL_BASE       (MMIO_ADDR+0xA0)
#define CAN_CTRL_BASE           (MMIO_ADDR+0x40)
#define QSPI_CTRL_BASE          (MMIO_ADDR+0x70)
#define CGU_CTRL_BASE           (MMIO_ADDR+0x1fff8)
#define VGA_CTRL_BASE           (MMIO_ADDR+0x3000)

#define ETHMAC_CTRL_BASE        (MMIO_ADDR+0x1000)
#define ETHMAC_TX_BD_BASE       (MMIO_ADDR+0x1400)
#define ETHMAC_RX_BD_BASE       (MMIO_ADDR+0x1600)

#define TOTAL_CORE              CORE_NUM
#if TOTAL_CORE>1
    #define ENABLE_SMP
#endif

#define ROCC_STATUS             ECII_EN
#if ROCC_STATUS==1
    #define ENABLE_ROCC
#endif

#endif
