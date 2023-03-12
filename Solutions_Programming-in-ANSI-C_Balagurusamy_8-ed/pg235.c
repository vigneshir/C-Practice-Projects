void main()
{
    float a[3][3],b[3][3],sum[3][3];int i,j;
    printf("Elements of array 1 (row-wise, one after other):\n ");
    for (i=0;i<3;i++)
    {
        for (j=0;j<3;j++)
        {
            scanf("%f",&a[i][j]);
        }
    }
    printf("\nElements of array 1 (row-wise, one after other): \n");
    for (i=0;i<3;i++)
    {
        for (j=0;j<3;j++)
        {
            scanf("%f",&b[i][j]);
        }
    }
    printf("\n\n");
    for (i=0;i<3;i++)
    {
        for (j=0;j<3;j++)
        {
            sum[i][j]=a[i][j]+b[i][j];
            printf("%4.2f  ",sum[i][j]);
        }
        printf("\n");
    }

}
