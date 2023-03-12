//error error error error

#include<stdio.h>
#include<string.h>

void main()
{
    char text[5000],word[50];int flag,i,j,count=0;
    printf("Text:\n");
    gets(text);
    printf("\nWord: ");
    scanf("%s",word);

    for(i=0 ; i<=( strlen(text)-strlen(word) ) ; i++)
    {
        flag=0;
        for (j=i ; flag==0 && j<i+strlen(word) ; j++)
        {
            if (strcmp(text[j],word[j-i]) != 0)
            {
                flag=1;
            }
        }
        if (flag==0)
        {
            count+=1;
        }
    }
    printf("\nOccurrence of word: %d times",count);
}
