#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#ifdef _WIN32
	#include<windows.h>
	#define SLEEP(x) Sleep(x * 1000)
	#define CLEAR_SCREEN() system("cls")
#else
	#include<unistd.h>
	#define SLEEP(x) usleep(x * 1000000)
	#define CLEAR_SCREEN() system("clear")
#endif

#include "trie.h"

//TODO--idk tbh

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
		CLEAR_SCREEN();
		printf("1.	Release a new slang word\n"); 
		printf("2.	Search a slang word\n");
		printf("3.	View all slang words starting with a certain prefix word\n");
		printf("4.	View all slang words\n");
		printf("5.	Exit\n");
		printf("Enter Menu (1-5): ");
		
		while(scanf("%d", &input) != 1)
		{
			CLEAR_SCREEN();
			printf("Input must be an Integer!\n");
			SLEEP(0.5);
			break;
		}
		getchar(); //consume the newline character left by scanf
		
		switch(input)
		{
			case 1:
				releaseWord();
				break;
			case 2:
				searchWord();
				break;
			case 3:
//				viewSlangWithPrefix();
				break;
			case 4:
				viewSlang();
				break;
			case 5:
				printf("Thank you... Have a nice day :)\n");
				SLEEP(1.5);
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
		desc[strlen(desc) - 1] = '\0'; //remove newline character from the end of the string
	} while(countWords(desc) <= 2);

	// if(!insertTrieNode(&root, input, desc))
	// {
	// 	printf("Failed to create a new slang!\nPress enter to continue...");
	// 	getchar();
	// 	return;
	// }
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

void viewSlang()
{
	if(root == NULL)
	{
		printf("There is no slang word yet in the dictionary.\nPress enter to continue...\n");
		getchar();
		return;
	}
	
	printf("List of all slang words in the dictionary:\n");
	printTrieNode(root);
	printf("Press enter to continue...");
	getchar();
}


