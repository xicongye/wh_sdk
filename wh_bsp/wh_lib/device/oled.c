#include "platform.h"
#include "csr.h"
#include "device/oledfont.h"

void oled_delay(int n)
{
        volatile int i;
        while(n--)
        {
            for(i=0;i<100;i++);
        }
}  

/*
 *  d=0~7
 */
void set_start_page(unsigned char d)
{
    spi_data_ctr(0x00);
    spi_send_byte(0x00, (0xb0&0xf0)|d);
}

void set_start_column(unsigned char d)
{
    spi_data_ctr(0x00);
    spi_send_byte(0x00, 0x00+d%16);
    spi_send_byte(0x00, 0x10+d/16);
}

/*
 * 1page~8hang ,0~turn off ,1~turn on
 */
void full_screen(unsigned char data)
{
       volatile unsigned int i;
       volatile unsigned int j;
       volatile int test = 0;
    for(i=0;i<8;i++)
    {
            test++;
          spi_data_ctr(0x00);
          set_start_page(i);
          set_start_column(0x00);

       for(j=0;j<128;j++)
         {
             spi_data_ctr(0x80);
             spi_send_byte(0x00,data);
         }
    }
}

void clean_page(char page)
{
       unsigned char j;
        spi_data_ctr(0x00);
        set_start_page(page);
        set_start_column(0x00);
       for(j=0;j<128;j++)
         {
             spi_data_ctr(0x80);
             spi_send_byte(0x00,0x00);
         }

}

/* set point(x,y)
 * x_0~127 , y_0~7 page
 */
void set_x_y(unsigned char x, unsigned char y)
{
    spi_data_ctr(0x00);
    set_start_page(y);
    set_start_column(x);
}

/* x_0~127
 * y_0~63
 */
void set_point(unsigned char x, unsigned char y)
{
    unsigned char data;
    data=0x01<<(y%8);
    set_x_y(x,(y>>3));
    spi_data_ctr(0x80);
    spi_send_byte(0x00, data);
}


void show_ascii(unsigned char x, unsigned char y)
{
    unsigned char j;
    unsigned char t;
    unsigned char k;
  for(t=0;t<5;t++)
  {
    for(k=0;k<20;k++)
     {
        set_x_y(x+6*k,y+t);
        spi_data_ctr(0x80);
        for(j=0;j<6;j++)
        spi_send_byte(0x00,F6x8[k+20*t][j]);
     }
  }
}

/*uctech
*/
void show3(unsigned char x, unsigned char y, unsigned char addra)
{
    unsigned char j;
    set_x_y(x,y);
    for(j=0;j<8;j++)
    {
        spi_data_ctr(0x80);
        spi_send_byte(0x00,uctech[16*addra+j]);
    }
    set_x_y(x,y+1);
    for(j=8;j<16;j++)
    {
        spi_data_ctr(0x80);
        spi_send_byte(0x00,uctech[16*addra+j]);
    }
}


/*
 * show uctech
 */
void show_uctech(unsigned char x ,unsigned char y, unsigned char x2, unsigned char x3 )
{
    volatile unsigned char i;
    for(i=x2;i<x3+1;i++)
    {
       show3(x,y,i);
       x=x+8;
    }
}

void show_hex_num(char lie,char page,unsigned long num)
{
    volatile long temp = num;
             char str[10]={0};
             char str2[10]={0};
    volatile int i=0;
    volatile int t=0;
    volatile char ch;
    do{
        ch = (char)(temp % 16);
        switch(ch)
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:str[i++] = '0' + ch;break;
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:str[i++]='A'+ch-10;break;
        default: ;
        }
    }while(temp = temp>>4);
    str[i] = '\0';
     while(i!=0){
         str2[t]=str[i-1];
         t=t+1;
         i=i-1;
         str2[t]='\0';
     }

    show_string(lie,page,str2,2);
}

/*
 * x,y,choose_font
 */
void show_string(char x,char y, char string[],char choose)
{

    volatile int k=0;
    volatile int m=0;
    volatile int j;
    while(string[k] !='\0')
    {

        m=string[k];
        set_x_y(x,y);
        if(choose==1)
        {
            spi_data_ctr(0x80);
            for(j=0;j<8;j++)
            spi_send_byte(0x00,F8X16[m*16+j-32*16]);         //pre32(acsi)_unused
            set_x_y(x,y+1);
            spi_data_ctr(0x80);
            for(j=9;j<16;j++)
            spi_send_byte(0x00,F8X16[m*16+j-32*16]);
            x=x+8;
            if((x+8)>127){ x=0; y=y+2; }
            if(y>7){ x=0; y=0; }
        }
        else if(choose==2)
        {
            spi_data_ctr(0x80);
            for(j=0;j<6;j++)
            spi_send_byte(0x00,F6x8[m-32][j]);
            x=x+6;
            if((x+6)>127){ x=0; y=y+1; }
            if(y>7){ x=0; y=0; }
        }

        k=k+1;
    }
}


