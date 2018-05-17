#include "index.h"

int main(int argc, const char * argv[]){
    char fileName[MAXWORD];/*contain the file name*/
    struct treeNode *root = NULL;
    strcpy(fileName, argv[1]);
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");/*reading the data from the file*/
        root = separateWordsFromFile(file);
        strcat(fileName, ".index");
        writeToFile(root,fileName);
        freeTree(root);
        fclose(file);
    }else{
        printf("somthing went wrong, could not opend file\n");
        exit(1);
    }
    
    return 0;
}


