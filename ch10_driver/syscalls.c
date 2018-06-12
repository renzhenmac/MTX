#include "syscalls.h"

/****** MTX5.0 syscall handler: ustack layout in syscall ************
usp   1   2   3   4   5   6   7   8   9  10   11   12  13  14  15  16
--|--------------------------------------------------------------------
|uds|ues|udi|usi|ubp|udx|ucx|ubx|uax|upc|ucs|uflag|rPC| a | b | c | d |
---------------------------------------------------------------------*/
// test for notpad++

#define AX 8
#define PA 13

extern PROC proc[NPROC], *running, *freeList, *readyQueue, *sleepQueue;

//*********** Low level system calls, copied from techfreak's github
u8 get_byte(u16 segment, u16 offset) {
	u8 byte;
	setds(segment);
	byte = *(u8 *)offset;
	setds(OSSEG);
	return byte;
}

int put_byte(u8 byte, u16 segment, u16 offset) {
	setds(segment);
	*(u8 *)offset = byte;
	setds(OSSEG);
	return 0;
}

u16 get_word(u16 segment, u16 offset) {
	u16 word;
	setds(segment);
	word = *(u16 *)offset;
	setds(OSSEG);
	return word;
}

int put_word(u16 word, u16 segment, u16 offset) {
	setds(segment);
	*(u16 *)offset = word;
	setds(OSSEG);
	return 0;
}

void getStringFromUMode(char *s, char uModeStr[]) {
	char byte;
	int i = 0;

	//read byte from segment
	byte = get_byte(running->uss, s); //check if it's in uss

	while(byte) {
		uModeStr[i++] = byte;
		byte = get_byte(running->uss, s + i);
	}
	uModeStr[i] = 0;
}

void putStringToUMode(char *s, char uModeStr[]) {
	int i = 0;
	char *p = uModeStr;

	while(*p) {
		put_word(*p, running->uss, s + i);
		i++;
		p++;
	}

	put_word(0, running->uss, s + i); //make sure it's null terminated
}

//********* Low level system calls finish *******

int kcinth() {
	u16 segment, offset;
	int a, b, c, d, r;
	segment = running->uss;
	offset = running->usp;
	/* get syscall parameters from ustack */
	a = get_word(segment, offset + 2*PA);
	b = get_word(segment, offset + 2*(PA+1));
	c = get_word(segment, offset + 2*(PA+2));
	d = get_word(segment, offset + 2*(PA+3));
	/* route syscall call to kernel functions by call# a */
	switch(a) {
	case 0 :
		r = getpid();
		break;
	case 1 :
		r = kps();
		break;
	case 2 :
		r = kchname(b);
		break;
	case 3 :
		r = kkfork();
		break; // kfork
	case 4 :
		r = kswitch();
		break;
	case 5 :
		r = kkwait(b);
		break;
	case 6 :
		r = kkexit(b);
		break;
	case 7 :
		r = knfork();
		break; // fork
	case 8 :
		r = kexec(b);
		break;
	case 9 :
		r = vfork();
		break; // vfork
	case 30 :
		r = kkpipe(b);
		break; // creat pipe
	case 31 :
		r = kread_pipe(b,c,d);
		break;
	case 32 :
		r = kwrite_pipe(b,c,d);
		break;
	case 33 :
		r = close_pipe(b);
		break;
	case 34 :
		r = itimer(b);
		break;
	case 35 :
		r = pipe_stat();
		break;
	case 36 :
		r = install_handler(b,c);
		break;
	case 37:
		r = putc(b);
		break;
	case 38:
		r = change_color(b);
		break;
	default:
		printf("invalid a syscall %d\n", a);
	}
	put_word(r, segment, offset + 2*AX); // return value in uax
}

int getpid() {
	return running->pid;
}

int kps() {
	printPROC("readyQueue:",readyQueue);
	printPROC("sleepQueue:",sleepQueue);
}

int kchname(char *name) {
	char s[32];
	int i,index;
	u16 uChar,uSEG;
	uSEG = (running->pid + 1)*0x1000;
	uChar = get_byte(uSEG, name);
	index = 1;
	for(i=0; i<32; i++) {
		if(!uChar) break;
		s[i] = uChar;
		uChar = get_byte(uSEG, name + index);
		index++;
	}
	strcpy(running->name, s);
	printf("kernel chname as: %s\n", running->name);
}

int kkfork() {
	PROC *p = kfork();
	if (p == 0) {
		printf("kfork failed\n");
		return -1;
	}
	return p->pid;
}

int knfork() {
	int pid = fork();
	if (pid == -1) printf("fork failed\n");
	return pid;
}

int kswitch() {
	if(readyQueue) {
		tswitch();
	}
	else {
//		printf("kswitch: empty readyQ, NO switching\n");
	}
}

int kkwait(int *uAddress) {
	int status,rval;
	u16 uSEG = (running->pid + 1)*0x1000;
	rval = kwait(&status);
	put_word(status, uSEG, uAddress);
	return rval;
}

int kkexit(int val) {
	return kexit(val);
}

int kkpipe(int pd[]) { // int pd[2] in userland
	int i, upd[2];
	u16 uSEG = (running->pid + 1)*0x1000;
	i = kpipe(upd); // kipie return 0 as OK
	if(i) {
		printf("pipe locate failed\n");
		return -1;
	}
	put_word(upd[0], uSEG, (int)pd);
	put_word(upd[1], uSEG, (int)pd + 2 ); // 2 bytes makes a word
	return i;
}

int kread_pipe(int fd, char *buf, int n) {	
	char UmodeString[128];
	int i;
//	printf("entered kread_pipe\n");
	i = read_pipe(fd, UmodeString, n);
//	printf("kread_pipe returned %d\n", i);
//	printf("kread_pipe read out kernel string: %s\n", UmodeString);
	putStringToUMode(buf, UmodeString);
	return i;
}

int kwrite_pipe(int fd, char *buf, int n) {
	char UmodeString[128];
	int i;
//	printf("entered kwrite_pipe\n");
	getStringFromUMode(buf, UmodeString);
//	printf("kwrite_pipe receive Umode string: %s\n", UmodeString);
	i = write_pipe(fd, UmodeString, n);
//	printf("kwrite_pipe returned %d\n", i);
	return i;
}