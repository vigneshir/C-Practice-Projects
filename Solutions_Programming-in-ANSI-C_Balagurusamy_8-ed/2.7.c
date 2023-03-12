#include<stdio.h>

float add(float a,float b),sub(float a,float b);

void main()
{
    float a,b;
    scanf("%f %f",&a,&b);
    printf("%.2f + %.2f = %.2f\n%.2f - %.2f = %.2f",a,b,add(a,b),a,b,sub(a,b));
}
float add(float a, float b)
{
    return a+b;
}
float sub(float a, float b)
{
    return a-b;
}
