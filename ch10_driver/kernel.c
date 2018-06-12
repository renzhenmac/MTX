#include "kernel.h"

PROC proc[NPROC], *running, *freeList, *readyQueue, *sleepQueue;
PIPE pipe[NPIPE], *freePipe; //pipe list
OFT oft[NFD], *freeOft; // file descriptor list
TQE tqe[NPROC], *tq;

/*************** kernel function *******************/

int scheduler() {
	if (running->status == READY)
		enqueue(&readyQueue, running);
	running = dequeue(&readyQueue);
	rflag = 0;
}

//re-enqueue the readyQueue, used after priority change
int reQready() {
	PROC *p, *tempQ = 0;
	while ( (p=dequeue(&readyQueue)) ) { // reorder readyQueue
		enqueue(&tempQ, p);
	}
	readyQueue = tempQ;
	//rflag = 0; // global reschedule flag
	if (running->priority < readyQueue->priority)
		rflag = 1;
}

PROC *kfork(char *filename) {
	int i;
	PROC *p;
	p = get_proc(&freeList);
	if (!p) {
		printf("no more PROC, kfork() failed\n");
		return 0;
	}
	p->status = READY;
	p->priority = 1; // priority = 1 for all proc except P0, which is 0
	p->ppid = running->pid; // parent = running
	p->parent = running;
	p->inkmode = 1; // 1 means in Umode, above 1 means in Kmode

	/* initialize new proc's kstack[ ] */
	if (p->pid == 0)
		return p;
	for (i=1; i<10; i++) // saved CPU registers
		p->kstack[SSIZE-i]= 0 ; // all 0's

	/* change the resume point to goUmode */
	p->kstack[SSIZE-1] = (int)goUmode; // resume point=address of body()
	p->ksp = &(p->kstack[SSIZE-9]); // proc saved sp

	/* create umode image if given filename */
	if(!filename) { // filename is zero
		p->uss = 0;
	}
	if(filename) {
		p->uss = (p->pid + 1)*OSSEG ;
		if(!load(filename,p->uss)) {
			printf("load %s image failed\n",filename);
			return 0;
		}
		p->usp = -24;
		put_word(0x0200,p->uss, -2);
		put_word(p->uss,p->uss, -4);
		for (i=3; i<=10; i++)
			put_word(0,p->uss, -2*i);
		put_word(p->uss,p->uss, -22);
		put_word(p->uss,p->uss, -24);
	}

	/* enqueue the new PROC */
	enqueue(&readyQueue, p); // enter p into readyQueue by priority
	nproc++;
	return p; // return child PROC pointer
}

int copyImage(u16 pseg, u16 cseg, u16 size) { // size counts by word, not byte
	u16 i;
	for (i=0; i<size; i++)
		put_word(get_word(pseg, 2*i), cseg, 2*i);
}

int fork() {
	int pid, i;
	u16 segment;
	PROC *p;
	printPROC("fork begin: readyQueue:", readyQueue);
	p = kfork(0); // kfork() a child, do not load image file
	if (p==0) return -1; // kfork failed
	segment = (p->pid+1)*0x1000; // child segment
	copyImage(running->uss, segment, 32*1024); // copy 32K words = 64k Byte
	p->uss = segment; // child’s own segment
	p->usp = running->usp; // same as parent's usp

	/*** initialize the file descriptor for pipe ***/
	for (i=0; i<NFD; i++) {
		if (running->fd[i]) { // copy only non-zero entries
			p->fd[i] = running->fd[i];
			p->fd[i]->refCount++; // inc OFT.refCount by 1
			if (p->fd[i]->mode == READ_PIPE)
				p->fd[i]->pipe_ptr->nreader++; // pipe.nreader++
			if (p->fd[i]->mode == WRITE_PIPE)
				p->fd[i]->pipe_ptr->nwriter++; // pipe.nwriter++
		}
	}

	/*** init the signal handlers to default value 0, normally means exit ***/
	for (i=0; i<NSIG; i++) {
		p->sig[i] = 0;
	}

	/**** change uDS, uES, uCS, AX in child's ustack ****/
	put_word(segment, segment, p->usp); // uDS=segment
	put_word(segment, segment, p->usp+2); // uES=segment
	put_word(0, segment, p->usp+2*8); // uax=0
	put_word(segment, segment, p->usp+2*10); // uCS=segment
	printPROC("fork end: readyQueue:", readyQueue);
	return p->pid;
}

