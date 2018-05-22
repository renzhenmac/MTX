#ifndef syscalls_h
#define syscalls_h

#include "type.h"
#include "queue.h"

u8 get_byte(u16 segment, u16 offset);
int put_byte(u8 byte, u16 segment, u16 offset);
u16 get_word(u16 segment, u16 offset);
int put_word(u16 word, u16 segment, u16 offset);
void getStringFromUMode(char *s, char uModeStr[]);
void putStringToUMode(char *s, char uModeStr[]);

int kcinth();
int getpid();
int kps();
int kchname(char *name);
int kkfork();
int knfork();
int kswitch();
int kkwait(int *uAddress);
int kkexit(int val);
int kkpipe(int pd[]);
int kread_pipe(int fd, char *buf, int n);
int kwrite_pipe(int fd, char *buf, int n);

#endif