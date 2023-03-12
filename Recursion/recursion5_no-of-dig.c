
int noofdig(int n);

void main()
{
    int n;
    printf("Number: ");
    scanf("%d",&n);
    printf("\nNumber of digits: %d",noofdig(n));
}

int noofdig(int n)
{
    static int counter=1;
    n=n/10;
    if(n>0)
    {
        ++counter;
        noofdig(n);
    }
    else
    {
        return (counter);
    }
}