int vfork() {
	int pid,i,w;
	u16 segment;
	PROC *p = kfork(0);
	if(p == 0) return -1;
	p->vforked = 1;

	/* copy a section of parent ustack for child to return to Umode */
	for(i=0; i<24; i++) { //24 words is enouth
		w = get_word(running->uss, running->usp + i*2);
		put_word(w, running->uss, running->usp - 1024 + i*2);
	}
	p->uss = running->uss;
	p->usp = running->usp - 1024;
	put_word(0, running->uss, p->usp + 8*2);// set child's return value to 0
	p->kstack[SSIZE - 1] = (int)goUmode;
	printf("---vfork done---\n");
	return p->pid;
}

int kexec(char *y) { // y points at filename in Umode space
	int i, length = 0 ;
	char filename[64], *cp = filename;
	u16 segment;

	/* so vforked process DO NOT loads to parent's share uss */
	if(running->vforked) {
		segment = (running->pid + 1)*0x1000;
	}
	if(!running->vforked)
		segment = running->uss;

	/* get filename from U space with a length limit of 64 */
	while( (*cp++ = get_byte(running->uss, y++)) && length++ < 64 );
	printf("kexec filename is: %s\n",filename);
	if(!load(filename, segment)) { // load ALWAYS returns 1,only print in fail ???
		printf("load %s failed\n", filename);
		return 0;
	}

	/* re-initialize process ustack for it return to VA=0 */
	for (i=1; i<=12; i++)
		put_word(0, segment, -2*i);
	running->uss = segment;
	running->usp = -24; // new usp = -24

	/* -1   -2  -3  -4 -5 -6 -7 -8 -9 -10  -11 -12 ustack layout */
	/* flag uCS uPC ax bx cx dx bp si  di  uES uDS */
	put_word(segment, segment, -2*12); // saved uDS=segment
	put_word(segment, segment, -2*11); // saved uES=segment
	put_word(segment, segment, -2*2); // uCS=segment; uPC=0
	put_word(0x0200, segment, -2*1); // Umode flag=0x0200
	return 1;
}

void ksleep(int event) {
	running->event = event;
	running->status = SLEEP;
	removeFromList(&readyQueue, running);
	enqueue(&sleepQueue, running);
}

//wake up all processes sleeping on event,put them to readyQueue
void kwakeup(int event) {
	PROC *p = sleepQueue;
	if(sleepQueue) {
		while(p) {
			while(p && (p->event != event))
				p = p->next;
			if(p) {
				removeFromList(&sleepQueue, p);
				p->event = 0;
				p->status = READY;
				enqueue(&readyQueue, p);
				p = p->next;
			}
		}
	}
}

int chpriority(int pid, int pri) {
	PROC *p;
	int i, ok=0, reQ=0;
	if (pid == running->pid) {
		running->priority = pri;
		if (pri < readyQueue->priority)
			rflag = 1;
		return 1;
	}
	// if not for running, for both READY and SLEEP procs
	for (i=1; i<NPROC; i++) {
		p = &proc[i];
		if (p->pid == pid && p->status != FREE) {
			p->priority = pri;
			ok = 1;
			if (p->status == READY) // in readyQueue==> redo readyQueue
				reQ = 1;
		}
	}
	if (!ok) {
		printf("chpriority failed\n");
		return 0;
	}
	if (reQ) // changed priority in readyQueue
		reQready();
	return 1;
}

