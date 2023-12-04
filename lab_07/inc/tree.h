#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char data;
    int count;
    int height;
    struct Node* left;
    struct Node* right;
};

struct Trunk {
    struct Trunk *prev;
    char* str;
};

int max(int a, int b);

int height(struct Node* node);

int get_balance(struct Node* node);

void show_trunks(struct Trunk *p);

void print_tree(struct Node* root, struct Trunk *prev, int isLeft);

struct Node* create_node(char value);

struct Node* right_rotate(struct Node* y);

struct Node* left_rotate(struct Node* x);

struct Node* insert(struct Node* root, char key);

struct Node *balance_tree(struct Node *root);

void in_order_traversal(struct Node* root);

struct Node* search(struct Node* root, char key);

struct Node* find_min(struct Node* root);

struct Node* del_node(struct Node* root, char key);

void free_tree(struct Node* root);

struct Node* del_rep_nodes(struct Node* root);

#endif
