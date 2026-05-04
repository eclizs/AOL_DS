#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifdef _WIN32
	#include<windows.h>
	#define SLEEP(x) Sleep((x) * 1000)
	#define CLEAR_SCREEN() system("cls")
#else
	#include<unistd.h>
	#define SLEEP(x) usleep((x) * 1000000)
	#define CLEAR_SCREEN() system("clear")
#endif

#include "trie.h"
#include "printASCII.h"

void printMenu();
void releaseWord();
void searchWord();
void viewSlangWithPrefix();
void viewSlang();
int containsSpace(char *str);
int countWords(char *str);
void printASCII();

TrieNode *root = NULL;

void (*functions[4])() = {releaseWord, searchWord, viewSlangWithPrefix, viewSlang};

int main()
{
	printMenu();
	
	return 0;
}

void printMenu()
{
	int input;
	do{
		input = 0; //reset input to prevent infinite loop when user enters non-integer value
		CLEAR_SCREEN();
		printf("1.	Release a new slang word\n"); 
		printf("2.	Search a slang word\n");
		printf("3.	View all slang words starting with a certain prefix word\n");
		printf("4.	View all slang words\n");
		printf("5.	Exit\n");
		printf("Enter Menu (1-5): ");
		
		if(scanf("%d", &input) != 1)
		{
			// Flush everything up to and including the next newline
			while(getchar() != '\n');

			CLEAR_SCREEN();
			printf("Input must be an Integer!\n");
			SLEEP(0.5);
		}
		else getchar(); // consume the newline left by a successful scanf
		
		if(input > 0 && input < 5) functions[input - 1]();
	} while(input != 5);

	CLEAR_SCREEN();
	printASCII();
	SLEEP(3);
	return;
}

int containsSpace(char *str) {
	int amntOfSpaces = 0;
   for(int i = 0; str[i] != '\0'; i++)
	{
      if(str[i] == ' ')
		{
			amntOfSpaces++;
			while(str[i] == ' ') i++;
		}
   }
   return amntOfSpaces;
}

int countWords(char *str)
{
	int count = 0;
	int len = strlen(str);
    char lastC;

    if(len > 0) lastC = str[0];
    for(int i = 0; i <= len; i++)
    {
        if((str[i] == ' ' || str[i] == '\0') && lastC != ' ') count++;
        lastC = str[i];
    }
    return count;
}

void releaseWord()
{
	CLEAR_SCREEN();
	char input[1000];
	
	do{
		printf("Input a new slang word [Must be more than 1 characters and contains no space]: ");
		scanf(" %[^\n]", input);
		getchar();
	} while(strlen(input) < 2 || containsSpace(input));
	
	char desc[1000];
	
	do{
		printf("Input a new slang word description [Must be more than 2 words]:  ");
		fgets(desc, sizeof(desc), stdin);
		desc[strlen(desc) - 1] = '\0'; //remove newline character from the end of the string
	} while(countWords(desc) <= 2);

	if(searchTrieNode(root, input).word != NULL)
	{
		printf("Slang word \"%s\"'s description has been updated!\nPress enter to continue...\n", input);
		getchar();
	}
	else
	{
		printf("Slang word \"%s\" has been added to the dictionary!\nPress enter to continue...\n", input);
		getchar();
	}
	insertTrieNode(&root, input, desc);
}

void searchWord()
{
	CLEAR_SCREEN();
	char input[1000];

	if(root == NULL)
	{
		printf("There is no slang word in the dictionary.\nPress enter to continue...");
		getchar();
		return;
	}

	do{
		printf("Input a slang word to search [Must be more than 1 characters and contains no space]: ");
		scanf(" %[^\n]", input);
		getchar();
	} while(strlen(input) < 2 || containsSpace(input));
	
	SlangWord result = searchTrieNode(root, input);
	if(result.word != NULL)
	{
		printf("Slang word: %s\nDescription: %s\nPress enter to continue...", result.word, result.description);
		getchar();
		return;
	}
	else
	{
		printf("There is no slang word \"%s\" in the dictionary.\nPress enter to continue...", input);
		getchar();
		return;
	}
}

void viewSlangWithPrefix()
{
	CLEAR_SCREEN();
	char input[1000];
	
	if(root == NULL)
	{
		printf("There is no slang word in the dictionary.\nPress enter to continue...");
		getchar();
		return;
	}
	
	do{
		printf("Input a prefix to be searched: ");
		scanf(" %[^\n]", input);
		getchar();
		if(containsSpace(input))
		{
			printf("Prefix must not contain space!\n");
			SLEEP(0.5);
		}
		if(strlen(input) == 0)
		{
			printf("Prefix must be more than 0 characters!\n");
			SLEEP(0.5);
		}
	} while(containsSpace(input) || strlen(input) == 0);
	
	if(findPrefixNode(root, (unsigned char*)input))
	{
		printf("Slang words starting with \"%s\":\n", input);
		printf("\n"); printPrefix(root, input); printf("\n");
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

void viewSlang()
{
	CLEAR_SCREEN();
	if(root == NULL)
	{
		printf("There is no slang word yet in the dictionary.\nPress enter to continue...\n");
		getchar();
		return;
	}
	
	printf("List of all slang words in the dictionary:\n");
	printf("\n"); printTrieNode(root); printf("\n");
	printf("Press enter to continue...");
	getchar();
}


