#include <stdio.h>
#include <stdlib.h>
#include "printASCII.h"

void printASCII()
{
    FILE *fp = fopen("ascii.txt", "r");
    if(fp == NULL)    {
        printf("Error opening ascii.txt file!\n");
        return;
    }

    char *art = (char*)malloc(1000 * sizeof(char));
    if(art == NULL)
    {
        printf("Memory allocation failed!\n");
        fclose(fp);
        return;
    }
    while(fgets(art, sizeof(art), fp) != NULL)
    {
        printf("%s", art);
        SLEEP(1e-12);
    }

	printf("Read Lord of The Mysteries if you haven't already!\n");

    free(art);
    fclose(fp);
}
