int fact(int n);

void main()
{
    int n;
    printf("Number: ");
    scanf("%d",&n);
    printf("\nFactorial: %ld",fact(n));
}

int fact(int n)
{
    unsigned long int factorial;
    if (n==1||n==0)
    {
        return 1;
    }
    else
    {
        factorial = n*fact(n-1);
    }

}
