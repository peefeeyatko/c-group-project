# makefile for producing main.out

main.out: menu.c password.c encryption.c compression.c main.c
	gcc -Wall -Werror -ansi -o main.out menu.c password.c encryption.c compression.c main.c -lm