/***************************************************************************************************
*
*   PROJECT:    SDJ2102
*
*   FILENAME:   i2c.h
*
*   FUNCTION:   define the interface to operate the I2C bus 
*
*   AUTHOR:     liaoll
*
*   DATE:       2017/09/06
*
*   ISFINISH:   NO
****************************************************************************************************/
#ifndef SDJ2102_I2C_H
#define SDJ2102_I2C_H

// I2C interrupt ID
#define LOCAL_I2C_ID    1

// I2C register
#define I2C_ADDR        0x3     //i2c address register
#define I2C_FD          0x4     //i2c frequency divide register
#define I2C_CON         0x5     //i2c control register
#define I2C_STA         0x6     //i2c status register
#define I2C_DATA        0x7     //i2c data register

// I2C control resgiter bit mask
#define I2C_CON_MIEN    0x1<<6  //master: module interrupt enable
#define I2C_CON_RSTA    0x1<<5  //repeat start
#define I2C_CON_TACK    0x1<<4  //transmit acknowledge
#define I2C_CON_MTX     0x1<<3  //master: transmission receive mode
#define I2C_CON_MSTA    0x1<<2  //master/slave device select
#define I2C_CON_MEN     0x1<<0  //mudole enable

// I2C status register bit mask
#define I2C_STA_MTF     0x1<<7  //master:data tramsmit finish check
#define I2C_STA_MAAS    0x1<<6  //master:address match
#define I2C_STA_MBB     0x1<<5  //master:bus busy
#define I2C_STA_MAL     0x1<<4  //master:arbitration lost status
#define I2C_STA_SRW     0x1<<3  //slave: read write status
#define I2C_STA_MINT    0x1<<2  //master: interrupt status
#define I2C_STA_RACK    0x1<<1  //receive acknowledge

// I2C operate function interface 
//if want to use the default fdr, make the parameter fdr zero when call this function 
void i2c_delay(int n);
void i2c_init(unsigned char addr, unsigned char fdr); 
void select_ms(unsigned char mode);//select device master or slave 
void i2c_write(unsigned char addr, const char *str, unsigned int len);
void i2c_read(unsigned char addr, char *str, unsigned int len);
void i2c_stop(void);
void i2c_write_byte_start(unsigned char addra);
void i2c_write_byte_data(unsigned char data);
char i2c_read_byte_start(unsigned char addr);
char i2c_read_byte_data();


#endif
