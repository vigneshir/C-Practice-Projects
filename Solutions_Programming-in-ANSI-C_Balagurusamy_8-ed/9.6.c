//error error error error error error error

#include<stdio.h>
#include<string.h>

void main()
{
    char text[500],origword[20],newword[20],ans[500],placeholder[500];
    printf("Text:\n");
    gets(text);
    printf("\nOriginal word, New Word (with only space in between): ");
    scanf("%s %s",origword,newword);

    if( strstr(text,origword) == NULL )
    {
        printf("\nOriginal word not found in text !\n");
    }
    else
    {
        int pos=strstr(text,origword),i,j;
        for (i=0;i<pos;i++)
        {
            ans[i]=text[i];
        }
        ans[pos]='\0';
        strcat(ans,newword);
        //printf("\n");
        //puts(ans);
        for (i=pos+strlen(origword),j=0;i<strlen(text);i++,j++)
        {
            placeholder[j]=text[i];
        }
        placeholder[j]='\0';
        strcat(ans,placeholder);
        printf("\n");
        puts(ans);
    }
}
