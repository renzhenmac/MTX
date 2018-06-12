#ifndef kernel_h
#define kernel_h

#include "type.h"
#include "queue.h"

extern PROC proc[NPROC], *running, *freeList, *readyQueue, *sleepQueue;
extern int nproc,rflag;
extern PIPE pipe[NPIPE], *freePipe;
extern OFT oft[NFD], *freeOft;
extern TQE tqe[NPROC], *tq;    // tq = timer queue pointer

extern int goUmode(); // external assembly function

int scheduler();
int reQready();
PROC *kfork(char *filename);
int copyImage(u16 pseg, u16 cseg, u16 size);
int fork();
int vfork();
int kexec(char *y);
void ksleep(int event);
void kwakeup(int event);
int chpriority(int pid, int pri);
int kexit(int exitValue);
int kwait(int *status);
int kpipe(int pd[]);
int read_pipe(int fd, char *buf, int n);
int write_pipe(int fd, char *buf, int n);
int close_pipe(int fd);
int itimer(int t);
int pipe_stat();
int install_handler(int signo, int func);

#endif