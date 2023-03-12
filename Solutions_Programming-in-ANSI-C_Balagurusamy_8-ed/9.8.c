void main()
{
    char word[30]; int i,n,flag=0;
    printf("Word: ");
    scanf("%s",word);
    n=strlen(word);
    for (i=0;i<n/2&&flag==0;i++)
    {
        if( word[i]!=word[n-1-i] )
        {
            flag=1;
        }
    }
    if (flag==1)
    {
        printf("\nNot a palindrome.\n");
    }
    else
    {
        printf("\nA palindrome.\n");
    }
}
