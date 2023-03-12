#include<math.h>
void main()
{
    double l,r,f,c;
    printf("Inductance,Resistance (separated by a blank space): ");
    scanf("%lf %lf",&l,&r);
    printf("\nCapacitance      Frequency");

    for (c=0.01;c<=0.1;c+=0.01)
    {
        f = pow( (1/(l*c)) - ((r*r)/(4*c*c)) ,0.5 );
        printf("\n%-8.2lf          %-8.4lf",c,f);
    }
}
