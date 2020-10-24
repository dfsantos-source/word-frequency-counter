#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "node.h"
#include "hashtable.h"

// creates a node, given a 'string' returns it
struct Node *createNode(char *string)
{
    char *newString = (char *)malloc(sizeof(char));
    strcpy(newString, string);
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->count = 1;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->word = newString;
    return newNode;
}

// recursive method for inserting a node, given a 'string'
// recurses on left and right nodes for insertion
struct Node *insertNode(struct Node *node, char *string)
{
    if (node == NULL)
    {
        char *newString = (char *)malloc(sizeof(char));
        strcpy(newString, string);
        struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
        newNode->count = 1;
        newNode->left = NULL;
        newNode->right = NULL;
        newNode->word = newString;
        return newNode;
    }
    if (strcmp(string, node->word) < 0)
    {
        node->left = insertNode(node->left, string);
    }
    else if (strcmp(string, node->word) > 0)
    {
        node->right = insertNode(node->right, string);
    }
    return node;
}

// recursive method for finding a node, given a 'string'
// recurses on left and right nodes for finding
struct Node *findNode(struct Node *node, char *string)
{
    if (node == NULL)
    {
        return NULL;
    }
    if (strcmp(string, node->word) == 0)
    {
        return node;
    }
    if (strcmp(string, node->word) < 0)
    {
        return findNode(node->left, string);
    }
    return findNode(node->right, string);
}
