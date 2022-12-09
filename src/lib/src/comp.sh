#!/bin/bash
#Literally no clue kas yra make file
#Sketchy sudas for the win
#usage ./comp.sh main
gcc -o CrippleMD.o -c CrippleMD.c
gcc -o $1 -I . -Wall -Wextra -g main.c CrippleMD.o
