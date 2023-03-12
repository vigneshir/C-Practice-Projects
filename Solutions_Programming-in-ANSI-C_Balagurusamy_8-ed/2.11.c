#include <stdio.h>
#include <math.h>
void main()
{
    float a,b,c,s,A;
    scanf("%f %f %f",&a,&b,&c);
    s = (a+b+c)/2;
    A = pow(s*(s-a)*(s-b)*(s-c),0.5);
    printf("%.2f",A);
}
