#ifndef ETHMAC
#define ETHMAC
typedef struct {
    volatile uint32_t   moder;       /* Mode Register */
    volatile uint32_t   int_src;     /* Interrupt Source Register */
    volatile uint32_t   int_mask;    /* Interrupt Mask Register */
    volatile uint32_t   ipgt;        /* Back to Bak Inter Packet Gap Register */
    volatile uint32_t   ipgr1;       /* Non Back to Back Inter Packet Gap Register 1 */
    volatile uint32_t   ipgr2;       /* Non Back to Back Inter Packet Gap Register 2 */
    volatile uint32_t   packet_len;  /* Packet Length Register (min. and max.) */
    volatile uint32_t   collconf;    /* Collision and Retry Configuration Register */
    volatile uint32_t   tx_bd_num;   /* Transmit Buffer Descriptor Number Register */
    volatile uint32_t   ctrlmoder;   /* Control Module Mode Register */
    volatile uint32_t   miimoder;    /* MII Mode Register */
    volatile uint32_t   miicommand;  /* MII Command Register */
    volatile uint32_t   miiaddress;  /* MII Address Register */
    volatile uint32_t   miitx_data;  /* MII Transmit Data Register */
    volatile uint32_t   miirx_data;  /* MII Receive Data Register */
    volatile uint32_t   miistatus;   /* MII Status Register */
    volatile uint32_t   mac_addr0;   /* MAC Individual Address Register 0 */
    volatile uint32_t   mac_addr1;   /* MAC Individual Address Register 1 */
    volatile uint32_t   hash_addr0;  /* Hash Register 0 */
    volatile uint32_t   hash_addr1;  /* Hash Register 1 */
    volatile uint32_t   txctrl;      /* Transmitter control register */
} ETHMAC_TypeDef;
#define eth_ptr           ((ETHMAC_TypeDef *)ETHMAC_CTRL_ADDR)

