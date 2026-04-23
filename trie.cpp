#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "trie.h"

TrieNode *createTrieNode()
{
	TrieNode *newNode = (TrieNode*)calloc(1,sizeof(TrieNode));
	
	return newNode;
}

bool insertTrieNode(TrieNode **root, char *signedText, char *desc)
{
	if(*root == NULL) *root = createTrieNode();
	
	unsigned char *text = (unsigned char*)signedText;
	
	TrieNode *temp = *root;
	int length = strlen(signedText);
	
	for(int i = 0 ; i < length; i++)
	{
		if(temp->children[text[i]] == NULL)
			temp->children[text[i]] = createTrieNode();
			
		temp = temp->children[text[i]];
	}
	
	if(temp->terminal == true) return false;
	else
	{
		temp->terminal = true;
		temp->description = strdup(desc);
	}
	
	return temp->terminal;
}

void printTrieNode_rec(TrieNode *node, unsigned char *prefix, int length, int *number)
{
	unsigned char newPrefix[length+2]; //1 for new char, 1 for null terminator
	memcpy(newPrefix, prefix, length);
	newPrefix[length + 1] = '\0';
	
	if(node->terminal)
	{
		printf("%d. %s\n", *number, newPrefix);
		*number += 1;
	}
	
	for(int i = 0; i < NUM_CHAR; i++)
	{
		if(node->children[i] != NULL)
		{
			newPrefix[length] = i;
			printTrieNode_rec(node->children[i],newPrefix, length+1, number);
		}
	}
}

void printTrieNode(TrieNode *root) //wrapper function
{
	if(root == NULL)
	{
		printf("There is no slang word yet in the dictionary.\nPress enter to continue...\n");
		getchar();
		return;
	}
	int number = 1;
	printTrieNode_rec(root, NULL, 0, &number);
}

void printPrefix_rec(TrieNode *node, unsigned char *buffer, int length, int *number)
{
	if(node == NULL) return;
	
	if(node->terminal)
	{
		printf("%d. %s\n", *number, buffer);
		*number += 1;
	}
	
	for(int i = 0; i < NUM_CHAR; i++)
	{
		if(node->children[i] != NULL)
		{
			buffer[length] = i;
			buffer[length+1] = '\0';
			
			printPrefix_rec(node->children[i], buffer, length+1, number);
		}
	}
}

TrieNode* findPrefixNode(TrieNode *root, unsigned char *prefix)
{
	TrieNode *temp = root;
	int length = strlen((char*)prefix);
	
	for(int i = 0; i < length; i++)
	{
		if(temp == NULL) return NULL;
		
		temp = temp->children[prefix[i]];
	}
	
	return temp;
}

void printPrefix(TrieNode *root, char *signedPrefix)
{
	unsigned char *prefix = (unsigned char*)signedPrefix;
	TrieNode *prefixNode = findPrefixNode(root, prefix);
	int number = 1;
	
	if(prefixNode == NULL)
	{
		printf("There is no prefix \"%s\" in the dictionary.\nPress enter to continue...", prefix);
		getchar();
		return;
	}
	
	unsigned char buffer[1000];
	strcpy((char*)buffer,(char*)prefix);
	
	printPrefix_rec(prefixNode, buffer, strlen((char*)prefix), &number);
}

SlangWord searchTrieNode(TrieNode *root, char *signedText)
{
	if(root == NULL) return (SlangWord){NULL, NULL};
	SlangWord result = {NULL, NULL};
	unsigned char *text = (unsigned char*) signedText;
	int length = strlen(signedText);
	TrieNode *temp = root;
	
	for(int i = 0; i < length; i++)
	{
		if(temp->children[text[i]] == NULL) return result;
		
		temp = temp->children[text[i]];
	}
	
	if(temp->terminal)
	{
		result.word = strdup(signedText);
		result.description = strdup(temp->description);
	}
	
	return result;
}

bool node_has_children(TrieNode *node)
{
	if(node == NULL) return false;
	
	for(int i = 0; i < NUM_CHAR; i++)
	{
		if(node->children[i] != NULL) return true;
	}
	
	return false;
}

TrieNode* deleteStr_rec(TrieNode *node, unsigned char *text, bool *deleted)
{
	if(node == NULL) return node;
	
	if(*text == '\0')
	{
		if(node->terminal == true)
		{
			node->terminal = false;
			*deleted = true;
			
			if(!node_has_children(node))
			{
				free(node);
				node = NULL;
			}
		}
		return node;
	}
	node->children[text[0]] = 
		deleteStr_rec(node->children[text[0]], text+1, deleted); //text+1 is pointer arithmetic->moving the pointer to the second character
	
	if(*deleted && !node->terminal && !node_has_children(node))
	{
		free(node);
		node = NULL;
	}
	return node;
}

bool deleteStr(TrieNode **root, char *signedText)
{
	unsigned char *text = (unsigned char*)signedText;
	bool result = false;
	
	if(*root == NULL) return false;
	
	*root = deleteStr_rec(*root, text, &result);
	return result;
}

// int main()
// {
// 	TrieNode *root = NULL;
	
// 	// insertTrieNode(&root, "KIT", "dwasdw");
// 	// insertTrieNode(&root, "KIND", "dwasdw");
// 	// insertTrieNode(&root, "KIN", "dwasdw");
// 	// insertTrieNode(&root, "KANKER", "dwasdw");
// 	// insertTrieNode(&root, "KLANKER", "dwasdw");
// 	// insertTrieNode(&root, "KORN", "dwasdw");
// 	// printTrieNode(root);
	
// 	// printf("search for JASON: %d\n", searchTrieNode(root, "JASON"));
// 	// printf("search for JACKSON: %d\n", searchTrieNode(root, "JACKSON"));
// 	// printf("search for JACSON: %d\n", searchTrieNode(root, "JACSON"));
	
// 	// deleteStr(&root, "KIN");
// 	// deleteStr(&root, "CA");
	
// 	// printPrefix(root, "K");

// 	return 0;
// }
