#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h> 
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

struct HashTableItem {
    struct Node* node;
};

/*
- takes in a string, returns a hash code 
- ie: "apple" -> 0
*/
int hashCode(char* string);



