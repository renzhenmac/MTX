#! /bin/bash

rm *.o
as86 -o k.o k.s
bcc -c -w -ansi *.c
ld86 -d -o mtx k.o main.o kernel.o bio.o queue.o syscalls.o timer.o signal.o mtxlib /usr/lib/bcc/libc.a
