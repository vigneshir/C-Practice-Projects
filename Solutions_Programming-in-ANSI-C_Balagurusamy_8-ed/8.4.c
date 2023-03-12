void main()
{
    int n,i,j;
    printf("Number of rows: ");
    scanf("%d",&n);
    int pasctable[n][n];
    for(i=0;i<n;i++)
    {
        pasctable[i][0]=1;
        pasctable[i][i]=1;
        for ( j=1; i>=2,j<i ; j++)
        {
            pasctable[i][j]=pasctable[i-1][j-1]+pasctable[i-1][j];
        }
        printf("\n");
        for (j=0; j<=i; j++)
        {
            printf("%-4d  ",pasctable[i][j]);
        }
        printf("\n");
    }

}
