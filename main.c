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

extern char **environ;

// converts an int to digit form, ie: 2356 -> 4
int findDigit(int x) { 
    int count = 0; 
    while (x != 0) { 
        x = x/10; 
        ++count; 
    } 
    return count; 
} 

// returns largest count from a root node
int digitLargest(struct Node* root, int max) {
    int i;
    if (root == NULL) {
      return max;
    }
    if ((i = digitLargest(root->left, max)) > max) {
        max = i;
    } 
    if ((root->count) > max) {
        max = root->count;
    }
    if ((i = digitLargest(root->right, max)) > max) {
        max = i;
    } 
    return max;
}      

// returns string length in int form
int stringLength(char* string) {
    int x = strlen(string);
    return x;
}

// returns largest string length from root node
int stringLargest(struct Node* root, int max) {
    int i;
    if (root == NULL) {
      return max;
    }
    if ((i = stringLargest(root->left, max)) > max) {
        max = i;
    } 
    if (stringLength(root->word) > max) {
        max = stringLength(root->word);
    }
    if ((i = stringLargest(root->right, max)) > max) {
        max = i;
    } 
    return max;
} 

// writes output to txt file
/*
- 'root' is the root node
- 'file' is the file being read from
- 'wfile' is the file that we will write into
- 'left' is used for left allignment formatting
- 'right' is used for right allignment formatting
*/
void write_inorder(struct Node *root, int file, int wfile, int left, int right) { 
    char* output = (char*) malloc(sizeof(char) * 1024);
    if (root != NULL) { 
        write_inorder(root->left,file, wfile, left, right); 
        if (root->word != NULL && root->count > 0) {
            sprintf(output,"%-*s : %*i\n", left, root->word, right, root->count);
            while ((wfile = write(file, output, strlen(output))) < 0) {
            }
        }
        write_inorder(root->right,file, wfile, left, right); 
    } 
} 

// returns 1 if 'c' is letter, 0 if not
int is_letter(char c) {
    return (c>='A' && c<='Z') || (c>='a' && c<='z');
}

// returns 1 if 'c' is alpha, 0 if not
int is_alpha(char c) {
    return (((c)>='a' && (c) <= 'z') || ((c)>='A' && (c) <= 'Z') || ((c)>='0' && (c) <= '9'));
}

// returns 'string' to lowercase form, ie: 'CODING' -> 'coding'
static char* toLowerCase(char* string) {
    int i = 0;
    while (string[i]) {
        string[i] = tolower(string[i]);
        i++;
    }
    return string;
}

/*
- handles the 'string' into a hash table 'element'
- inserts 'string' into table
- adds the count of 'string' from table
- returns 1 if data was changed or added
- returns 0 if node was null
*/
int handleWord(char* string, struct HashTableItem* element) {
    if (element->node == NULL) {
        return 0;
    }
    else if (element->node != NULL && findNode(element->node, string) == NULL) {
        insertNode(element->node, string);
        return 1;
    }
    else if (findNode(element->node, string) != NULL) { 
        findNode(element->node, string)->count++;
        return 1;
    }
    return 1;
}

