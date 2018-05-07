#!/bin/bash 
sudo mount -o loop ./mtximage /mnt
sudo cp ./mtx /mnt/boot/mtx
sudo cp ./USER/u2 /mnt/bin/u1
sudo umount /mnt

