#include <stdio.h>
#include "complex.h"

/***********
I got premission to sent the home work late
***********/


/*array struct of all funcations.
 contain paramters of the function name, pointer to the function, and the type of parameters (one complex numbr, two doubles etc.)*/
struct {
    char *name;
    void (*func)();
    int parameterType;
} funcArray[] = {
    {"read_comp", read_comp,TWO_DOUBLE},
    {"print_comp", print_comp, ONE_COMP},
    {"add_comp", add_comp,TWO_COMP},
    {"sub_comp", sub_comp,TWO_COMP},
    {"mult_comp_real", mult_comp_real,ONE_DOUBLE},
    {"mult_comp_img", mult_comp_img,ONE_DOUBLE},
    {"mult_comp_comp", mult_comp_comp,TWO_COMP},
    {"abs_comp", abs_comp,ONE_COMP},
    {"not_valid", NULL}
};

/*the extarn complex impelemntation*/
complex A,B,C,D,E,F;

/*array struct that contains the name of the complex numbers and pointers to them*/
struct {
    char *name;
    complex *var;
} complexArray[] = {
    {"A",&A},
    {"B",&B},
    {"C",&C},
    {"D",&D},
    {"E",&E},
    {"F",&F},
    {"0", NULL}
};
/*declaration*/
void removeSpaces(char* source);

int main(int argc, const char * argv[]) {
    /*variables declaration*/
    int c;
    unsigned long restLength;
    char command[MAX_COMMAND];/*contains the command input*/
    int i, funcIndex, varIndex;/*i: temp index for loops. funcIndex: contain the index for the current function. varIndex: contain the index for the current variable name*/
    int programState = TRUE, paramType=0;/* programState: contain the state of the program, true or error. paramType: contain the index for the right parameter type */
    char *commandName = "", *varName = "", *restOfTheCommand = "";/*pointers for the sperate command. contain three pointers: for the command, the variable, and the rest of the command (second arument) */
    FOREVER
    {
        /*reset of all variables and pointers*/
        c=0;i=0,funcIndex=0 , varIndex=0;
        programState = 1, paramType=0;
        commandName = "", varName = "", restOfTheCommand = "";
        memset(command, 0, sizeof(command));
        
        /*receiving input*/
        printf("Please enter command, or write \"halt\" to exit from the program!\n");
        while (((c = getchar()) != '\n') && i < MAX_COMMAND) {
            command[i++] = c;
            if (i>=MAX_COMMAND) {
                programState = ERROR;
                printf("Error: the command is too long");
            }
            
            if (c == EOF) {
                printf("Error: the program stopped working (EOF)\n");
                exit(1);
            }
        }
        
        /*proper program exit*/
        if(strcmp(command, "halt") == 0){
            printf("Program halting: exiting!\n");
            exit(0);
        }
        /*spliting the input command into the different variables*/
        commandName = strtok(command, " ");
        varName = strtok(NULL,",");
        restOfTheCommand = strtok(NULL,"");
        
        if (varName == NULL) {
            programState = ERROR;
            printf("Error: missing arguments\n");
        }
        
        
        /*check dommand and action*/
        if (programState != ERROR && commandName != NULL) {
            /*getting the right command anf checking if it exist in the different commands*/
            for (i=0; funcArray[i].func != NULL; i++) {
                if (strcmp(funcArray[i].name, commandName) == 0)
                    break;
            }
            
            if (funcArray[i].func == NULL) {
                programState = ERROR;
                printf("Invalid command\n");
            }else{
                funcIndex = i;
                removeSpaces(varName);                
                /*getting the comlex number name*/
                for (i=0; complexArray[i].var != NULL; i++)
                    if (strcmp(complexArray[i].name, varName) == 0)
                        break;
                
                /*checking some errors*/
                if (complexArray[i].var == NULL) {
                    programState = ERROR;
                    if (restOfTheCommand == NULL)
                        printf("Missing comma\n");
                    else
                        printf("Invalid complex variable\n");
                }else{
                    /*getting the parameter type and acting accordingly*/
                    paramType = funcArray[funcIndex].parameterType;
                    varIndex = i;
                    switch (paramType) {
                            /*parameter: one comple numer*/
                        case ONE_COMP:
                            if (restOfTheCommand == NULL)
                                funcArray[funcIndex].func(complexArray[varIndex].var,complexArray[varIndex].name);
                            else
                                printf("Excessive text\n");
                            break;
                            /*parameters: two complex numbers*/
                        case TWO_COMP:
                        {
                            if (restOfTheCommand == NULL) {
                                printf("Error: Missing parameters\n");
                            }else{
                                removeSpaces(restOfTheCommand);
                                restLength = strlen(restOfTheCommand);
                                if (restLength > 1) {
                                    if (restOfTheCommand[0] == ',')
                                        printf("Multiple consecutive commas\n");
                                    else
                                        printf("Error: secound argument is too long\n");
                                }else{
                                    /*getting the secound comle number name*/
                                    for (i=0; complexArray[i].var != NULL; i++)
                                        if (strcmp(complexArray[i].name, restOfTheCommand) == 0)
                                            break;
                                    
                                    if (complexArray[i].var == NULL) {
                                        programState = ERROR;
                                        printf("Invalid complex variable\n");
                                    }else
                                        funcArray[funcIndex].func(complexArray[varIndex].var,complexArray[i].var,complexArray[varIndex].name,complexArray[i].name);
                                }
                            }
                            break;
                            /*parameters: two real numbers*/
                        case TWO_DOUBLE:
                            {
                                double a,b;
                                char *aChar;
                                char *bChar;
                                /*spliting the command into the doubls and checking that it's only digits*/
                                a = strtod(strtok(restOfTheCommand,","), &aChar) ;
                                b = strtod(strtok(NULL,","), &bChar) ;
                                if ((aChar == NULL && bChar == NULL) || (aChar[0] == '\0' && bChar[0] == '\0'))
                                    funcArray[funcIndex].func(complexArray[varIndex].var,a,b,complexArray[varIndex].name);
                                else
                                    printf("Wrong parameter, second parameter must be a real number\n");
                            }
                            break;
                            /*parameter: one real number*/
                        case ONE_DOUBLE:{
                            char *ptr;
                            /*changing the char into a double and checking that it's only digits*/
                            double num = strtod(restOfTheCommand, &ptr);
                            if(ptr == NULL || ptr[0] == '\0'){
                                funcArray[funcIndex].func(complexArray[varIndex].var,num,complexArray[varIndex].name);
                            }
                            else
                                printf("Error: the second argument should be a valid number\n");
                            break;
                        }
                        default:
                            break;
                        }/*end of switch*/
                    }
                }
            }
        }
    }
    return 0;
}

/*removing space or tabs from giving string*/
void removeSpaces(char* source)
{
    if (source != NULL) {
        char* i = source;
        char* j = source;
        while(*j != 0)
        {
            *i = *j++;
            if(*i != ' ' && *i != '\t')
                i++;
        }
        *i = 0;
    }
}

