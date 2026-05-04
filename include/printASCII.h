#ifndef PRINTASCII_H
#define PRINTASCII_H

#ifdef _WIN32
	#include<windows.h>
	#define SLEEP(x) Sleep((x) * 1000)
	#define CLEAR_SCREEN() system("cls")
#else
	#include<unistd.h>
	#define SLEEP(x) usleep((x) * 1000000)
	#define CLEAR_SCREEN() system("clear")
#endif

void printASCII();

#endif // PRINTASCII_H