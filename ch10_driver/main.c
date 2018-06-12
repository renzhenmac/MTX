#include "type.h"
#include "queue.h"
#include "kernel.h"

extern void int80h(); //int80 handler, assembly function
extern void tinth(); //timer int handler, assembly function
extern void divide(); //devide-by-zero int handler, assembly function

int procSize = sizeof(PROC);
int nproc, rflag;

void set_vector(int vector, int handler) {
	put_word(handler, 0x0000, vector*4); 	// KPC points to handler
	put_word(0x1000, 0x0000, vector*4+2); 	// KCS segment=0x1000
}

void init() {
	PROC *p;
	PIPE *pip;
	OFT *fd;
	int i;
	printf("init ....\n");
	/**** initialize proc[] ****/
	for (i=0; i<NPROC; i++) { // initialize all procs
		p = &proc[i];
		p->pid = i;
		p->status = FREE;
		p->vforked = 0;
		p->priority = 1;
		p->next = &proc[i+1];
		p->name[1] = 'N';
	}
	proc[NPROC-1].next = 0;
	freeList = proc; // all procs are in freeList
	readyQueue = 0;
	sleepQueue = 0;
	/**** init Pipe & Oft list ****/
	for (i=0; i<NPIPE; i++) { // initialize all PIPE
		pip = &pipe[i];
		pip->next = &pipe[i+1];
	}
	pipe[NPIPE-1].next = 0;
	freePipe = pipe;
	
	for (i=0; i<NFD; i++) { // initialize all OFT
		fd = &oft[i];
		fd->next = &oft[i+1];
	}
	oft[NFD-1].next = 0;	
	freeOft = oft;

	/**** create P0 as running of the main ******/
	p = get_proc(&freeList); // allocate a PROC from freeList
	p->priority = 0; // P0's init prio is 0, others' are 1
	p->ppid = 0; // P0’s parent is itself
	p->status = READY;
	p->inkmode = 1; //as P0 is in kmode
	running = p;
	nproc = 1;	
}

int main(void) {
	vid_init();
	printf("MTX starts in main()\n");
	init(); // initialize and create P0 as running	
	kfork("/bin/u1"); // P0 kfork P1 and run goUmode	
	set_vector(80, (int)int80h);	
	set_vector(0, (int)divide);
	set_vector(8, (int)tinth);
//	timer_init();
	while(1) {
		while(!readyQueue) // P0 idle loop while readyQueue empty
			printf("In main, no other thread to switch\n");
		ksleep(running); // P0 sleep on its own address
		printf("main: switch\n");
		tswitch();
	}
}
