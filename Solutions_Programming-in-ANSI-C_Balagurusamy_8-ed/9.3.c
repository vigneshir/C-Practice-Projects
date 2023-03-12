#include<stdio.h>
#include<string.h>
void main()
{
    char sent[70]; int m,n,i,j;
    gets(sent);
    printf("\nm(no. of extracted chrs) n(pos of chr in sent): ");
    scanf("%d %d",&m,&n);
    char ans[m];
    for(i=n-1,j=0;i<=n-1+m-1;i++,j++)
    {
        ans[j]=sent[i];
    }
    printf("\n");
    puts(ans);

}
