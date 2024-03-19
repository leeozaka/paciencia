CC=gcc
CVERSION= -std=c17
CFLAGS= -O3 -Wall -Wextra -pedantic
FILES= main.c c.c piles.c cards.c decks.c
FILENAME = paciencia.exe

C_MAIN = $(wildcard ./main.c)
C_SOURCE = $(wildcard ./src/*.c)
H_SOURCE = $(wildcard ./src/*.h)

paciencia.exe: main.c 
	$(CC) $(CVERSION) $(CFLAGS) $(C_MAIN) $(C_SOURCE) -o $(FILENAME) 

