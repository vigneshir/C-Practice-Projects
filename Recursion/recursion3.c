int sumall(int n);

void main()
{
    int n;
    printf("till which number is sum to be found: ");
    scanf("%d",&n);
    printf( "\n%d",sumall(n));
}

int sumall(int n)
{
    int sum;
    if (n>0)
    {
        sum = n+sumall(n-1);
        return (sum);
    }

}
