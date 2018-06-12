#! /bin/bash

rm *.o
as86 -o u.o u.s
bcc -c -ansi bio.c
bcc -c -ansi u1.c
bcc -c -ansi u2.c
ld86 -o u1 u.o bio.o u1.o mtxlib /usr/lib/bcc/libc.a
ld86 -o u2 u.o bio.o u2.o mtxlib /usr/lib/bcc/libc.a

