
int sumofdig(int n);

void main()
{
    int n;
    printf("Number: ");
    scanf("%d",&n);
    printf("\nSum of digits: %d",sumofdig(n));
}

int sumofdig(int n)
{
    static int sum=0,dig;
    if (n>0)
    {
        dig=n%10;
        sum+=dig;
        sumofdig(n/10);
    }
    else
    {
        return sum;
    }
}
