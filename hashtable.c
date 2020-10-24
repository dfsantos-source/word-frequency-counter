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

/*
- takes in a string, returns a hash code 
- ie: "apple" -> 0
*/
int hashCode(char* string) {
    char c = string[0];
    for (int i=97; i<123; i++) {
        if (i == c) {
            return i-97;
        }
    }
    return 0;
}