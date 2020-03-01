/*******************************************************************                                                          
*
*       PROJECT:        W01
*
*       FILENAME:       i2c.c
*
*       FUNCTION:       IIC driver
*
*       AUTHOR:         yexc
*
*       DATE:           2018/11/02
*
*       IS_FINISH:      NO
*
********************************************************************/

/* Includes --------------------------------------------------------*/
#include "platform.h"
#include "csr.h"

/* Private define --------------------------------------------------*/
/* Private macro ---------------------------------------------------*/
/* Private variables -----------------------------------------------*/
/* Extern variables ------------------------------------------------*/
/* Private function prototypes -------------------------------------*/
/* Private functions -----------------------------------------------*/
/********************************************************************
* Function Name         :       i2c_delay
* Description           :       I2C delay
* Input                 :       - n -
* Output                :       none
* Return                :       none
********************************************************************/
void i2c_delay(int n)
{
    volatile int i;

    while(n--)
        for(i=0;i<4;i++);
}


/********************************************************************
* Function Name         :       i2c_init
* Description           :       I2C initial function
* Input                 :       - adr -
*                       :       - fre -
* Output                :       none
* Return                :       none
********************************************************************/
void i2c_init(unsigned char adr, unsigned char fre)
{
    /*addra[7:1]_slave,[0]_0_write,1_read
     *i2c_module as slave ,its_addra
     *
     * fre_i2c_fre
     */
    I2C_REG(I2C_CON) = 0x01;        //I2C_module_en
    I2C_REG(I2C_ADDR) = adr;        //I2C_slave_address
    I2C_REG(I2C_FD) = fre;          //I2C_fre_divide
}


/********************************************************************
* Function Name         :       i2c_start
* Description           :       I2C start function
* Input                 :       -  -
* Output                :       none
* Return                :       none
********************************************************************/
void i2c_start(void)
{
    I2C_REG(I2C_CON) = 0x4d;                                   //MIEN,MSTA,MEN=1(MTX=1)
}


/********************************************************************
* Function Name         :       i2c_stop
* Description           :       I2C stop function
* Input                 :       -  -
* Output                :       none
* Return                :       none
********************************************************************/
void i2c_stop(void)
{
    I2C_REG(I2C_CON) |= 0x10;                                  //TACK=1
    i2c_delay(2);
    I2C_REG(I2C_STA) &= 0xfb;                                  //MINT=0
}

/********************************************************************
* Function Name         :       i2c_read_byte_start
* Description           :       ----------
* Input                 :       - addr -
* Output                :       none
* Return                :       none
********************************************************************/
char i2c_read_byte_start(unsigned char addr)
{
    volatile char back_data;

    I2C_REG(I2C_DATA) = addr;           //send addr,and read_inst
    I2C_REG(I2C_CON) = 0x4d;            //top_MIEN=1,TACK=0,MTX=1,MSTA=1,MEN=1

    //while( (I2C_REG(I2C_STA)|0x7f)==0x7f);
    while((I2C_REG(I2C_STA) | 0xfb) == 0xfb);

    I2C_REG(I2C_DATA) = 0x00;                       //clear mtf
    I2C_REG(I2C_CON) = 0x45;                        //MTX=0,MEN=1,MSTA=1,TACK=0.MIEN=1,RSTA=0
    I2C_REG(I2C_STA) &= 0xfb;                       //MINT=0
    //i2c_delay(5);
    while(( I2C_REG(I2C_STA)|0xfb) == 0xfb);
    //while((I2C_REG(I2C_STA)|0x7f) == 0x7f);

    return back_data = I2C_REG(I2C_DATA);       //read_clear mtf
}


/********************************************************************
* Function Name         :       i2c_read_byte_data
* Description           :       ----------
* Input                 :       - -
* Output                :       none
* Return                :       none
********************************************************************/
char i2c_read_byte_data(void)
{
    volatile char back_data;

    I2C_REG(I2C_CON) = 0x45;                        //MTX=0,MEN=1,MSTA=1,TACK=0.MIEN=1,RSTA=0
    I2C_REG(I2C_STA) &= 0xfb;                       //MINT=0
    while((I2C_REG(I2C_STA) | 0xfb) == 0xfb );
    //while((I2C_REG(I2C_STA)|0x7f) == 0x7f );

    return back_data = I2C_REG(I2C_DATA);
}


/********************************************************************
* Function Name         :       i2c_write_byte_start
* Description           :       ----------
* Input                 :       - addra -
* Output                :       none
* Return                :       none
********************************************************************/
void i2c_write_byte_start(unsigned char addra)
{
    /*
     *con:[6]MIEN,[5]RSTA,[4]TACK,[3]MTX,[2]MSTA,[0]MEN
     */
    I2C_REG(I2C_CON) &= I2C_CON_MEN;
    I2C_REG(I2C_DATA) = addra;          //send_addra,bit0_1/receive,0_send
    I2C_REG(I2C_CON) |= I2C_CON_MIEN;   //set_itr_en
    I2C_REG(I2C_CON) |= I2C_CON_MTX;    //set_send_mode
    I2C_REG(I2C_CON) |= I2C_CON_MSTA;   //start_send    |start

//  I2C_REG(I2C_CON)=0x4d;          //top_MIEN=1,TACK=0,MTX=1,MSTA=1,MEN=1

    while((I2C_REG(I2C_STA) | 0x7f) == 0x7f)    //check_MTF
    {
        i2c_delay(1);
    }

//  while((I2C_REG(I2C_STA) | 0xfb) == 0xfb );  //check_MINT
//  I2C_REG(I2C_DATA) = 0xff;           //clear MTF

    I2C_REG(I2C_CON) |= I2C_CON_TACK;       //STOP
    I2C_REG(I2C_STA) &= ~I2C_STA_MINT;      //clear MINT
}

/********************************************************************
* Function Name         :       i2c_write_byte_data
* Description           :       ----------
* Input                 :       - data -
* Output                :       none
* Return                :       none
********************************************************************/
void i2c_write_byte_data(unsigned char data)
{
    I2C_REG(I2C_DATA) = data;           //send_data,clear_MTF
    //I2C_REG(I2C_CON) = 0x4d;              //top_MIEN=1,TACK=0,MTX=1,MSTA=1,MEN=1
    I2C_REG(I2C_STA)&=0xfb;                         //MINT=0

    while( ( I2C_REG(I2C_STA)|0xfb )==0xfb );

    //while( (I2C_REG(I2C_STA)|0x7f )==0x7f )
    //{
    //  i2c_delay(1);
    //}
}
