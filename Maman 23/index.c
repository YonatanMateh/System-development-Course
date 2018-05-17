#include "index.h"

/*tree functions*/
/*creating a new tree node*/
struct treeNode *newTreeNode(char *item, int line){
    struct treeNode *temp = (struct treeNode *)malloc(sizeof(struct treeNode));
    temp->key = malloc(sizeof(item));
    strcpy(temp->key, item);
    temp->lines = malloc(sizeof(int *));
    temp->lines[0] = line;
    temp->linesLength = 1;
    temp->left = temp->right = NULL;
    return temp;
}
/*inserting a new node into a given tree*/
struct treeNode *insertNewNode(struct treeNode *newNode, char *key, int line){
    /* If the tree is empty, return a new node */
    int  ret;
    int i;
    int *temp;
    int check = TRUE;
    /*if the tree is null, creata new one*/
    if (newNode == NULL) return newTreeNode(key, line);
    
    /*if not, check if theword is the same as the previous one, and locate it in the right place in the binary search tree*/
    ret = strcmp(key, newNode->key);
    
    
    if (ret < 0)/*the new word is before the previous one*/
        newNode->left = insertNewNode(newNode->left, key, line);
    else if(ret >0 )/*the new word is after the previous one*/
        newNode->right = insertNewNode(newNode->right, key, line);
    else{/*the new word already exists in the tree. adding the line number into the array*/
        for (i=0; i<newNode->linesLength; i++) {/*checking if the word alerdy exists in the specific line*/
            if (newNode->lines[i] == line)
                check = FALSE;
        }
        if(check){/*if it's a ne word in the line, reallocad memory for a new line number*/
            temp = realloc(newNode->lines, newNode->linesLength + 2);
            if (!temp)
            {
                fprintf(stderr, "Out of memory!\n");
                exit(0);
            }
            newNode->lines = temp;
            newNode->lines[newNode->linesLength] = line;
            newNode->linesLength++;
        }
        
    }
    /* return the  node pointer */
    return newNode;
}
/*separating the string of the file into words*/
struct treeNode* separateWordsFromFile(FILE *file){
    struct treeNode *root = NULL;
    char c;
    char word[MAXWORD] = {0};
    int line=1,i=0;
    if (file) {
        while ((c = fgetc(file)) != EOF)
        {
            if (c == '\n') {/*new line*/
                if (word[0] != '\0'){
                    if (root == NULL)
                        root = insertNewNode(root, word, line);
                    else
                        insertNewNode(root, word, line);
                    i=0;
                    memset(word, 0, sizeof(word));
                }
                line++;
            }else if ((isalpha(c) || isdigit(c))) {/*check that the current charckter is a valid one*/
                if (isupper(c))
                    c = tolower(c);
                
                word[i] = c;
                i++;
            }else{/*there is a full word; add to the tree*/
                if (word[0] != '\0'){
                    if (root == NULL)
                        root = insertNewNode(root, word, line);
                    else
                        insertNewNode(root, word, line);
                    
                    i=0;
                    memset(word, 0, sizeof(word));
                }
            }
        }
        /*for the last word from the file*/
        if (word[0] != '\0'){
            if (root == NULL)
                root = insertNewNode(root, word, line);
            else
                insertNewNode(root, word, line);
            
            i=0;
            memset(word, 0, sizeof(word));
        }
        
    }else{
        printf("Error: something went wrong, check if the file exists");
        exit(0);
    }
    return root;
    
}

/*free the memory of the tree*/
void freeTree(struct treeNode *node){
    if (node != NULL) {
        freeTree(node->right);
        freeTree(node->left);
        free(node->lines);
        free(node);
    }
}
/*recursive function the going over the tree node and sending the data for printing to the file*/
void writeToFile(struct treeNode *node,char fileName[MAXWORD]){
    if (node != NULL) {
        writeToFile(node->left,fileName);
        printToFile(node,fileName);
        writeToFile(node->right,fileName);
    }
}
/*writing the data into the file*/
void printToFile(struct treeNode *node,char fileName[MAXWORD]){
    FILE *file = fopen(fileName, "a");
    int i;
    fprintf(file, "%-13s appears in ",node->key);
    fprintf(file, "%s ",(node->linesLength>1) ? "lines" : "line");
    for (i=0; i<node->linesLength; i++) {
        fprintf(file, "%d",node->lines[i]);
        if (i != (node->linesLength-1)) {
            fputc(',', file);
        }
    }
    fputs("\n", file);
    fclose(file);
}
