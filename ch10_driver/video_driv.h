#ifndef video_driv_h
#define video_driv_h

#include "type.h"

#define VDC_INDEX 0x3D4
#define VDC_DATA 0x3D5
#define CUR_SIZE 10 // cursor size register
#define VID_ORG 12 // start address register
#define CURSOR 14 // cursor position register
#define LINE_WIDTH 80 // # characters on a line
#define SCR_LINES 25 // # lines on the screen
#define SCR_BYTES 4000 // bytes of one screen=25*80
#define CURSOR_SHAPE 15 // block cursor for EGA/VGA

void vid_init();
void scroll();
void move_cursor();
int putc(char c);
void set_VDC(u16 reg, u16 val);
int change_color(u16 c);
void show_clock(int c);  

// attribute byte: 0x0HRGB, H=highLight; RGB determine color
static u16 base = 0xB800; // VRAM base address
static u16 vid_mask = 0x3FFF; // mask=Video RAM size - 1
static u16 offset; // offset from VRAM segment base
static int color; // attribute byte
static int org; // current display origin, r.e. VRAM base
static int row, column; // logical row, col position

#endif