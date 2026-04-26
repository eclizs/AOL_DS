#ifndef TRIE_H
#define TRIE_H

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
void printTrieNode_rec(TrieNode *node, unsigned char *prefix, int length);
void printTrieNode(TrieNode *root);  //wrapper function
TrieNode *findPrefixNode(TrieNode *root, unsigned char *prefix);
void printPrefix_rec(TrieNode *node, unsigned char *buffer, int length, int *number);
void printPrefix(TrieNode *root, char *signedPrefix); //wrapper function
SlangWord searchTrieNode(TrieNode *root, char *signedText);
bool node_has_children(TrieNode *node);

#endif
