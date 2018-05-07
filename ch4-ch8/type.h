#ifndef type_h
#define type_h

#define NPROC 9
#define SSIZE 1024
/******* PROC status ********/
#define FREE 0
#define READY 1
#define RUNNING 2
#define STOPPED 3
#define SLEEP 4
#define ZOMBIE 5
#define NFD 10
#define READ_FD 3
#define WRITE_FD 4
#define NPIPE 10
#define PSIZE 64

#define READ_PIPE 0
#define WRITE_PIPE 1

#define OSSEG 0x1000

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned long  u32;

typedef struct pipe {
	struct pipe *next;
	char buf[PSIZE]; // circular data buffer
	int head, tail; // circular buf index
	int data, room; // number of data & room in pipe
	int nreader, nwriter; // number of readers, writers on pipe
} PIPE;

typedef struct oft {
	struct oft *next;
	int mode; // READ_PIPE|WRITE_PIPE
	int refCount; // number of PROCs using this pipe end
	struct pipe *pipe_ptr; // pointer to the PIPE object
} OFT;

typedef struct proc {
	struct proc *next;
	int *ksp;
	int uss;
	int usp;
	int inkmode; //ADD: process in Kmode flag; initial = 1
	int pid; // add pid for identify the proc
	int ppid; // parent pid;
	int status; // status = FREE|READY|STOPPED|DEAD, etc
	int priority; // scheduling priority
	int event; // event sleeping on
	int vforked; // vforked, share segment with parent
	int exitCode;
	struct proc *parent;
	char name[32];
	OFT *fd[NFD];
	int kstack[SSIZE]; // proc stack area
} PROC;

typedef struct tq {
	struct tq *next; // next element pointer
	int time; // requested time
	struct PROC *proc; // pointer to PROC
	int (*action)(); // 0|1|handler function pointer
} TQE;


#endif