#define ETH_TOTAL_BD           128
#define ETH_MAXBUF_LEN         0x600
/* Tx BD */
#define ETH_TX_BD_READY        0x8000 /* Tx BD Ready */
#define ETH_TX_BD_IRQ          0x4000 /* Tx BD IRQ Enable */
#define ETH_TX_BD_WRAP         0x2000 /* Tx BD Wrap (last BD) */
#define ETH_TX_BD_PAD          0x1000 /* Tx BD Pad Enable */
#define ETH_TX_BD_CRC          0x0800 /* Tx BD CRC Enable */
#define ETH_TX_BD_UNDERRUN     0x0100 /* Tx BD Underrun Status */
#define ETH_TX_BD_RETRY        0x00F0 /* Tx BD Retry Status */
#define ETH_TX_BD_RETLIM       0x0008 /* Tx BD Retransmission Limit Status */
#define ETH_TX_BD_LATECOL      0x0004 /* Tx BD Late Collision Status */
#define ETH_TX_BD_DEFER        0x0002 /* Tx BD Defer Status */
#define ETH_TX_BD_CARRIER      0x0001 /* Tx BD Carrier Sense Lost Status */
#define ETH_TX_BD_STATS        0x01FF
/* Rx BD */
#define ETH_RX_BD_EMPTY        0x8000 /* Rx BD Empty */
#define ETH_RX_BD_IRQ          0x4000 /* Rx BD IRQ Enable */
#define ETH_RX_BD_WRAP         0x2000 /* Rx BD Wrap (last BD) */
#define ETH_RX_BD_MISS         0x0080 /* Rx BD Miss Status */
#define ETH_RX_BD_OVERRUN      0x0040 /* Rx BD Overrun Status */
#define ETH_RX_BD_INVSIMB      0x0020 /* Rx BD Invalid Symbol Status */
#define ETH_RX_BD_DRIBBLE      0x0010 /* Rx BD Dribble Nibble Status */
#define ETH_RX_BD_TOOLONG      0x0008 /* Rx BD Too Long Status */
#define ETH_RX_BD_SHORT        0x0004 /* Rx BD Too Short Frame Status */
#define ETH_RX_BD_CRCERR       0x0002 /* Rx BD CRC Error Status */
#define ETH_RX_BD_LATECOL      0x0001 /* Rx BD Late Collision Status */
#define ETH_RX_BD_STATS        0x00FF
/* MODER Register */
#define ETH_MODER_RXEN         0x00000001 /* Receive Enable  */
#define ETH_MODER_TXEN         0x00000002 /* Transmit Enable */
#define ETH_MODER_NOPRE        0x00000004 /* No Preamble  */
#define ETH_MODER_BRO          0x00000008 /* Reject Broadcast */
#define ETH_MODER_IAM          0x00000010 /* Use Individual Hash */
#define ETH_MODER_PRO          0x00000020 /* Promiscuous (receive all) */
#define ETH_MODER_IFG          0x00000040 /* Min. IFG not required */
#define ETH_MODER_LOOPBCK      0x00000080 /* Loop Back */
#define ETH_MODER_NOBCKOF      0x00000100 /* No Backoff */
#define ETH_MODER_EXDFREN      0x00000200 /* Excess Defer */
#define ETH_MODER_FULLD        0x00000400 /* Full Duplex */
#define ETH_MODER_RST          0x00000800 /* Reset MAC */
#define ETH_MODER_DLYCRCEN     0x00001000 /* Delayed CRC Enable */
#define ETH_MODER_CRCEN        0x00002000 /* CRC Enable */
#define ETH_MODER_HUGEN        0x00004000 /* Huge Enable */
#define ETH_MODER_PAD          0x00008000 /* Pad Enable */
#define ETH_MODER_RECSMALL     0x00010000 /* Receive Small */
/* Interrupt Source Register */
#define ETH_INT_TXB            0x00000001 /* Transmit Buffer IRQ */
#define ETH_INT_TXE            0x00000002 /* Transmit Error IRQ */
#define ETH_INT_RXF            0x00000004 /* Receive Frame IRQ */
#define ETH_INT_RXE            0x00000008 /* Receive Error IRQ */
#define ETH_INT_BUSY           0x00000010 /* Busy IRQ */
#define ETH_INT_TXC            0x00000020 /* Transmit Control Frame IRQ */
#define ETH_INT_RXC            0x00000040 /* Received Control Frame IRQ */
/* Interrupt Mask Register */
#define ETH_INT_MASK_TXB       0x00000001 /* Transmit Buffer IRQ Mask */
#define ETH_INT_MASK_TXE       0x00000002 /* Transmit Error IRQ Mask */
#define ETH_INT_MASK_RXF       0x00000004 /* Receive Frame IRQ Mask */
#define ETH_INT_MASK_RXE       0x00000008 /* Receive Error IRQ Mask */
#define ETH_INT_MASK_BUSY      0x00000010 /* Busy IRQ Mask */
#define ETH_INT_MASK_TXC       0x00000020 /* Transmit Control Frame IRQ Mask */
#define ETH_INT_MASK_RXC       0x00000040 /* Received Control Frame IRQ Mask */
/* Control Module Mode Register */
#define ETH_CTRLMODER_PASSALL  0x00000001 /* Pass Control Frames */
#define ETH_CTRLMODER_RXFLOW   0x00000002 /* Receive Control Flow Enable */
#define ETH_CTRLMODER_TXFLOW   0x00000004 /* Transmit Control Flow Enable */
/* MII Mode Register */
#define ETH_MIIMODER_CLKDIV    0x000000FF /* Clock Divider */
#define ETH_MIIMODER_NOPRE     0x00000100 /* No Preamble */
#define ETH_MIIMODER_RST       0x00000200 /* MIIM Reset */
/* MII Command Register */
#define ETH_MIICOMMAND_SCANSTAT  0x00000001 /* Scan Status */
#define ETH_MIICOMMAND_RSTAT     0x00000002 /* Read Status */
#define ETH_MIICOMMAND_WCTRLDATA 0x00000004 /* Write Control Data */
/* MII Address Register */
#define ETH_MIIADDRESS_FIAD    0x0000001F /* PHY Address */
#define ETH_MIIADDRESS_RGAD    0x00001F00 /* RGAD Address */
/* MII Status Register */
#define ETH_MIISTATUS_LINKFAIL 0x00000001 /* Link Fail */
#define ETH_MIISTATUS_BUSY     0x00000002 /* MII Busy */
#define ETH_MIISTATUS_NVALID   0x00000004 /* Data in MII Status Register is invalid */

#endif
