#ifndef timer_h
#define timer_h

#include "type.h"
#define LATCH_COUNT 0x00 // cc00xxxx, cc=channel=00, x=any
#define SQUARE_WAVE 0x36 // ccaammmb, aa=access,mmm=mode,b=BCD
#define TIMER_FREQ 1193182L // timer frequency
#define TIMER_COUNT TIMER_FREQ/60 //initial value of counter
#define TIMER_PORT 0x40 // channel 0 timer port address
#define TIMER_MODE 0x43
#define TIMER_IRQ 0 // IRQ0
#define INT_CNTL 0x20 // master PIC control register
#define INT_MASK 0x21 // master PIC mask reg:bit i=0=enable

extern int tick; // tick count
int timer_init();
int enable_irq(u16 irq);
int disable_irq(u16 irq);
int thandler(); // jobs like print the clock

#endif
