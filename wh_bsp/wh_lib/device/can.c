#include "platform.h"
#include "csr.h"




//////////extend_mode////////////////////
void can_extend_reset()
{
    CAN_REG(CAN_SET_EXTEND)&=0x7f;                  //change to basic_mode
    CAN_REG(CAN_SET_RESET)|=0x01;               //basic_mode > basic_reset_mode
    CAN_REG(CAN_SET_EXTEND)|=0x80;                      //basic_reseet_mode > extend_reset_mode
    CAN_REG(CAN_EXTEND_ACCEPTANCE_FILTER_MODE)|=0x08;       //single_filter_mode
    //CAN_REG(CAN_EXTEND_ACCEPTANCE_FILTER_MODE)|=0x0c;   

    // 96MHz, 100kbps
    //CAN_REG(CAN_FRE_JUMPWIDTH)=0x3f;                  //[7:6]jumpwidth,[5:0]devide_frequence
    //CAN_REG(CAN_SAMP_SENDDUAN)=0x1b;                  //[7]samp,[6:4]seg2,[3:0]seg1,250kbps

    // 97.5MHz, 100kbps
    CAN_REG(CAN_FRE_JUMPWIDTH)=0x26;                //[7:6]jumpwidth,[5:0]devide_frequence
    CAN_REG(CAN_SAMP_SENDDUAN)=0x7f;                //[7]samp,[6:4]seg2,[3:0]seg1,250kbps

    // 48MHz, 250kbps
    //CAN_REG(CAN_FRE_JUMPWIDTH)=0x0f;                  //[7:6]jumpwidth,[5:0]devide_frequence
    //CAN_REG(CAN_SAMP_SENDDUAN)=0x18;                  //[7]samp,[6:4]seg2,[3:0]seg1,250kbps

    CAN_REG(CAN_IRQENEST)=0x03;                     // extend_mode interrupt_en

    CAN_REG(CAN_ACEPTANCE_CODE_0)=0xa6;
    CAN_REG(CAN_ACEPTANCE_CODE_1)=0xa0;
    CAN_REG(CAN_ACEPTANCE_CODE_2)=0xa6;
    CAN_REG(CAN_ACEPTANCE_CODE_3)=0xa0;
    CAN_REG(CAN_ACEPTANCE_MASK_0)=0xff;
    CAN_REG(CAN_ACEPTANCE_MASK_1)=0xff;
    CAN_REG(CAN_ACEPTANCE_MASK_2)=0xff;
    CAN_REG(CAN_ACEPTANCE_MASK_3)=0xff;

    CAN_REG(CAN_SET_RESET)&=0xfe;                   //when in extend_reset_mode change to extend mode
}


void can_data_send(char IDE,char RTR,char DLC,int ID,char data0,char data1,char data2,
                   char data3,char data4,char data5,char data6,char data7)
{
    int i;
    can_extend_reset();
    can_data_need_to_send(IDE,RTR,DLC,ID,data0,data1,data2,data3,data4,data5,data6,data7);
    CAN_REG(CAN_EXTEND_COMMAND)=0x11;               //send_command
    //for(i=0;i<48000;i++);                 //send_delay
}

void can_basic_reset()
{
    CAN_REG(CAN_SET_EXTEND)&=0x7f;           //change to basic_mode
    CAN_REG(CAN_SET_RESET)|=0x01;

    CAN_REG(CAN_BASIC_RESET_IRQ)|=0x1e;

    CAN_REG(CAN_SJW_AND_FRE)=0x0f;
    CAN_REG(CAN_BS_AND_SAMP)=0x18;           //250kbps

    CAN_REG(BASICRST_ACEPTANCE_CODE_0)=0xe8;
    CAN_REG(BASICRST_ACEPTANCE_MASK_0)=0xff;

    CAN_REG(CAN_SET_RESET)&=0xfe;           //return to basic_mode
}


