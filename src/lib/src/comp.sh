#!/bin/bash
#Literally no clue kas yra make file
#Sketchy sudas for the win
#usage ./comp.sh main
gcc -o CrippleMD.o -g -c CrippleMD.c
gcc -o main.out -I . -Wall -Wextra -g main.c CrippleMD.o
