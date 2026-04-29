CC = gcc
CFLAGS = -Wall -g
OBJS = main.o trie.o
BIN = main
TARGET = main

all: $(BIN)

main: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o main

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -r main *.o