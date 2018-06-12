#! /bin/bash

rm *.o
as86 -o k.o k.s
bcc -c -w -ansi *.c
ld86 -d -o mtx k.o video_driv.o main.o bio.o kernel.o queue.o syscalls.o timer.o signal.o mtxlib /usr/lib/bcc/libc.a
