#include <stdio.h>
#include <stdlib.h>

void printFunc(char *str);
char *getInputFromUser();

int main(int argc, const char * argv[]) {
    printFunc(getInputFromUser());
    return 0;
}

char *getInputFromUser(){
    /* NOTE: an instructor wrote in the forum that there isn't need for efficiency */
    char *str = malloc(sizeof(char));/* alloc*/
    int c;
    int len = 0;
    while (EOF != (c = getchar())) {/*getting input from user until he stopped*/
        str[len++] = c;
        str = realloc(str, sizeof(char) * (len+1));/*realloc for the next charackter*/
    }
    str[len++]='\0';/*the end*/
    return str;
}

/*print method*/
void printFunc(char *str){
    int i=0;
    putchar('\n');
    while (str[i]!= '\0') {
        putchar(str[i]);
        i++;
    }
    putchar('\n');
}
