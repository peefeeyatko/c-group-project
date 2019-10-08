# makefile for producing main.out

CC = gcc
FLAGS = -Wall -Werror -ansi

main.out: menu.c password.c encryption.c compression.c main.c
	$(CC) $(FLAGS) -o main.out menu.c password.c encryption.c compression.c main.c -lm