int main(int argc, char* argv[]) {

    // create hash table, initialize nodes to null
    struct HashTableItem* arr[26];
    for (int i=0; i<26;i++) {
        arr[i] = (struct HashTableItem*)malloc(sizeof(struct HashTableItem));
        arr[i]->node = NULL;
    }
    
    // file handling variables
    int fdin;
    char* buf = (char*) malloc(sizeof(char) * 1024);
    ssize_t c; 
    char* envFile = getenv("WORD_FREAK"); 

    // handling environment variable
    if (envFile != NULL) { 
        char* word = (char*) malloc(sizeof(char) * 1024);
        fdin = open(envFile, O_RDONLY); 
        // loop through words, handle them
        while ((c = read(fdin, buf, 1)) > 0) {
            // if character is alpha and letter concat the word, else handle word
            if (is_alpha(buf[0]) == 1 && is_letter(buf[0])) { 
                strcat(word,buf);
            }  
            else if (is_alpha(word[0]) == 1 && is_letter(word[0])) { 
                int hash = hashCode(word);
                if (handleWord(toLowerCase(word), arr[hashCode(word)]) == 0) {
                    arr[hashCode(word)]->node = createNode(word);
                }
                word[0] = '\0';
            }   
        }     
        // edge case if last word is not added
        if (is_letter(word[strlen(word)-1]) == 1)  {
            int hash = hashCode(word);
            if (handleWord(toLowerCase(word), arr[hashCode(word)]) == 0) {
                arr[hashCode(word)]->node = createNode(word);
            }
            word[0] = '\0';
        } 
        // deallocate memory for word for environment handling
        free(word);  
    }
    // handling cmd line arguments
    if (argc > 1) { 
        char* word = (char*) malloc(sizeof(char) * 1024);       
        for (int i=1; i<argc;i++) {
            if ((fdin = open(argv[i], O_RDONLY)) == -1) {
                perror("File cannot be opened. \n");
            }
            else {
                // loop through words, handle them
                while ((c = read(fdin, buf, 1)) > 0) {   
                    // if character is alpha and letter concat the word, else handle word
                    if (is_alpha(buf[0]) == 1 && is_letter(buf[0])) { 
                        strcat(word,buf);
                    }  
                    else if (is_alpha(word[0]) == 1 && is_letter(word[0])) { 
                        int hash = hashCode(word);
                        if (handleWord(toLowerCase(word), arr[hashCode(word)]) == 0) {
                            arr[hashCode(word)]->node = createNode(word);
                        }
                        word[0] = '\0';
                    }   
                }     
                // edge case if last word is not added
                if (is_letter(word[strlen(word)-1]) == 1)  {
                    int hash = hashCode(word);
                    if (handleWord(toLowerCase(word), arr[hashCode(word)]) == 0) {
                        arr[hashCode(word)]->node = createNode(word);
                    }
                    word[0] = '\0';
                }   
                if ((close(fdin)) == -1) {
                    perror("File cannot be closed. \n");
                }
            }
        } 
        // deallocate memory for word for argument handling
        free(word);
    }    
    // handling piping and stdin    
    char* word = (char*) malloc(sizeof(char) * 1024);
    // loop through words, handle them
    while ((c = read(STDIN_FILENO, buf, 1)) > 0) {   
        // if character is alpha and letter concat the word, else handle word
        if (is_alpha(buf[0]) == 1 && is_letter(buf[0])) { 
            strcat(word,buf);
        }  
        else if (is_alpha(word[0]) == 1 && is_letter(word[0])) { 
            int hash = hashCode(word);
            if (handleWord(toLowerCase(word), arr[hashCode(word)]) == 0) {
                arr[hashCode(word)]->node = createNode(word);
            }
            word[0] = '\0';
        }   
    }     
    // edge case if the last word is not added
    if (is_letter(word[strlen(word)-1]) == 1)  {
        int hash = hashCode(word);
        if (handleWord(toLowerCase(word), arr[hashCode(word)]) == 0) {
            arr[hashCode(word)]->node = createNode(word);
        }
        word[0] = '\0';
    }  
    // deallocate memory for word for piping
    free(word);

    // handling outfile for writing
    int outfile = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    int w;

    // variables used for left and right allignment    
    int left = 0;
    int right = 0;

    // get left and right for allignment, looping through arr of BST's, ie: ['a']['b']['c']..
    for (int i=0; i<26; i++) {
        if (arr[i]->node != NULL) {
            int rightTemp = findDigit(digitLargest(arr[i]->node, 0));
            int leftTemp = stringLargest(arr[i]->node, 0);
            if (leftTemp > left) {
                left = leftTemp;
            } 
            if (rightTemp > right) {
                right = rightTemp;
            }
        }
    }
    right += 1;

    // write words to file, looping through arr of BST's, ie: ['a']['b']['c']..
    for (int i=0; i<26;i++) {
        if (arr[i]->node != NULL) {
            write_inorder(arr[i]->node, outfile, w, left, right);
        }
    }
    
    // deallocate memory for hash table
    for (int i=0; i<26;i++) {
        free(arr[i]);
    }

    return 0;
}