CC=gcc
CFLAGS= -O2 -Wall -Wextra
FILES= main.c c.c piles.c cards.c decks.c
FILENAME = paciencia.exe

C_MAIN = $(wildcard ./main.c)
C_SOURCE = $(wildcard ./src/*.c)
H_SOURCE = $(wildcard ./src/*.h)

paciencia.exe: main.c 
	$(CC) $(CFLAGS) $(C_MAIN) $(C_SOURCE) -o $(FILENAME) 

