#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h> 
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

// struct for holding the node
struct Node {
    struct Node *left;
    char* word;
    int count;
    struct Node *right;
};

// creates a node, given a 'string' returns it
struct Node* createNode(char* string);

// recursive method for inserting a node, given a 'string'
// recurses on left and right nodes for insertion
struct Node* insertNode(struct Node* node, char* string);

// recursive method for finding a node, given a 'string'
// recurses on left and right nodes for finding
struct Node* findNode(struct Node* node, char* string);