int kexit(int exitValue) {
	int i, wakeupP1 = 0;
	PROC *p;
	if (running->pid==1 && nproc>2) { // nproc = number of active PROCs
		printf("other procs still exist, P1 can't die yet\n");
		return -1;
	}
	/* send children (dead or alive) to P1's orphanage */
	for (i = 1; i < NPROC; i++) {
		p = &proc[i];
		if (p->status != FREE && p->ppid == running->pid) {
			p->ppid = 1;
			p->parent = &proc[1];
			wakeupP1++;
		}
	}
	/* record exitValue and become a ZOMBIE */
	running->exitCode = exitValue;
	running->status = ZOMBIE;
	/* wakeup parent and also P1 if necessary */
	kwakeup(running->parent); // parent sleeps on its PROC address
	if (wakeupP1)
		kwakeup(&proc[1]);
	printPROC("kexit: switch to readyQueue:", readyQueue);
	tswitch(); // give up CPU
}

//find **one ZOMBIE child** and return with the PID
int kwait(int *status) { // wait for ZOMBIE child
	PROC *p;
	int i, hasChild = 0;
	while(1) { // search PROCs for a child
		for (i=1; i<NPROC; i++) { // exclude P0
			p = &proc[i];
			if (p->status != FREE && p->ppid == running->pid) {
				hasChild = 1; // has child flag
				if (p->status == ZOMBIE) { // lay the dead child to rest
					*status = p->exitCode; // collect its exitCode
					p->status = FREE; // free its PROC
					removeFromList(&readyQueue, p);
					put_proc(&freeList, p); // to freeList
					nproc--; // once less processes
					return(p->pid); // return its pid
				}
			}
		}
		if (!hasChild) return -1; // no child, return ERROR
		ksleep(running); // still has kids alive: sleep on PROC address
		tswitch();
	}
}

int kpipe(int pd[]) {
	PIPE *pip;
	OFT *readOFT, *writeOFT;

	//initialize the PIPE
	pip = get_pipe(freePipe);
	if(!pip) {
		printf("get_pipe failed\n");
		return -1;
	}
	pip->head = 0;
	pip->tail = 0;
	pip->data = 0;
	pip->room = PSIZE;
	pip->nreader = 1;
	pip->nwriter = 1;

	// Read side of the pipe
	readOFT = get_oft(freeOft);
	if(!readOFT) {
		printf("Read side get_oft failed\n");
		return -1;
	}
	readOFT->mode = READ_PIPE;
	readOFT->refCount = 1;
	readOFT->pipe_ptr = pip;

	// Write side of the pipe
	writeOFT = get_oft(freeOft);
	if(!writeOFT) {
		printf("Write side get_oft failed\n");
		return -1;
	}
	writeOFT->mode = WRITE_PIPE;
	writeOFT->refCount = 1;
	writeOFT->pipe_ptr = pip;

	//locate fd[3] and fd[4] in PROC, 3 for read, 4 for write
	running->fd[READ_FD] = readOFT;
	running->fd[WRITE_FD] = writeOFT;

	pd[0] = 3;
	pd[1] = 4; // let syscall kkpipe send to Userspace
	return 0;
}

int read_pipe(int fdi, char *buf, int n) {
	char *cp;
	PIPE *pip;
	int r = 0;
	if (n <= 0) return 0;
	if(fdi>=NFD || fdi<0) {
		printf("file descriptor %d out of range\n", fdi);
		return 0;
	}
	if(!running->fd[fdi]) {
		printf("file descriptor %d is not in use\n", fdi );
		return 0;
	}
	pip = running->fd[fdi]->pipe_ptr;
	cp = buf;
	while(n) {
		while(pip->data) {
			//read a byte form pipe to buf
			*cp++ = pip->buf[pip->head];
			pip->head = (pip->head + 1)%PSIZE;
			n--;
			r++;
			(pip->data)--;
			(pip->room)++;
			if (n==0)
				break;
		}
		if (r) { // has read some data
			kwakeup(&pip->room);
			return r;
		}
		// pipe has no data
		if (pip->nwriter) { // if pipe still has writer
			kwakeup(&pip->room); // wakeup ALL writers, if any.
			ksleep(&pip->data); // sleep for data
			tswitch();
			continue;
		}
		// pipe has no writer and no data
		printf("read_pipe: No writer NO data,exit\n");
		return 0;
	}
}


