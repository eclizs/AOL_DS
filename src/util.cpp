#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include "trie.h"

static TrieNode *root = NULL;

static void (*functions[4])(void) = {releaseWord, searchWord, viewSlangWithPrefix, viewSlang};

void printASCII(void)
{
    FILE *fp = fopen("ascii.txt", "r");
    if(fp == NULL)
    {
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

    while(fgets(art, 1000, fp) != NULL)
        printf("%s", art);

    free(art);
    fclose(fp);
}

void printMenu(void)
{
    int input;

    do
    {
        input = 0;
        CLEAR_SCREEN();
        printf("1. Release a new slang word\n");
        printf("2. Search a slang word\n");
        printf("3. View all slang words starting with a certain prefix word\n");
        printf("4. View all slang words\n");
        printf("5. Exit\n");
        printf("Enter Menu (1-5): ");

        if(scanf("%d", &input) != 1)
        {
            while(getchar() != '\n');

            printf("Input must be an Integer!\npress enter to continue...");
            getchar();
        }
        else
        {
            getchar();
        }

        if(input > 0 && input < 5)
        {
            functions[input - 1]();
        }
    } while(input != 5);

    CLEAR_SCREEN();
    destroyTrieNode(&root);
    printASCII();
    SLEEP(1.5);
}

int countSpace(char *str)
{
    int amountOfSpaces = 0;

    int i = 0;
    int length = strlen(str);
    while(str[i] == ' ') i++;
    while(str[length - 1] == ' ') length--;

    for(; str[i] != '\0' && i < length; i++)
    {
        if(str[i] == ' ')
        {
            amountOfSpaces++;
            while(str[i] == ' ')
            {
                i++;
            }
        }
    }

    return amountOfSpaces;
}

int countWords(char *str)
{
    if(strlen(str) == 0) return 0;
    return countSpace(str) + 1;
}

void releaseWord(void)
{
    CLEAR_SCREEN();
    char input[1000];

    do
    {
        printf("Input a new slang word [Must be more than 1 characters and contains no space]: ");
        scanf(" %[^\n]", input);
        getchar();
    } while(strlen(input) < 2 || countSpace(input) > 0);

    char desc[1000];

    do
    {
        printf("Input a new slang word description [Must be more than 2 words]:  ");
        fgets(desc, sizeof(desc), stdin);
        desc[strlen(desc) - 1] = '\0';
    } while(countWords(desc) <= 2);

    if(!insertTrieNode(&root, input, desc))
    {
        printf("Slang word %s's description has been updated!\nPress enter to continue...\n", input);
        getchar();
    }
    else
    {
        printf("Slang word \"%s\" has been added to the dictionary!\nPress enter to continue...\n", input);
        getchar();
    }
}

void searchWord(void)
{
    CLEAR_SCREEN();
    char input[1000];

    if(root == NULL)
    {
        printf("There is no slang word in the dictionary.\nPress enter to continue...");
        getchar();
        return;
    }

    do
    {
        printf("Input a slang word to search [Must be more than 1 characters and contains no space]: ");
        scanf(" %[^\n]", input);
        getchar();
    } while(strlen(input) < 2 || countSpace(input) > 0);

    SlangWord result = searchTrieNode(root, input);

    if(result.word != NULL)
    {
        printf("Slang word: %s\nDescription: %s\nPress enter to continue...", result.word, result.description);
        getchar();
        free(result.word);
        free(result.description);
        return;
    }
    else
    {
        printf("There is no slang word \"%s\" in the dictionary.\nPress enter to continue...", input);
        getchar();
        return;
    }
}

void viewSlangWithPrefix(void)
{
    CLEAR_SCREEN();
    char input[1000];

    if(root == NULL)
    {
        printf("There is no slang word in the dictionary.\nPress enter to continue...");
        getchar();
        return;
    }

    do
    {
        printf("Input a prefix to be searched: ");
        scanf(" %[^\n]", input);
        getchar();

        if(countSpace(input) > 0)
        {
            printf("Prefix must not contain space!\n");
            SLEEP(0.5);
        }

        if(strlen(input) == 0)
        {
            printf("Prefix must be more than 0 characters!\n");
            SLEEP(0.5);
        }
    } while(countSpace(input) > 0 || strlen(input) == 0);

    if(findPrefixNode(root, input))
    {
        printf("Slang words starting with \"%s\":\n", input);
        printf("\n");
        printPrefix(root, input);
        printf("\n");
        printf("Press enter to continue...");
        getchar();
    }
    else
    {
        printf("No slang words found starting with \"%s\".\n", input);
        printf("Press enter to continue...");
        getchar();
    }
}

void viewSlang(void)
{
    CLEAR_SCREEN();
    if(root == NULL)
    {
        printf("There is no slang word yet in the dictionary.\nPress enter to continue...\n");
        getchar();
        return;
    }

    printf("List of all slang words in the dictionary:\n");
    printf("\n");
    printTrieNode(root);
    printf("\n");
    printf("Press enter to continue...");
    getchar();
}
