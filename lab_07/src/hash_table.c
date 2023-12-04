#include "hash_table.h"

struct HashNode* createNode(char key)
{
    struct HashNode* newNode = (struct HashNode*)malloc(sizeof(struct HashNode));
    if (newNode != NULL)
    {
        newNode->key = key;
        newNode->count = 1;
        newNode->next = NULL;
    }
    return newNode;
}

void initHashTable(struct HashTable* hashTable)
{
    for (int i = 0; i < TABLE_SIZE; ++i)
        hashTable->table[i] = NULL;
}

int hashFunction(char key)
{
    return abs((int)key % TABLE_SIZE);
}

void hash_insert(struct HashTable* hashTable, char key)
{
    int index = hashFunction(key);
    struct HashNode* newNode = createNode(key);

    if (hashTable->table[index] == NULL)
    {
        hashTable->table[index] = newNode;
    }
    else if (hashTable->table[index]->key == key)
    {
        hashTable->table[index]->count += 1;
        free(newNode);
    }
    else
    {
        newNode->next = hashTable->table[index];
        hashTable->table[index] = newNode;
    }
}

void displayHashTable(struct HashTable* hashTable)
{
    for (int i = 0; i < TABLE_SIZE; ++i)
    {
        struct HashNode* currentNode = hashTable->table[i];
        while (currentNode != NULL)
        {
            printf("Символ: %c, Количество: %d\n", currentNode->key, currentNode->count);
            currentNode = currentNode->next;
        }
    }
}

void displayWholeHashTable(struct HashTable* hashTable)
{
    printf(" i | char | cnt\n");
    for (int i = 0; i < TABLE_SIZE; ++i)
    {
        struct HashNode* currentNode = hashTable->table[i];
        if (!currentNode)
            printf("%3d|%6c|\n", i, '-');
        while (currentNode != NULL)
        {
            printf("%3d|%6c| %d\n", i, currentNode->key, currentNode->count);
            currentNode = currentNode->next;
        }
    }
}

int hash_search(struct HashTable* hashTable, char key)
{
    int index = hashFunction(key);
    struct HashNode* currentNode = hashTable->table[index];

    while (currentNode != NULL)
    {
        if (currentNode->key == key)
        {
            return currentNode->count;
        }
        currentNode = currentNode->next;
    }

    return 0;
}

void freeHashTable(struct HashTable* hashTable)
{
    for (int i = 0; i < TABLE_SIZE; ++i) {
        struct HashNode* currentNode = hashTable->table[i];
        while (currentNode != NULL) {
            struct HashNode* tempNode = currentNode;
            currentNode = currentNode->next;
            free(tempNode);
        }
    }
}
