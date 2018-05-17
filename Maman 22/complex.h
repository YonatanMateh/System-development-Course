
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
/*macros*/
#define MAX_COMMAND 50
#define FOREVER for(;;)
#define MIN_ARGS 3
#define ERROR 0
#define TRUE 1
/*complex data struct*/
typedef struct complex{
    double a;
    double b;
}complex;

extern complex A,B,C,D,E,F;

/*defining the parameters type*/
enum parameterType {ONE_COMP,TWO_COMP,ONE_DOUBLE,TWO_DOUBLE};

/*reading complex number into the struct*/
void read_comp(complex *comNum, double aValue, double bValue);

/*print the choosen complex number*/
void print_comp(complex *comNum,char *name);

/*adding two complex number*/
void add_comp(complex *comNum1, complex*comNum2,char *name1,char *name2);


/*subtraction of two complex number*/
void sub_comp(complex *comNum1, complex *comNum2,char *name1,char *name2);

/*multipling complex number with real number*/
void mult_comp_real(complex *comNum, double num,char *name);

/*multipling complex number with imaginary number*/
void mult_comp_img(complex *comNum, double num,char *name);

/*multipling two complex numbers*/
void mult_comp_comp(complex *comNum1, complex *comNum2,char *name1,char *name2);

/*printing the Absolute value of giving numer*/
void abs_comp(complex *comNum,char *name);
