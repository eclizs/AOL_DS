#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "trie.h"

TrieNode *createTrieNode()
{
	TrieNode *newNode = (TrieNode*)calloc(1,sizeof(TrieNode));

	if(newNode == NULL)
	{
		printf("Memory allocation failed! Program will be terminated. Press enter to continue...\n");
		getchar();
		exit(EXIT_FAILURE);
	}
	
	return newNode;
}

bool insertTrieNode(TrieNode **root, char *signedText, char *desc)
{
	if(strlen(signedText) == 0 || strlen(desc) == 0) return false;
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
	
	if(temp->terminal == true)
	{
		free(temp->description);
		temp->description = strdup(desc);
		return false;
	}
	else
	{
		temp->terminal = true;
		temp->description = strdup(desc);
	}
	
	return temp->terminal;
}

static void printTrieNode_rec(TrieNode *node, unsigned char *buffer, int length, int *number)
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
			printTrieNode_rec(node->children[i], buffer, length+1, number);
		}
	}
}

void printTrieNode(TrieNode *root) //wrapper function
{
	if(root == NULL) return;
	
	unsigned char buffer[1000] = {'\0'};

	int number = 1;
	printTrieNode_rec(root, buffer, 0, &number);
}

TrieNode* findPrefixNode(TrieNode *root, char *signedPrefix)
{
	TrieNode *temp = root;
	int length = strlen(signedPrefix);
	unsigned char *prefix = (unsigned char*)signedPrefix;
	
	for(int i = 0; i < length; i++)
	{
		if(temp == NULL) return NULL;
		
		temp = temp->children[prefix[i]];
	}
	
	return temp;
}

void printPrefix(TrieNode *root, char *signedPrefix)
{
	if(root == NULL) return;

	TrieNode *prefixNode = findPrefixNode(root, signedPrefix);
	unsigned char *prefix = (unsigned char*)signedPrefix;
	
	if(prefixNode == NULL) return;
	
	unsigned char buffer[1000];
	memcpy(buffer, prefix, strlen(signedPrefix));
	buffer[strlen(signedPrefix)] = '\0';
	
	int number = 1;
	printTrieNode_rec(prefixNode, buffer, strlen(signedPrefix), &number);
}

SlangWord searchTrieNode(TrieNode *root, char *signedText)
{
	SlangWord result = {NULL, NULL};
	
	if(root == NULL) return result;

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

void destroyTrieNode(TrieNode **root)
{
	if(*root == NULL) return;

	for(int i = 0; i < NUM_CHAR; i++)
	{
		if((*root)->children[i] != NULL)
			destroyTrieNode(&(*root)->children[i]);
	}

	if((*root)->description) free((*root)->description);
	free(*root);
	*root = NULL;
}
