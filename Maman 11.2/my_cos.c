#include <stdio.h>
#include <math.h>

#define PI 3.14159265359

double my_cos(double x);
double factorial(int num);

int main(int argc, const char * argv[]) {
    double num;
    double originalNumber;
    double result;
    scanf("%lf",&num);
    originalNumber = num;
    num = fmod(num, PI*2);
    if (num <0) {
        num*=-1;
    }
    result = my_cos(num);
    printf("\nThe result from my cos: %f",result);
    printf("\nThe result from the nath library: %f\n",cos(originalNumber));
    return 0;
}
/*my clculation method for cos*/
double my_cos(double x){
    unsigned int i=0;
    double result=0.0;
    double temp = 1.0;
    for (i=0;  temp> 1e-6 || temp <= -1e-6; i++) {
       temp = pow((-1), i) * pow(x, 2*i) / factorial(2*i);
       result+=temp;
    }
    return result;
}

double factorial(int num){
    if(num==0)
        return(1);
    else
        return(num*factorial(num-1));
}




