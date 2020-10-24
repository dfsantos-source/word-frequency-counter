# Project 3 Overview:
Takes some files as input, and counts how many times each 
word occurs across them all, writing words and associated 
counts to an output file in alphabetical order.

## Youtube Video:
https://youtu.be/7TL-XDG_8CU

## Output: 
1. Files can be done by stdin, which can be a file typed in, or words
that are typed in as well. stdin will be handled accordingly, into 
the output.txt file. 
ie: cat aladdin.txt | ./wordfreak
2. Files can also be done by arguments, in which the files are registered
as arguments. 
ie: ./wordfreak iliad.txt newton.txt
3. Files can also be done by environment variable. Where the environment 
variable is passed in by the command line, in which files are handled.
ie: WORD_FREAK=iliad.txt ./wordfreak
4. Finally, files can be handled by all above, where the program can handle
files piped in or words typed in, files passed in as argv, and a file as
the environment variable all at once.

## Structure/Design: 
In my program, I use two main structures for the program to work. I use 
struct Node, which contains variables, 'left', 'right', 'word', 'count'
I use another structure for handling the hash function, called 
struct HashTableItem which stores a single struct Node. In my implementation,I create a hash table, where we have 26 HashTableItems, which contain pointers to 26 nodes. In this case, 26 binary search trees.

## Word Handling:
In the program, words are tokenized, by checking the ASCII values of 
characters. The words are then converted to lowercase using toLowerCase(char* string). 
Once the word is complete, the word is hashed by hashCode(word). By hashing we figure
out what BST this word should be handled in. For example, hashing "apple"
will return an index for the appropriate BST of the hash table. After 
figuring out what BST we are working with, we handle the word by the
function, handleWord(char* string, HashTableItem* element). By handling 
the word, we will either add it to the BST, or update the count if the 
word already exists.  

## Writing:
An output txt file is opened, so the words can be written into it. In order
for the format to be correct, we must get a left and right allignment value
so the format is lined up. The 'left' variable is used to allign the words,
while the 'right' variable is used to allign the count of the words. Once
left and right allignment values are found, the program is ready to write
the words into output.txt. The program loops through all BST's, printing 
in order recursively, using write_inorder(). Passing left and right values
into sprintf(), the format is aligned correctly.