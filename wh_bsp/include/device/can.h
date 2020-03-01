#ifndef SDJ2102_CAN_H
#define SDJ2102_CAN_H

///opencan use in(ID and data),ID high 4bit_function-code,low 7bit_device-code 

/////////////////NEW_Extended_RESET_Mode////////////
#define CAN_SET_RESET             0x00      //change to reset_mode or normal_mode
#define CAN_EXTEND_ACCEPTANCE_FILTER_MODE    0x00         //1_single_filter,0_double_filter
#define CAN_IRQENEST              0x04      //extend_mode_interrupt_en
#define CAN_FRE_JUMPWIDTH         0x06      //[7:6]jumpwidth,[5:0]devide_frequence
#define CAN_SAMP_SENDDUAN         0x07      //[7]samp,[6:4]seg1,[3:0]seg2 | [7]samp,[6:4]seg2,[3:0]seg1
#define CAN_ACEPTANCE_CODE_0      0x10
#define CAN_ACEPTANCE_CODE_1      0x11
#define CAN_ACEPTANCE_CODE_2      0x12
#define CAN_ACEPTANCE_CODE_3      0x13
#define CAN_ACEPTANCE_MASK_0      0x14
#define CAN_ACEPTANCE_MASK_1      0x15
#define CAN_ACEPTANCE_MASK_2      0x16
#define CAN_ACEPTANCE_MASK_3      0x17
#define CAN_SET_EXTEND            0x1f      //change to basic or extend,bit[7]

////////////////NEW_BASIC_RESET_MODE///////////////
#define CAN_BASIC_RESET_IRQ         0x00      //bit[1]~bit[4]_receive_transmit_error_overrun_irq_en
#define BASICRST_ACEPTANCE_CODE_0   0x04
#define BASICRST_ACEPTANCE_MASK_0   0x05
#define CAN_SJW_AND_FRE             0x06      //[7:6]jumpwidth,[5:0]devide_frequence
#define CAN_BS_AND_SAMP             0x07      //[7]samp,[6:4]seg1,[3:0]seg2 | [7]samp,[6:4]seg2,[3:0]seg1

////////////////NEW_BASIC_MODE////////////////////
#define CAN_BASIC_IRQEN             0x00      //bit[1]~bit[4]_receive_transmit_error_overrun_irq_en(only read)
#define CAN_BASIC_COMMAND           0x01      //basic_command[4:0]
#define CAN_BASIC_STATUS_REG        0x02      //bit[0]~bit[7]:(receive,overrun,transmit_buffer,transmit_complete,receive,transmit,error,node_buffer)_only read
#define CAN_BASIC_IRQ               0x03      //irq_reg (only read)
#define CAN_BASIC_SJW_FRE           0x06      //[7:6]jumpwidth,[5:0]devide_frequence

//write_addra//
#define CAN_BASIC_TX_DATA_0             0x0c
#define CAN_BASIC_TX_DATA_1             0x0d
#define CAN_BASIC_TX_DATA_2             0x0e
#define CAN_BASIC_TX_DATA_3             0x0f
#define CAN_BASIC_TX_DATA_4             0x10
#define CAN_BASIC_TX_DATA_5             0x11
#define CAN_BASIC_TX_DATA_6             0x12
#define CAN_BASIC_TX_DATA_7             0x13
#define CAN_BASIC_TX_DATA_8             0x14
#define CAN_BASIC_TX_DATA_9             0x15

//read_addra//
#define CAN_BASIC_RX_DATA_0             0x14
#define CAN_BASIC_RX_DATA_1             0x15
#define CAN_BASIC_RX_DATA_2             0x16
#define CAN_BASIC_RX_DATA_3             0x17
#define CAN_BASIC_RX_DATA_4             0x18
#define CAN_BASIC_RX_DATA_5             0x19
#define CAN_BASIC_RX_DATA_6             0x1a
#define CAN_BASIC_RX_DATA_7             0x1b
#define CAN_BASIC_RX_DATA_8             0x1c
#define CAN_BASIC_RX_DATA_9             0x1d

#define CAN_READ_BASIC_TX_DATA_0        0x0a
#define CAN_READ_BASIC_TX_DATA_1        0x0b

                             
////////////////NEW_EXTEND_MODE///////////////////
////rx_data_reg_addra=tx_data_reg_addra/////
#define CAN_EXTEND_IRQEN                   0x00 //bit[1]~bit[4]_receive_transmit_error_overrun_irq_en(only read)
#define CAN_EXTEND_COMMAND                 0x01     //extend_command[4:0]
#define CAN_EXTEND_STATUS_REG              0x02      //bit[0]~bit[7]:(receive,overrun,transmit_buffer,transmit_complete,receive,transmit,error,node_buffer_status)_only read_
#define CAN_EXTEND_IRQ                         0x04 //irq,bit[0]~bit[7](receive,transmit,error..... _irq)
#define CAN_EXTEND_SJW_FRE                     0x06 //[7:6]jumpwidth,[5:0]devide_frequence(only_read)
#define CAN_EXTEND_RX_DATA_0                   0x10          
#define CAN_EXTEND_RX_DATA_1                   0x11
#define CAN_EXTEND_RX_DATA_2                   0x12
#define CAN_EXTEND_RX_DATA_3                   0x13
#define CAN_EXTEND_RX_DATA_4                   0x14
#define CAN_EXTEND_RX_DATA_5                   0x15
#define CAN_EXTEND_RX_DATA_6                   0x16
#define CAN_EXTEND_RX_DATA_7                   0x17
#define CAN_EXTEND_RX_DATA_8                   0x18
#define CAN_EXTEND_RX_DATA_9                   0x19
#define CAN_EXTEND_RX_DATA_10                  0x1a
#define CAN_EXTEND_RX_DATA_11                  0x1b
#define CAN_EXTEND_RX_DATA_12                  0x1c



void can_extend_reset();
void can_basic_reset();
void can_data_need_to_send(char IDE,char RTR,char DLC,int ID,char data0,char data1,char data2,char data3,char data4,char data5,char data6,char data7);
void can_receive_data();
void can_data_send(char IDE,char RTR,char DLC,int ID,char data0,char data1,char data2,
                   char data3,char data4,char data5,char data6,char data7);
void can_basic_mode_send_demo();

#endif
