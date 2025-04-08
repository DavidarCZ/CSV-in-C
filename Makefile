# Projekt: CSV databáze
# Autor:   David Sklenář
# Datum:   3.1.2023

CC=gcc
CFLAGS= -std=c99 -pedantic -Wall -Wextra -g -fsanitize=address
NAME = program

$(NAME): main.o functions.o  #slinkovani
	$(CC) $(CFLAGS) main.o functions.o -o $(NAME)

main.o: main.c functions.h #preklad hlavniho
	$(CC) $(CFLAGS) -c main.c

functions.o: functions.c functions.h #preklad funkci
	$(CC) $(CFLAGS) -c functions.c