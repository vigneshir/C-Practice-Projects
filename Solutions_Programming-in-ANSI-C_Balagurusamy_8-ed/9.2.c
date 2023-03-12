#include<stdio.h>
#include<string.h>

void main()
{
    int turn=3,flag=0; char ans[50]="";
    printf("Who invented C?\n");
    do
    {
        gets(ans);
        turn-=1;
        if (!strcmp(ans,"Dennis Ritchie"))
        {
            flag=1;
            printf("\nCorrect answer.\n\n");
        }
        else
        {
            printf("Wrong answer. %d chance(s) remaining.\n",turn);
        }
    }
    while(flag==0 && turn>0);
    if (flag==0)
    {
        printf("Chances over. The correct answer is Dennis Ritchie.\n\n");
    }

}
