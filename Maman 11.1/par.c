#include <stdio.h>
#include "par.h"

int brackets[100];/*contains the brackets for order check*/
char line[100];/*contain the current line*/
int currentIndex=0;/*the current index in the line*/
int curlyBracketCounter=0;/*counting the number of curly brackets when opening and closing*/
int currentLine=0;/*the number of the current line*/

void addBracket(int currentBracket);
void resetIndex();
void resetLine();
void checkString(char str[100]);
void deleteCpmments(char str[100]);
int closeBracket(char bracket);
void errorInLineNumber(int lineNumber, char content[100],char errorType[100],char bracket);
void resetLine();

int main(int argc, const char * argv[]) {
    int state = FLOW;
    char c;
    int index=0;
    while ((c=getchar()) != EOF) {
        switch (state) {
            case FLOW:
              if (c=='/')
		state = RIGHT_SLASH;
              else if(c=='\n'){/*when the text got to the end of the line, run the check*/
 		checkString(line);
/*reset the line and index, for a new check*/
                index=0;
                resetLine();
                state = FLOW;
	      }else
                line[index++]=c;
            break;
/*comment mode*/
        case RIGHT_SLASH:
            if (c=='*')
                state = IN_COMMENT;
            else{
                line[index++]='/';
                line[index++]=c;
                state = FLOW;
            }
            break;
        case IN_COMMENT:
            if (c=='*')
                state = RIGHT_STAR;
            break;
        case RIGHT_STAR:
            if (c == '/')
                state = FLOW;
            else if (c != '*')
                state = IN_COMMENT;
            break;
        default:
            break;

    }
    }

    if (curlyBracketCounter!=0) {
        printf(SPARE_CURLY_BRACKET_ERROR);
    }
    return 0;

}

void addBracket(int currentBracket){/*adding bracket to the array for a later check if there a match closing bracket*/
    brackets[currentIndex] = currentBracket;
    currentIndex++;
}

int closeBracket(char bracket){/*checking if there a match opening bracket, and returning true or false*/
    currentIndex--;
    if (bracket==')') {
        if (brackets[currentIndex] == ROUND_BRACKET) {
            resetIndex();
            return TRUE;
        }else
            return FALSE;
    }

    if (bracket==']'){
        if (brackets[currentIndex] == SQUARE_BRACKET) {
            resetIndex();
            return TRUE;
        }else
            return FALSE;
    }else
        return FALSE;
}

void resetIndex(){
    brackets[currentIndex]='\0';
}
/*the method is checking one line every time for errors of brackets*/
void checkString(char str[100]){
    int error=FALSE;
    int i;
    char c=str[0];
    int inString = FALSE;
    currentLine++;
    for (i=0;str[i]!='\0' ; i++) {/*looping till the end of the line*/
        if (error) {/*if there is an error in the line, if there is don't check the rest of the line*/
            c=EOF;
        }else
            c=str[i];

        if(c=='\"' || c=='\'')/*if the text is in a ' or " (aka string), don't check for errors (-was written in the forum)*/
            inString = !inString;

        if (!inString) {
            if (c=='{') {
               if (str[i+1]=='\0')
                curlyBracketCounter++;
            else{
                error=TRUE;
                errorInLineNumber(currentLine, str, CURLI_BRACKET_ERROR,' ');
            }
        }else if(c=='}'){
            if (str[i+1]=='\0')
                if (curlyBracketCounter==0) {/*check that the bracket is closing*/
                    error=TRUE;
                    printf(CLOSE_CURLY_BRACKET_ERROR);
                }else
                    curlyBracketCounter--;
            else{
                error=TRUE;
                errorInLineNumber(currentLine, str, CURLI_BRACKET_ERROR,' ');
            }
        }

        if (c=='(')
            addBracket(ROUND_BRACKET);
        else if (c==')'){
            if (!closeBracket(')')) {
                error=TRUE;
                errorInLineNumber(currentLine, str, ORDER_BRACKET_ERROR,')');
            }
        }

        if(c=='[')
            addBracket(SQUARE_BRACKET);
        else if(c==']'){
            if (!closeBracket(']')) {
                error=TRUE;
                errorInLineNumber(currentLine, str,ORDER_BRACKET_ERROR,']');
            }
        }
    }
    }
}

/*print func*/
void errorInLineNumber(int lineNumber, char content[100],char errorType[100],char bracket){
    printf("\nline number %d content: %s %s bracket type: %c \n",lineNumber,content,errorType,bracket);
}

/*resets the line array*/

void resetLine(){
    int i=0;
    char c=line[0];
    for (i=0; c!='\0'; i++) {
        line[i]='\0';
        c=line[i+1];
    }
}



