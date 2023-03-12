#include<math.h>
#include<stdlib.h>

#define ACCURACY 0.000001
#define PI 3.141592

void main()
{
    double sinx, term, x; int i,j;
    printf("Angle in degrees: ");
    scanf("%lf",&x);
    x = x*(PI/180);
    term = x;
    sinx = term;
    for (i=3,j=1 ; abs(term)>=ACCURACY ; i+=2,j++)
    {
        term = pow( -1,j ) * ( ( abs(term) * x*x )/( i*(i-1) ) );
        sinx += term;
        //printf("\n%lf\n",term);
    }
    //printf("%d %d\n",i,j);
    printf("sin %f = %lf",x,sinx);
}