void oled_thread_trg()
{
    oled_init();

    while(1)
    {
        /*
    show_uctech(20,1,0,8);
    oled_delay(6000);
    clean_page(1);
    clean_page(2);
    show_uctech(10,2,0,8);
    oled_delay(6000);
    clean_page(2);
    clean_page(3);
    show_uctech(0,3,0,8);
    oled_delay(6000);
    clean_page(3);
    clean_page(4);
    show_uctech(10,4,0,8);
    oled_delay(6000);
    clean_page(4);
    clean_page(5);
    show_uctech(20,5,0,8);
    oled_delay(6000);
    clean_page(5);
    clean_page(6);
    show_uctech(30,6,0,8);
    oled_delay(6000);
    clean_page(6);
    clean_page(7);
    show_uctech(38,5,0,8);
    oled_delay(6000);
    clean_page(5);
    clean_page(6);
    show_uctech(46,4,0,8);
    oled_delay(6000);
    clean_page(4);
    clean_page(5);
    show_uctech(55,3,0,8);
    oled_delay(6000);
    clean_page(3);
    clean_page(4);
    show_uctech(46,2,0,8);
    oled_delay(6000);
    clean_page(2);
    clean_page(3);
    show_uctech(38,1,0,8);
    oled_delay(6000);
    clean_page(1);
    clean_page(2);
    show_uctech(30,0,0,8);
    oled_delay(6000);
    clean_page(0);
    clean_page(1);
*/
        oled_delay(6000);full_screen(0x00);show_uctech(20,1,0,8);
        oled_delay(6000);full_screen(0x00);show_uctech(10,2,0,8);
        oled_delay(6000);full_screen(0x00);show_uctech(0,3,0,8);
        oled_delay(6000);full_screen(0x00);show_uctech(10,4,0,8);
        oled_delay(6000);full_screen(0x00);show_uctech(20,5,0,8);
        oled_delay(6000);full_screen(0x00);show_uctech(30,6,0,8);
        oled_delay(6000);full_screen(0x00);show_uctech(38,5,0,8);
        oled_delay(6000);full_screen(0x00);show_uctech(46,4,0,8);
        oled_delay(6000);full_screen(0x00);show_uctech(55,3,0,8);
        oled_delay(6000);full_screen(0x00);show_uctech(46,2,0,8);
        oled_delay(6000);full_screen(0x00);show_uctech(38,1,0,8);
        oled_delay(6000);full_screen(0x00);show_uctech(30,0,0,8);

    }
}


void oled_init()
{
        spi_init(0x04, 0x08);           //8bit_data
        spi_data_ctr(0x00);             //send_cmd
        spi_send_byte(0x00, 0xae);
        spi_send_byte(0x00, 0x00);
        spi_send_byte(0x00, 0x10);
        spi_send_byte(0x00, 0x40);
        spi_send_byte(0x00, 0x81);
        spi_send_byte(0x00, 0xcf);
        spi_send_byte(0x00, 0xa0);      //a0  //a1       //x_diandao
        spi_send_byte(0x00, 0xc0);      //c0  //c8       //y_diandao
        spi_send_byte(0x00, 0xa6);
        spi_send_byte(0x00, 0xa8);
        spi_send_byte(0x00, 0x3f);      //3f  //1f
        spi_send_byte(0x00, 0xd3);
        spi_send_byte(0x00, 0x00);
        spi_send_byte(0x00, 0xd5);
        spi_send_byte(0x00, 0x80);
        spi_send_byte(0x00, 0xd9);
        spi_send_byte(0x00, 0xf1);
        spi_send_byte(0x00, 0xda);
        spi_send_byte(0x00, 0x12);      //12  //02
        spi_send_byte(0x00, 0xdb);
        spi_send_byte(0x00, 0x40);
        spi_send_byte(0x00, 0x20);
        spi_send_byte(0x00, 0x02);
        spi_send_byte(0x00, 0x8d);
        spi_send_byte(0x00, 0x14);
        spi_send_byte(0x00, 0xa4);
        spi_send_byte(0x00, 0xa6);
        spi_send_byte(0x00, 0xaf);

        full_screen(0x00);
}

