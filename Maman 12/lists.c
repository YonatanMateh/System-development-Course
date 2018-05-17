#include <stdio.h>
#include <stdlib.h>
typedef struct node * nodeItem;
typedef struct node{
    char data;
    nodeItem next;
}item;

void addToList(nodeItem *, char);
void printList(nodeItem);
void freeList(nodeItem *);

int main(){
    nodeItem list = NULL;
    char input; /*contins the input charackter*/
    
    while (scanf("%c",&input)!=EOF) {
        addToList(&list, input);
    }
    printList(list);
    freeList(&list);
    return 0;
}

void addToList(nodeItem *theList, char input){
    nodeItem temp1, temp2 = NULL;
    /*the new node*/
    nodeItem newNode;
    newNode= (nodeItem)malloc(sizeof(item));
    if(!newNode){
        printf("\nError! somthing went wrong");
        exit(0);
    }
    newNode->data=input;
    temp1 = *theList;
    
    while (temp1){
        temp2 = temp1;
        temp1 = temp1->next;
    }
    /* if the list is null set the pointer to the first node */
    if(!*theList){
        *theList = newNode;
        newNode->next=temp1;
    }else{
        /* set the last pointer to point on the new nodw */
        temp2->next = newNode;
        newNode->next=temp1;
    }
    
}

void printList(nodeItem list){
    printf("\n");
    while (list) {
        printf("%c",list->data);
        list = list->next;
    }
    printf("\n");
}

void freeList(nodeItem *theList){
    nodeItem temp;
    while (*theList) {
        temp=*theList;
        *theList = (*theList)->next;
        free(temp);
    }
}
