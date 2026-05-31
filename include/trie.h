#ifndef TRIE_H
#define TRIE_H

#include<stdbool.h>

#define NUM_CHAR 256

typedef struct TrieNode{
	struct TrieNode *children[NUM_CHAR];
	bool terminal;
	char *description;
} TrieNode;

typedef struct SlangWord{
	char *word;
	char *description;
} SlangWord;

TrieNode *createTrieNode();
bool insertTrieNode(TrieNode **root, char *signedText, char *desc);
void printTrieNode(TrieNode *root);
TrieNode *findPrefixNode(TrieNode *root, unsigned char *prefix);
void printPrefix(TrieNode *root, char *signedPrefix);
SlangWord searchTrieNode(TrieNode *root, char *signedText);
void destroyTrieNode(TrieNode **root);

#endif
