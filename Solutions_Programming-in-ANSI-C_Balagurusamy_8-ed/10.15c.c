void strjoin(char a[50],char b[50]);

void main()
{
    char a[50],b[50];
    printf("Strings to be concatenated: ");
    scanf("%s %s",a,b);
    strjoin(a,b);
}

void strjoin(char a[50],char b[50])
{
    int i,j=0;
    for (i=0;a[i]!='\0';i++)
    {

    }
    while (b[j]!='\0')
    {
        a[i+j]=b[j];
        ++j;
    }
    a[i+j]='\0';
    printf("\n%s",a);
}
