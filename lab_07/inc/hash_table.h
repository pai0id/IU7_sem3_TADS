#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TABLE_SIZE 128

struct HashNode
{
    char key;
    int count;
    struct HashNode* next;
};

struct HashTable
{
    struct HashNode* table[TABLE_SIZE];
};

struct HashNode* createNode(char key);

void initHashTable(struct HashTable* hashTable);

int hashFunction(char key);

void hash_insert(struct HashTable* hashTable, char key);

void displayHashTable(struct HashTable* hashTable);

void displayWholeHashTable(struct HashTable* hashTable);

int hash_search(struct HashTable* hashTable, char key);

void freeHashTable(struct HashTable* hashTable);

#endif
