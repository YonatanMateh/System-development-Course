
#include "complex.h"

void read_comp(complex *comNum, double aValue, double bValue){
    (*comNum).a = aValue;
    (*comNum).b = bValue;
}

void print_comp(complex *comNum,char *name){
    if (name != NULL)
        printf("The complex number %s is: %.2f + %.2fi\n",name,(*comNum).a, (*comNum).b);
    else
        printf("The complex number is: %.2f + %.2fi\n",(*comNum).a, (*comNum).b);
}

void add_comp(complex *comNum1, complex*comNum2,char *name1,char *name2){
    complex temp;
    temp.a = (*comNum1).a + (*comNum2).a;
    temp.b = (*comNum1).b + (*comNum2).b;
    printf("After adding the two complex numbers %s and %s,\n",name1,name2);
    print_comp(&temp,NULL);
}

void sub_comp(complex *comNum1, complex *comNum2,char *name1,char *name2){
    complex temp;
    temp.a = (*comNum1).a - (*comNum2).a;
    temp.b = (*comNum1).b - (*comNum2).b;
    printf("After reducing the two complex numbers %s and %s,\n",name1,name2);
    print_comp(&temp,NULL);
}

void mult_comp_real(complex *comNum, double num,char *name){
    complex temp;
    temp.a = (*comNum).a * num;
    temp.b = (*comNum).b * num;
    printf("After multipling the complex number %s with %f,\n",name,num);
    print_comp(&temp,NULL);
}

void mult_comp_img(complex *comNum, double num,char *name){
    complex temp;
    temp.a = (*comNum).a * num;
    temp.b = -(*comNum).b * num;
    printf("After multipling complex number %s with imaginary number,\n",name);
    if (temp.a > 0)
        print_comp(&temp,NULL);
    else
        printf("The complex number is: %.2f + (%.2fi)\n", temp.b, temp.a);

}

void mult_comp_comp(complex *comNum1, complex *comNum2,char *name1,char *name2){
    complex temp;
    temp.a = ((*comNum1).a * (*comNum2).a) - ((*comNum1).b * (*comNum2).b);
    temp.b = ((*comNum1).a * (*comNum2).b) + ((*comNum1).b * (*comNum2).a);
    printf("After multipling the two complex number %s and %s,\n",name1,name2);
    print_comp(&temp,NULL);
}

void abs_comp(complex *comNum,char *name){
    double abs = sqrt(pow((*comNum).a, 2.0) + pow((*comNum).b, 2.0));
    printf("The Absolute value of the complex number %s is: %.2f\n", name,abs);

}

