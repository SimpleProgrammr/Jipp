#include <math.h>
#include <stdio.h>

double Mabs(double x) {
    if(x<0) return -x;
    return x;
}
int main(void) {
    double x = 3.14, y= 12.56, z = 7;
    int k =2, m=4;

    double w1 = pow(x/(y*z), 1.0/3.0) * log(pow(x,2.0)+pow(y,2.0));
    double w2 = sin((double)k*(x/2.0))*cos((double)m*y)
    + y * exp(2.0*x-1.0);
    double w3 = (double)Mabs(x/((2*pow(y,2.0) +1)))
    + sqrt(y/(pow(z,2.0)+3))
    + 5*pow(y+z,3);
    double w4 = x/(y*z) * pow(z+1, 1.0/3.0)+ pow(pow(x,2.0)+pow(z,2.0) +1.0, 1.0/(double)k) - Mabs(y);
    double w5 = 1/(sqrt(pow(x,2.0)+pow(y,2.0) + pow(k,2.0))) + (1/x)*sin((double)k*y) ;

    printf("w1 = %.8lf\n", w1);
    printf("w2 = %.8lf\n", w2);
    printf("w3 = %.8lf\n", w3);
    printf("w4 = %.8lf\n", w4);
    printf("w5 = %.8lf\n", w5);
}

