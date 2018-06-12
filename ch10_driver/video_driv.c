/*********** Display Driver vid.c file of MTX kernel ************/
#include "video_driv.h"

void vid_init() { // initializes org=0 (row,column)=(0,0)
	int i, w;
	org = row = column = 0; // initialize globals
	color = 0x0C; // high YELLOW;
	set_VDC(CUR_SIZE, CURSOR_SHAPE); // set cursor size
	set_VDC(VID_ORG, 0); // display origin to 0
	set_VDC(CURSOR, 0); // set cursor position to 0
	w = 0x0700; // White, blank char
	for (i=0; i<25*80; i++) // clear screen
		put_word(w, base, 0+2*i); // write 25*80 blanks to VRAM
}

void scroll() { //scroll UP one line
	u16 i, w, bytes;
	// test offset = org + ONE screen + ONE more line
	offset = org + SCR_BYTES + 2*LINE_WIDTH;
	if (offset <= vid_mask) // offset still within VRAM area
		org += 2*LINE_WIDTH; // just advance org by ONE line
	else { // offset exceeds VRAM area ==> reset to VRAM beginning by
		// copy current rows 1-24 to BASE, then reset org to 0
		for (i=0; i<24*80; i++) {
			w = get_word(base, org+160+2*i);
			put_word(w, base, 0+2*i);
		}
		org = 0;
	}
	// org has been set up properly
	offset = org + 2*24*80; // offset = beginning of row 24
	// copy a line of BLANKs to row 24
	w = 0x0C00; // HRGB=1100 ==> HighLight RED, Null char
	for (i=0; i<80; i++)
		put_word(w, base, offset + 2*i);
	set_VDC(VID_ORG, org >> 1); // set VID_ORG to org
}

void move_cursor() { // move cursor to current position
	int pos = 2*(row*80 + column);
	offset = (org + pos) & vid_mask;
	set_VDC(CURSOR, offset >> 1);
}

// display a char, handle special chars '\n','\r','\b'
// right now we just consider '\n' means '\n\r'
int putc(char c) {
	u16 w, pos;
	if (c == '\n') {
		row++;
		if (row >= 25) {
			row = 24;
			scroll();
		}
		column=0;
		move_cursor();
		return;
	}
	if (c == '\r') {
		column=0;
		move_cursor();
		return;
	}
	if (c == '\b') {
		if (column > 0) {
			column--;
			move_cursor();
			put_word(0x0700, base, offset);
		}
		return;
	}
	// c is an ordinary char
	pos = 2*(row*80 + column);
	offset = (org + pos) & vid_mask;
	w = (color << 8) + c;
	put_word(w, base, offset);
	column++;
	if (column >= 80) {
		column = 0;
		row++;
		if (row >= 25) {
			row = 24;
			scroll();
		}
	}
	move_cursor();
}

void set_VDC(u16 reg, u16 val) { //set VDC register reg to val
	lock();
	out_byte(VDC_INDEX, reg); // set index register
	out_byte(VDC_DATA, (val>>8)&0xFF); // output high byte
	out_byte(VDC_INDEX, reg + 1); // next index register
	out_byte(VDC_DATA, val&0xFF); // output low byte
	unlock();
}

int change_color(int c) {
	color = c;
	return;
}

void show_clock(int t) {
	int hour,min,sec;
	hour = t/3600;
	min = (t%3600)/60;
	sec = (t%3600)%60;
//	printf("time: %d:%d:%d\n", hour, min, sec);
	put_word((color << 8) + (hour/10) + '0', base, org+2*(25*80-8));
	put_word((color << 8) + (hour%10) + '0', base, org+2*(25*80-7));
	put_word((color << 8) + ':', base, org+2*(25*80-6));
	put_word((color << 8) + (min/10) + '0', base, org+2*(25*80-5));
	put_word((color << 8) + (min%10) + '0', base, org+2*(25*80-4));
	put_word((color << 8) + ':', base, org+2*(25*80-3));
	put_word((color << 8) + (sec/10) + '0', base, org+2*(25*80-2));
	put_word((color << 8) + (sec%10) + '0', base, org+2*(25*80-1));
}
