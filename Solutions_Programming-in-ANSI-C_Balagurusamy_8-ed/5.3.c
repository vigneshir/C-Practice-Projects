void main()
{
    float n;
    scanf("%f",&n);
    if ( n-(int)n >= 0.5 )
    {
        printf("%d",(int)n+1);
    }
    else
    {
        printf("%d",(int)n);
    }
}
