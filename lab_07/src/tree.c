#include "tree.h"

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(struct Node* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int get_balance(struct Node* node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

void show_trunks(struct Trunk *p) {
    if (p == NULL) {
        return;
    }

    show_trunks(p->prev);
    printf("%s", p->str);
}

void print_tree(struct Node* root, struct Trunk *prev, int isLeft) {
    if (root == NULL) {
        return;
    }

    char* prev_str = "    ";
    struct Trunk *trunk = (struct Trunk*)malloc(sizeof(struct Trunk));
    trunk->prev = prev;
    trunk->str = prev_str;

    print_tree(root->right, trunk, 1);

    if (!prev) {
        trunk->str = "———";
    } else if (isLeft) {
        trunk->str = ".———";
        prev_str = "   |";
    } else {
        trunk->str = "`———";
        prev->str = prev_str;
    }

    show_trunks(trunk);
    if (root->count > 1)
        printf(" \033[0;31m%c\033[0;37m\n", root->data);
    else
        printf(" %c\n", root->data);

    if (prev) {
        prev->str = prev_str;
    }
    trunk->str = "   |";

    print_tree(root->left, trunk, 0);
}

struct Node* create_node(char value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->count = 1;
    newNode->height = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct Node* right_rotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

struct Node* left_rotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

struct Node* insert(struct Node* root, char key) {
    if (root == NULL) {
        return create_node(key);
    }

    if (key < root->data) {
        root->left = insert(root->left, key);
    } else if (key > root->data) {
        root->right = insert(root->right, key);
    } else {
        root->count++;
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));

    return root;
}

struct Node* insert_bal(struct Node* root, char key)
{
    if (root == NULL) {
        return create_node(key);
    }

    if (key < root->data) {
        root->left = insert_bal(root->left, key);
    } else if (key > root->data) {
        root->right = insert_bal(root->right, key);
    } else {
        root->count++;
        return root;
    }

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = get_balance(root);

    if (balance > 1 && key < root->left->data) {
        return right_rotate(root);
    }

    if (balance < -1 && key > root->right->data) {
        return left_rotate(root);
    }

    if (balance > 1 && key > root->left->data) {
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    if (balance < -1 && key < root->right->data) {
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

void balance_insertiions(struct Node *root, struct Node **new)
{
    if (root != NULL)
    {
        balance_insertiions(root->right, new);
        *new = insert_bal(*new, root->data);
        balance_insertiions(root->left, new);
    }
}

struct Node *balance_tree(struct Node *root)
{
    // if (root == NULL)
    //     return NULL;

    // root->left = balance_tree(root->left);
    // root->right = balance_tree(root->right);

    // int balance = get_balance(root);

    // while (balance > 1 || balance < -1)
    // {
    //     if (balance > 1)
    //         root = right_rotate(root);
    //     else if (balance < -1)
    //         root = left_rotate(root);
        
    //     printf("%d", balance);
    //     balance = get_balance(root);
    // }

    // return root;
    struct Node *new_tree = NULL;
    balance_insertiions(root, &new_tree);
    free_tree(root);
    return new_tree;
}

void in_order_traversal(struct Node* root) {
    if (root != NULL) {
        in_order_traversal(root->left);
        if (root->count > 1)
            printf(" \033[0;31m%c\033[0;37m", root->data);
        else
            printf(" %c", root->data);
        in_order_traversal(root->right);
    }
}

struct Node* search(struct Node* root, char key) {
    if (root == NULL || root->data == key) {
        return root;
    }

    if (key < root->data) {
        return search(root->left, key);
    }

    return search(root->right, key);
}

struct Node* find_min(struct Node* root) {
    while (root != NULL && root->left != NULL) {
        root = root->left;
    }
    return root;
}

struct Node* del_node(struct Node* root, char key) {
    if (root == NULL) {
        return root;
    }

    if (key < root->data) {
        root->left = del_node(root->left, key);
    } else if (key > root->data) {
        root->right = del_node(root->right, key);
    } else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        struct Node* temp = find_min(root->right);
        root->data = temp->data;
        root->count = temp->count;
        root->right = del_node(root->right, temp->data);
    }

    return root;
}

void free_tree(struct Node* root) {
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

struct Node* del_rep_nodes(struct Node* root) {
    if (root == NULL) {
        return NULL;
    }

    root->left = del_rep_nodes(root->left);
    root->right = del_rep_nodes(root->right);

    if (root->count > 1) {
        return del_node(root, root->data);
    }

    return root;
}
