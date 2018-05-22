#include "type.h"
#include "queue.h"
#include "kernel.h"

// return the first *PROC in list
PROC *get_proc(PROC **list) {
	PROC *p = *list;
	if(p) {
		*list = (*list)->next;
		p->next = 0;
	}
	return p;
}

void put_proc(PROC **list, PROC *p) {
	PROC *tmp = *list;
	if (!tmp) { //list is empty
		*list = p;
		p->next = 0;
	} else {
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = p;
		p->next = 0;
	}
}

void enqueue(PROC **queue, PROC *p) {
	PROC *temp, *previous;
	temp = previous = *queue;
	if(!temp) { // empty queue
		*queue = p;
		p->next = 0;
		return;
	}
	while(temp && (p->priority <= temp->priority)) {
		previous = temp;
		temp = temp->next;
	}
	p->next = previous->next; //true even when previous is temp
	previous->next = p;
}

void put_tq(TQE **tq, TQE *tqe){
	TQE *now, *previous;
	int count = 0;
	now = previous = *tq;
	if(!*tq){
		*tq = tqe;
		tqe->next = 0;
		return;
	}
	while(now){
		count += now->time;
		if(count <= tqe->time){
			previous = now;
			now = now->next;
		}
		else break;
	}
	previous->next = tqe;
	tqe->next = now;
	tqe->time -= count;
}

PROC *dequeue(PROC **queue) {
	PROC *temp = 0;
	if (*queue) {
		temp = *queue;
		(*queue) = (*queue)->next;
		temp->next = 0;
		return temp;
	}
	return temp;
}


void removeFromList(PROC **list, PROC *p) {
	PROC *tmp = *list;
	if (tmp) {
		if(tmp == p) { //remove queue head
			*list = tmp->next;
			tmp->next = 0;
		}
		while(tmp && tmp->next != p)
			tmp = tmp->next;
		if(tmp) {
			tmp->next = p->next;
			p->next = 0;
		}
	}
}

void printPROC(char *name, PROC *list) {
	PROC *tmp = list;
	if(name)
		printf(name);
	while(tmp) {
		printf("%d",tmp->pid);
		if(tmp->event)
			printf("[%d]",tmp->event);
		printf(" -->");
		tmp = tmp->next;
	}
	printf(" NULL\n");
}

void printOFT(char *name, OFT *list) {
	OFT *tmp = list;
	int count = 0;
	if(name)
		printf(name);
	while(tmp) {
		count++;
		tmp = tmp->next;
	}
	printf(" %d\n", count);
}

void printPIPE(char *name, PIPE *list) {
	PIPE *tmp = list;
	int count = 0;
	if(name)
		printf(name);
	while(tmp) {
		count++;
		tmp = tmp->next;
	}
	printf(" %d\n", count);
}

//something about pipe&Oft, should not be here, but still OK

PIPE *get_pipe(PIPE **list) {
	PIPE *p = *list;
	if(p) {
		*list = (*list)->next;
		p->next = 0;
	}
	return p;
}

void put_pipe(PIPE **list, PIPE *p) {
	PIPE *tmp = *list;
	if (!tmp) { //list is empty
		*list = p;
		p->next = 0;
	} else {
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = p;
		p->next = 0;
	}
}

OFT *get_oft(OFT **list) {
	OFT *p = *list;
	if(p) {
		*list = (*list)->next;
		p->next = 0;
	}
	return p;
}

void put_oft(OFT **list, OFT *p) {
	OFT *tmp = *list;
	if (!tmp) { //list is empty
		*list = p;
		p->next = 0;
	} else {
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = p;
		p->next = 0;
	}
}