void can_basic_mode_send_demo()
{
    //char rdata;
    short int one_times_flag=0;
    int i;
    //uart_init(115200);

    can_basic_reset();

    CAN_REG(CAN_BASIC_COMMAND)=0x00;

    while(1)
    {
        //rdata=uart_getchar2();
        //if(one_times_flag==0)
        {
            can_data_need_to_send(0x00,0x00,0x07,0x673,0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37);
            CAN_REG(CAN_BASIC_COMMAND)=0x11;                        //send_command
            for(i=0;i<48000;i++);
            CAN_REG(CAN_BASIC_COMMAND)=0x04;
        //  one_times_flag=1;
        }
    }
}



void can_receive_data()
{
    char tmp_data[11];

    if( (CAN_REG(CAN_SET_EXTEND)&0x80)==0x80 )          //extend_mode,stand_frame
    {
        tmp_data[8]=CAN_REG(CAN_EXTEND_RX_DATA_0);  //IDE+RTR+DLC[3:0]
        tmp_data[9]=CAN_REG(CAN_EXTEND_RX_DATA_1);  //ID[10:3]
        tmp_data[10]=CAN_REG(CAN_EXTEND_RX_DATA_2); //ID[2:0]
        tmp_data[0]=CAN_REG(CAN_EXTEND_RX_DATA_3);  //data0
        tmp_data[1]=CAN_REG(CAN_EXTEND_RX_DATA_4);  //data1
        tmp_data[2]=CAN_REG(CAN_EXTEND_RX_DATA_5);  //data2
        tmp_data[3]=CAN_REG(CAN_EXTEND_RX_DATA_6);  //data3
        tmp_data[4]=CAN_REG(CAN_EXTEND_RX_DATA_7);  //data4
        tmp_data[5]=CAN_REG(CAN_EXTEND_RX_DATA_8);  //data5
        tmp_data[6]=CAN_REG(CAN_EXTEND_RX_DATA_9);  //data6
        tmp_data[7]=CAN_REG(CAN_EXTEND_RX_DATA_10); //data7

        CAN_REG(CAN_EXTEND_COMMAND)|=0x04;              //release_buffer

/*
        uart_putchar(tmp_data[8]);
        uart_putchar(tmp_data[9]);
        uart_putchar(tmp_data[10]);
        uart_putchar(tmp_data[0]);
        uart_putchar(tmp_data[1]);
        uart_putchar(tmp_data[2]);
        uart_putchar(tmp_data[3]);
        uart_putchar(tmp_data[4]);
        uart_putchar(tmp_data[5]);
        uart_putchar(tmp_data[6]);
        uart_putchar(tmp_data[7]);
*/
    }
    else
    {
        tmp_data[0]=CAN_REG(CAN_BASIC_RX_DATA_0);           //receive ID[10:3]
        tmp_data[1]=CAN_REG(CAN_BASIC_RX_DATA_1);           //receive ID[2:0]+RTR+DLC[3:0]
        tmp_data[2]=CAN_REG(CAN_BASIC_RX_DATA_2);           //data0
        tmp_data[3]=CAN_REG(CAN_BASIC_RX_DATA_3);           //data1
        tmp_data[4]=CAN_REG(CAN_BASIC_RX_DATA_4);           //data2
        tmp_data[5]=CAN_REG(CAN_BASIC_RX_DATA_5);           //data3
        tmp_data[6]=CAN_REG(CAN_BASIC_RX_DATA_6);           //data4
        tmp_data[7]=CAN_REG(CAN_BASIC_RX_DATA_7);           //data5
        tmp_data[8]=CAN_REG(CAN_BASIC_RX_DATA_8);           //data6
        tmp_data[9]=CAN_REG(CAN_BASIC_RX_DATA_9);           //data7

        CAN_REG(CAN_BASIC_COMMAND)|=0x04;                   //release_buffer

/*
        uart_putchar(tmp_data[0]);
        uart_putchar(tmp_data[1]);
        uart_putchar(tmp_data[2]);
        uart_putchar(tmp_data[3]);
        uart_putchar(tmp_data[4]);
        uart_putchar(tmp_data[5]);
        uart_putchar(tmp_data[6]);
        uart_putchar(tmp_data[7]);
        uart_putchar(tmp_data[8]);
        uart_putchar(tmp_data[9]);
*/
    }
    tmp_data[11]=0;
}

