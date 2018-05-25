Chapter 9 Signals and Signal Processing

Added divide-by-zero handler, didn't use longjump but a normal function, it works and I don't know why.

I think it's because the function changed bx in some mysterious way.

The divide assambly code is idiv bx, so if bx is 0, the idiv is not successful and triggered int0. And after the iret it comes back to idiv bx.

One way is to change bx in Umode divide-by-zero handler, which should be a assembly function.
