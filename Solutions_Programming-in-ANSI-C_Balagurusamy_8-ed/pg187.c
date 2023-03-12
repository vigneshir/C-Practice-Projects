void main()
{
    int n,i,digit,bin[20];
    scanf("%d",&n);
    for(i=0;n>0;i++)
    {
        digit = n%2 ;
        bin[i] = digit;
        n=n/2;
    }
    for (i=i-1;i>=0;i--)
    {
        printf("%d",bin[i]);
    }
}
