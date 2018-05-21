#include "timer.h"
#include "kernel.h"

int tick = 0; // tick count

int timer_init() { // Initialize channel 0 of the 8253A timer to 60 Hz
	out_byte(TIMER_MODE, SQUARE_WAVE); // set timer continuous MODE
	out_byte(TIMER_PORT, TIMER_COUNT); // write timer low byte
	out_byte(TIMER_PORT, TIMER_COUNT >> 8);// write timer high byte
	enable_irq(TIMER_IRQ);
}

int enable_irq(u16 irq) {
	out_byte(INT_MASK, in_byte(INT_MASK) & ~(1 << irq));
}

int disable_irq(u16 irq) {
	out_byte(INT_MASK, in_byte(INT_MASK) | (1 << irq));
}

int thandler() {
	int counter;
	TQE *tmp; // to remove the first TQE of tq
//	printf("----# timer interrupt in ");
//	running->inkmode > 1 ? putc('K') : putc('U'); printf("mode #----\n");
	tick++;
	tick %= 60;
	if (tick == 0) { // at each second
		printf("--+++-- tick 1 second --+++--\n");
		if(!tq){
			out_byte(0x20, 0x20); // issue EOI to 8259 PIC
			return;
		}
		tq->time--;
		while(tq->time == 0){
			tmp = tq;
			tq = tq->next;
			tmp->next = 0;
			kwakeup(tmp->proc);
			printf("thandler: wake up %d\n", tmp->proc);
			if(!tq){
				printf("thandler: tq is empty\n");
				break;
			}
		}		
	}
	out_byte(0x20, 0x20); // issue EOI to 8259 PIC
}
