#ifndef UTIL_H
#define UTIL_H

#include "trie.h"

#ifdef _WIN32
	#include <windows.h>
	#define SLEEP(x) Sleep((x) * 1000)
	#define CLEAR_SCREEN() system("cls")
#else
	#include <unistd.h>
	#define SLEEP(x) usleep((x) * 1000000)
	#define CLEAR_SCREEN() system("clear")
#endif

void printASCII(void);
void printMenu(void);
int containsSpace(char *str);
int countWords(char *str);
void releaseWord(void);
void searchWord(void);
void viewSlangWithPrefix(void);
void viewSlang(void);

#endif