int write_pipe(int fdi, char *buf, int n) {
	char *cp;
	PIPE *pip;
	int r = 0;
	if (n <= 0) return 0;
	if(fdi>=NFD || fdi<0) {
		printf("file descriptor %d out of range\n", fdi);
		return 0;
	}
	if(!running->fd[fdi]) {
		printf("file descriptor %d is not in use\n", fdi);
		return 0;
	}
	pip = running->fd[fdi]->pipe_ptr;
	cp = buf;
	while (n) {
		if (!pip->nreader) { // no more readers
			printf("write_pipe: broken pipe\n");
			return 0;
		}
		while(pip->room) {
			//write a byte from buf to pipe;
			pip->buf[pip->tail] = *cp++;
			pip->tail = (pip->tail + 1)%PSIZE;
			r++;
			pip->data++;
			pip->room--;
			n--;
			if (n==0)
				break;
		}
		kwakeup(&pip->data); // wakeup ALL readers, if any.
		if (n==0)
			return r; // finished writing n bytes
		ksleep(&pip->room); // sleep for room
		tswitch();
	}
}

int close_pipe(int fdi) {
	OFT *fdp;
	PIPE *pip;
	printf("-------------------------------------\n");
	printOFT("into close_pipe: freeOFT:", freeOft);
	printPIPE("into close_pipe: freePIPE:", freePipe);

	if( fdi >= NFD || fdi < 0) {
		printf("close_pipe: fdi %d not valid\n", fdi);
		return -1;
	}
	if(!running->fd[fdi]) {
		printf("close_pipe: fdi %d is not in use\n", fdi);
		return -1;
	}
	fdp = running->fd[fdi];
	fdp->refCount--;
	pip = fdp->pipe_ptr;

	if(fdp->mode == WRITE_PIPE) {
		pip->nwriter--;
		if(!pip->nreader) {
			printf("close_pipe: no reader!\n");
			put_pipe(&freePipe, pip); // let kpipe() do the data initialize
			fdp->pipe_ptr = 0;
			put_oft(&freeOft, fdp);
			kwakeup(&pip->room);
		}
	} else { // mode is READ_PIPE
		pip->nreader--;
		if(!pip->nwriter) {
			if(!pip->nreader) {
				printf("close_pipe: no reader no writer\n");
				put_pipe(&freePipe, pip); // let kpipe() do the data initialize
				fdp->pipe_ptr = 0;
				put_oft(&freeOft, fdp);
			} else {
				if(!pip->data) {
					printf("close_pipe: reader but no data\n");
					put_pipe(&freePipe, pip); // let kpipe() do the data initialize
					fdp->pipe_ptr = 0;
					put_oft(&freeOft, fdp);
				} else {
					// there's more to read
					printf("close_pipe: reader,data...but no writer\n");
				}
			}
		}
	}
	// now don't have to recycle pipe but maybe need to recycle oft
	if(!fdp->refCount) {
		put_oft(&freeOft, fdp);
	}
	printOFT("out close_pipe: freeOFT:", freeOft);
	printPIPE("out close_pipe: freePIPE:", freePipe);
	printf("-------------------------------------\n");
}


int itimer(int t) {
	TQE *tqe_p = &tqe[running->pid];
	tqe_p->time = t;
	tqe_p->proc = running;
	lock();
	put_tq(&tq, tqe_p);
	unlock();
	ksleep(running);
	printf("--------- itimer: after running sleep: -------\n");
	kps();
	printf("-----------------------------------------------\n");
	tswitch();
}

int pipe_stat() {
	PROC *p;
	PIPE *pip;
	p = running;
	if(p->fd[READ_FD])
		pip = p->fd[READ_FD]->pipe_ptr;
	if(p->fd[WRITE_FD])
		pip = p->fd[WRITE_FD]->pipe_ptr;
	else {
		printf("NO FD in running PROC\n");
		return 0;
	}
	printf("pipe stat: nwriter: %d | nreader: %d\n", pip->nwriter, pip->nreader);
}

int install_handler(int signo, u16 func){
//	printf("install_handler: instal handler address %d for sig %d\n", func, signo);
	running->sig[signo] = func;
	return 0;
}


