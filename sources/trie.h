#ifndef TRIE_H
#define TRIE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
};

struct TrieNode* createTrieNode() {
    struct TrieNode* newNode = (struct TrieNode*)malloc(sizeof(struct TrieNode));
    newNode->isEndOfWord = false;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

int getCharIndex(char c) {
    return tolower(c) - 'a';
}

void insertTrie(struct TrieNode* root, const char* key) {
    struct TrieNode* curr = root;
    int length = strlen(key);
    
    for (int i = 0; i < length; i++) {
        if (key[i] == ' ') continue; 
        
        int index = getCharIndex(key[i]);
        if (index < 0 || index >= ALPHABET_SIZE) continue; // validasi karakter alfabet

        if (curr->children[index] == NULL) {
            curr->children[index] = createTrieNode();
        }
        curr = curr->children[index];
    }
    curr->isEndOfWord = true;
}

void suggestRec(struct TrieNode* root, char prefix[], int level, bool *hasSuggestion) {
    if (root == NULL) return;

    if (root->isEndOfWord) {
        prefix[level] = '\0';
        printf("- %s\n", prefix);
        *hasSuggestion = true;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i] != NULL) {
            prefix[level] = 'a' + i;
            suggestRec(root->children[i], prefix, level + 1, hasSuggestion);
        }
    }
}

int printAutoSuggestions(struct TrieNode* root, const char* query) {
    struct TrieNode* curr = root;
    int length = strlen(query);
    
    char prefixBuffer[100];
    int level = 0;

    for (int i = 0; i < length; i++) {
        if (query[i] == ' ') continue;
        
        int index = getCharIndex(query[i]);
        if (index < 0 || index >= ALPHABET_SIZE || curr->children[index] == NULL) {
            return 0; // tidak ada menu yang cocok dengan awalan tersebut
        }
        
        prefixBuffer[level++] = tolower(query[i]);
        curr = curr->children[index];
    }

    bool hasSuggestion = false;
    suggestRec(curr, prefixBuffer, level, &hasSuggestion);
    
    return hasSuggestion ? 1 : 0;
}

#endif