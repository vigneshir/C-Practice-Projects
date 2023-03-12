#include<stdio.h>
#include<string.h>
void main()
{
    char name[30]; int i;
    gets(name);
    for (i=0;i<strlen(name);i++)
    {
        printf("%d ",name[i]);
    }
}
