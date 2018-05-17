#include <stdio.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define MAXWORD 100
#define TRUE 1
#define FALSE 0
struct treeNode {
    char *key;/*the key/word*/
    int *lines;/*array of line numbers*/
    int linesLength;/*length of the lines array*/
    struct treeNode *left, *right;/*leafs of the tree*/
};

/*declaration*/
struct treeNode *newTreeNode(char *item, int line);
struct treeNode *insertNewNode(struct treeNode *newNode, char *key, int line);
struct treeNode* separateWordsFromFile(FILE *file);

void writeToFile(struct treeNode *node,char fileName[]);
void printToFile(struct treeNode *node,char fileName[]);
void freeTree(struct treeNode *root);
