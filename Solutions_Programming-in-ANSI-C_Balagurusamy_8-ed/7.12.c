#include<math.h>

void main()
{
    float p,pscrap,c,d; int n;
    printf("Original Cost, Depreciation Rate, Scrap Value (separated by spaces): ");
    scanf("%f %f %f", &c,&d,&pscrap);
    p=c;
    for (n=1; p!= pscrap; n++)
    {
        p = c * (1-d);
        c = p;
    }
    n = n-1;
    printf("\nUseful life: %d years\n",n);
}
