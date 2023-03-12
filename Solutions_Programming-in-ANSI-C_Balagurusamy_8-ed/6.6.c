#include<math.h>
void main()
{
    printf("Number  ");
    for (float i=0.0;i<1.0;i+=0.1)
    {
        printf("%6.1f  ",i);
    }
    printf("\n");
    for(int i=0;i<=9;i++)
    {
        printf("%6d",i);
        for (float j=0.0;j<1.0;j+=0.1)
        {
            printf("%8.4f",sqrt(i+j));
        }
        printf("\n");
    }

}
