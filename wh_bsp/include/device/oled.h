#ifndef SDJ2102_OLED_H
#define SDJ2102_OLED_H

void oled_delay(int n);
void set_start_page(unsigned char d);
void set_start_column(unsigned char d);
void full_screen(unsigned char data);
void clean_page(char page);
void set_x_y(unsigned char x, unsigned char y);
void set_point(unsigned char x, unsigned char y);

void show_ascii(unsigned char x, unsigned char y);

void show3(unsigned char x, unsigned char y, unsigned char addra);
void show_uctech(unsigned char x ,unsigned char y, unsigned char x2, unsigned char x3 );
void show_string(char x,char y, char string[],char choose);
void oled_init();
void show_hex_num(char lie,char page,unsigned long num);

#endif
