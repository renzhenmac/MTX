#!/bin/bash 
sudo mount -o loop ./mtximage /mnt
sudo cp ./mtx /mnt/boot/mtx
sudo cp ./USER/u1 /mnt/bin
sudo cp ./USER/u2 /mnt/bin
sudo umount /mnt

