#ifndef queue_h
#define queue_h

#include "type.h"

PROC *get_proc(PROC **list);
void put_proc(PROC **list, PROC *p);
void enqueue(PROC **queue, PROC *p);
PROC *dequeue(PROC **queue);
void removeFromList(PROC **list, PROC *p);
void printPROC(char *name, PROC *list);
void printOFT(char *name, OFT *list);
void printPIPE(char *name, PIPE *list);

// something about pipe&oft
PIPE *get_pipe(PIPE **list);
void put_pipe(PIPE **list, PIPE *p);

OFT *get_oft(OFT **list);
void put_oft(OFT **list, OFT *p);

void put_tq(TQE **tq, TQE *tqe);

#endif
