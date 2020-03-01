#include "platform.h"
#include "csr.h"


void vga_init()
{
	VGA_REG(VGA_CTRL)=0x0000;

	VGA_REG(VGA_CTRL) |= VGA_BL; 		//bl=1
	VGA_REG(VGA_CTRL) |= VGA_CSL; 		//csl=1

	VGA_REG(VGA_CTRL) |= VGA_VSL;		//vsl=1_vsync_=1
	VGA_REG(VGA_CTRL) |= VGA_HSL;		//hsl=1_hsync =1

	VGA_REG(VGA_CTRL) &= ~VGA_PC;		//pc=0

	VGA_REG(VGA_CTRL) |= VGA_CD_H;		// 24bit per pixel
	VGA_REG(VGA_CTRL) &= ~VGA_CD_L;

	VGA_REG(VGA_CTRL) &= ~VGA_VBL_H;	//burst 1 cycle
	VGA_REG(VGA_CTRL) &= ~VGA_VBL_L;

	VGA_REG(VGA_CTRL) &= ~VGA_CBSWE;	//cbswe=0
	VGA_REG(VGA_CTRL) &= ~VGA_CBSIE;	//cbsie=0

	VGA_REG(VGA_CTRL) &= ~VGA_VBSWE;		//vbswe=1,open_switch_vedio_memory
	VGA_REG(VGA_CTRL) &= ~VGA_VBSIE;		//vbsie=1

	VGA_REG(VGA_CTRL) &= ~VGA_HIE;		//HIE=0
	VGA_REG(VGA_CTRL) |= VGA_VIE;		//VIE=0
}


void vga_start()
{
	VGA_REG(VGA_CTRL) |=VGA_VEN;
}

void vga_htim(char thsync,char thgdel,int thgate)
{
	VGA_REG(VGA_HTIM) = ( (thsync<<24) | (thgdel << 16)|(thgate & 0xffff) );
}

void vga_vtim(char tvsync,char tvgdel,int tvgate)
{
	VGA_REG(VGA_VTIM) = ( (tvsync<<24) | (tvgdel << 16)|(tvgate & 0xffff) );
}

void vga_hvlen(int thlen ,int tvlen)
{
	VGA_REG(VGA_HVLEN) = ( (thlen << 16)|(tvlen & 0xffff) );
}

void vga_vbara(int vbara)
{
	VGA_REG(VGA_VBARA) = vbara;
}

void vga_vbarb(int vbarb)
{
	VGA_REG(VGA_VBARB) = vbarb;
}


