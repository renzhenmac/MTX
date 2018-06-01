Chapter 9 Signals and Signal Processing

Added divide-by-zero handler, didn't use longjump but a normal function, it works and I don't know why !!!
Maybe printf has some side effect, but it shouldn't. I rewrite the putc to remove the "movb  bl,#0x0D", no effect.

In u2.c, we do the i/j, j is 0 and i is 20.
The assambly code is "idiv bx", so if bx is 0, the idiv is not successful and triggered int0. After the iret, it should comes back to "idiv bx" again.

One way is to change bx in Umode divide-by-zero handler. 
Another way is add the return address of divide-by-zero handler by 2, so jumps over the "idiv bx",
but all methods change the i and j, I don't know why.

---------------------------update---------------------------------

problems solved 
calling printf changes the bx
j is not changed if the handler is right, the right handler is in u.s. The handler should be some assembly function, cause it's called between a assembly procedure, it can't use the registers freely as a c function. 
i is changed because it's in the same address as uSP+13, where sig# is inserted as Figure 9.2 shows
