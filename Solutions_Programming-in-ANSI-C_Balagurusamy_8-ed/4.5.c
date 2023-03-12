void main()
{
    float n;
    scanf("%f",&n);
    if ( n-(int)n != 0)
    {
        printf("%d   %f   %d", (int)n+1,n,(int)n);
    }
    else
    {
        printf("%d   %f   %d", n,n,n);
    }
}
