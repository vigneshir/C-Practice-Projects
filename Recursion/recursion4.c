// needs to be improved such that function itself prints the series

int fibterm(int n);

void main()
{
    int n,i;
    printf("How many terms: ");
    scanf("%d",&n);
    for(i=1; i<=n;i++)
    {
        printf("%4d ", fibterm(i));
    }
}

int fibterm(int n)
{
    int term;
    if(n==1 || n==2)
    {
        term=1;
        return (term);
    }
    else
    {
        term = fibterm(n-1)+fibterm(n-2);
        return (term);
    }


}
