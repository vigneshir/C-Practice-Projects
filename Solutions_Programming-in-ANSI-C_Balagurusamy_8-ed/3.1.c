void main()
{
    int i,n; float hsum=0;
    printf("Enter number of terms in harmonic series: ");
    scanf("%d",&n);
    for (i=1;i<=n;i++)
    {
        hsum += 1.0/i ;
    }
    printf("\nThe sum of the harmonic series is: %f",hsum);

}
