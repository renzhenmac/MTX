#! /bin/bash

dd if=a.out of=vdisk bs=16 count=27 conv=notrunc
dd if=a.out of=vdisk bs=512 seek=1  conv=notrunc
