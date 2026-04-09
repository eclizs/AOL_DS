CC = g++
CFLAGS = -Wall -g
TARGET = DS_AOL_2902575375.exe

all: $(TARGET)

$(TARGET): DS_AOL_2902575375.cpp trie.cpp trie.h
	$(CC) $(CFLAGS) -o $(TARGET) DS_AOL_2902575375.cpp trie.cpp

clean:
	del $(TARGET)

.PHONY: all clean