#include "util.h"
#include "trie.h"
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

int main()
{
    // =============================================
    //          TESTS FOR HELPER FUNCTIONS 
    // =============================================
    
    // containsSpace()
    assert(containsSpace("") == 0);
    assert(containsSpace("ab") == 0);
    assert(containsSpace("a b c d") == 3);

    // countWords()
    assert(countWords("") == 0);
    assert(countWords("ab") == 1);
    assert(countWords("a b c d") == 4);

    // =============================================
    //        TESTS FOR TRIE DATA STRUCTURE
    // =============================================

    // createTrieNode()
    TrieNode* root = NULL;
    assert((root = createTrieNode()) != NULL);
    
    // insertTrieNode()
    assert(insertTrieNode(&root, "", "") == false);
    assert(insertTrieNode(&root, "ab", "") == false);
    assert(insertTrieNode(&root, "", "ab") == false); 
    assert(insertTrieNode(&root, "ab", "ab") == true);
    assert(insertTrieNode(&root, "a b", "ab") == true);
    assert(insertTrieNode(&root, "ab", "a b") == false); // inserting the same string will fail

    // printing functions
    
    insertTrieNode(&root, "KIT", "dwasdw");
	insertTrieNode(&root, "KIND", "dwasdw");
	insertTrieNode(&root, "KIN", "dwasdw");
	insertTrieNode(&root, "KANKER", "dwasdw");
	insertTrieNode(&root, "KLANKER", "dwasdw");
	insertTrieNode(&root, "KORN", "dwasdw");
	printf("print all words:\n"); printTrieNode(root); printf("\n");

    printf("print all words with prefix \"K\":\n");printPrefix(root, "K"); printf("\n");

    // findPrefixNode()

    assert(findPrefixNode(root, "K") != NULL);
    assert(findPrefixNode(root, "a") != NULL);
    assert(findPrefixNode(root, "v") == NULL);

    // searchTrieNode()
    SlangWord temp = searchTrieNode(root, "KIT");

    assert(temp.word != NULL && temp.description != NULL);
    temp = searchTrieNode(root, "KORN");
    assert(temp.word != NULL && temp.description != NULL);
    temp = searchTrieNode(root, "ab");
    assert(temp.word != NULL && temp.description != NULL);
    temp = searchTrieNode(root, "invalid");
    assert(temp.word == NULL && temp.description == NULL);

    // destroyTrieNode()
    printf("destroying trie... should print \"There is no slang word yet in the dictionary.\"\n");
    destroyTrieNode(&root);

    printTrieNode(root);

    printf("all tests passed\n");
}