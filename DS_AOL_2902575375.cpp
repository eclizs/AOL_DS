#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifdef _WIN32
#include<windows.h>
#else
#include<unistd.h>
#endif

#include "trie.h"

void printMenu();
void releaseWord();
void searchWord();
void viewSlangWithPrefix();
void viewSlang();
int containsSpace(char *str);
int countWords(char *str);

TrieNode *root = NULL;

int main()
{
	printMenu();
	
	return 0;
}

void printMenu()
{
	int input;
	do{
		system("cls");
		printf("1.	Release a new slang word\n"); 
		printf("2.	Search a slang word\n");
		printf("3.	View all slang words starting with a certain prefix word\n");
		printf("4.	View all slang words\n");
		printf("5.	Exit\n");
		printf("Enter Menu (1-5): ");
		
		while(scanf("%d", &input) != 1)
		{
			printf("\nInput must be an Integer!\n");
			getchar();
			sleep(0.5);
			break;
		}
		
		switch(input)
		{
			case 1:
				releaseWord();
				break;
			case 2:
//				searchWord();
				break;
			case 3:
//				viewSlangWithPrefix();
				break;
			case 4:
//				viewSlang();
				break;
			case 5:
				printf("Thank you... Have a nice day :)\n");
				sleep(1.5);
				return;
			default:
				break;
		}
		input = 0; //reset input to prevent infinite loop when user enters non-integer value
	} while(input != 5);
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
		desc[strlen(desc) - 1] = '\0';
		printf("wordCount: %d\n", countWords(desc));
		sleep(1);
	} while(countWords(desc) <= 2);

	if(!insertTrieNode(&root, input, desc))
	{
		printf("Failed to create a new slang!\nPress enter to continue...");
		getchar();
		return;
	}
	printTrieNode(root);
	sleep(1.5);
}


