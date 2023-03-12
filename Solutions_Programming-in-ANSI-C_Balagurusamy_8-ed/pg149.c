#include<string.h>
void main()
{
    char a[100];
    int c0,c1,c2,c3,c4,c5,c6,c7,c8,c9;
    c0=c1=c2=c3=c4=c5=c6=c7=c8=c9 = 0;
    scanf("%s",a);
    for (int i=0;i<strlen(a);i++)
    {
            switch(a[i])
            {
                case '0' : c0+=1;break;
                case '1' : c1+=1;break;
                case '2' : c2+=1;break;
                case '3' : c3+=1;break;
                case '4' : c4+=1;break;
                case '5' : c5+=1;break;
                case '6' : c6+=1;break;
                case '7' : c7+=1;break;
                case '8' : c8+=1;break;
                case '9' : c9+=1;break;
            }
     }
     printf("\n\n0 appears %d times\n1 appears %d times\n2 appears %d times\n3 appears %d times\n4 appears %d times\n5 appears %d times\n6 appears %d times\n7 appears %d times\n8 appears %d times\n9 appears %d times", c0,c1,c2,c3,c4,c5,c6,c7,c8,c9);
}