void can_data_need_to_send(char IDE,char RTR,char DLC,int ID,char data0,char data1,char data2,
                   char data3,char data4,char data5,char data6,char data7)
{
    if( (CAN_REG(CAN_SET_EXTEND)&0x80)==0x80 )
    {
        CAN_REG(CAN_EXTEND_RX_DATA_0)=( ((0x01 & IDE)<<7)|((0x01 & RTR)<<6)|(0x0f & DLC) );

        if(IDE==0x00)       //extend_mode/standard_frame
        {
            //ID
            CAN_REG(CAN_EXTEND_RX_DATA_1)=(ID>>3);
            CAN_REG(CAN_EXTEND_RX_DATA_2)=( (0x07 & ID)<<5 );
            //data
            CAN_REG(CAN_EXTEND_RX_DATA_3)=data0;
            CAN_REG(CAN_EXTEND_RX_DATA_4)=data1;
            CAN_REG(CAN_EXTEND_RX_DATA_5)=data2;
            CAN_REG(CAN_EXTEND_RX_DATA_6)=data3;
            CAN_REG(CAN_EXTEND_RX_DATA_7)=data4;
            CAN_REG(CAN_EXTEND_RX_DATA_8)=data5;
            CAN_REG(CAN_EXTEND_RX_DATA_9)=data6;
            CAN_REG(CAN_EXTEND_RX_DATA_10)=data7;
        }
        else                //extend_mode/extend_frame
        {
          //ID
            CAN_REG(CAN_EXTEND_RX_DATA_1)=(ID>>21);
            CAN_REG(CAN_EXTEND_RX_DATA_2)=(ID>>13);
            CAN_REG(CAN_EXTEND_RX_DATA_3)=(ID>>5);
            CAN_REG(CAN_EXTEND_RX_DATA_4)=((0x1f & ID)<<3);
            //data
            CAN_REG(CAN_EXTEND_RX_DATA_5)=data0;
            CAN_REG(CAN_EXTEND_RX_DATA_6)=data1;
            CAN_REG(CAN_EXTEND_RX_DATA_7)=data2;
            CAN_REG(CAN_EXTEND_RX_DATA_8)=data3;
            CAN_REG(CAN_EXTEND_RX_DATA_9)=data4;
            CAN_REG(CAN_EXTEND_RX_DATA_10)=data5;
            CAN_REG(CAN_EXTEND_RX_DATA_11)=data6;
            CAN_REG(CAN_EXTEND_RX_DATA_12)=data7;
        }
    }
    else                    //basic_mode
    {
        CAN_REG(CAN_BASIC_TX_DATA_0)=(ID>>3);     //11bit_ID
        CAN_REG(CAN_BASIC_TX_DATA_1)=( ((0x07 & ID)<<5)|((0x01 & RTR)<<4)|(0x0f & DLC) );
        CAN_REG(CAN_BASIC_TX_DATA_2)=data0;
        CAN_REG(CAN_BASIC_TX_DATA_3)=data1;
        CAN_REG(CAN_BASIC_TX_DATA_4)=data2;
        CAN_REG(CAN_BASIC_TX_DATA_5)=data3;
        CAN_REG(CAN_BASIC_TX_DATA_6)=data4;
        CAN_REG(CAN_BASIC_TX_DATA_7)=data5;
        CAN_REG(CAN_BASIC_TX_DATA_8)=data6;
        CAN_REG(CAN_BASIC_TX_DATA_9)=data7;
    }
}



