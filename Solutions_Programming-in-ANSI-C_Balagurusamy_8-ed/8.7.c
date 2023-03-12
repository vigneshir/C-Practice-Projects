void main()
{
    int p,q,r,s,i,j,k;
    printf("Enter size of matrix1 (rows columns): ");
    scanf("%d %d",&p,&q);
    printf("\nEnter size of matrix2 (rows columns): ");
    scanf("%d %d",&r,&s);
    if(q!=r)
    {
        printf("\nMATRICES NOT CONFORMABLE TO MATRIX MULTIPLICATION !\n\n");
    }
    else
    {
        float mat1[p][q], mat2[r][s],prodmat[p][s];
        printf("\n\nElements of matrix1 (row-wise):\n");
        for (i=0;i<p;i++)
        {
            for (j=0;j<q;j++)
            {
                scanf("%f",&mat1[i][j]);
            }
        }
        printf("\n\nElements of matrix2 (row-wise):\n");
        for (i=0;i<r;i++)
        {
            for (j=0;j<s;j++)
            {
                scanf("%f",&mat2[i][j]);
            }
        }
        printf("\n\nProduct:\n");
        for (i=0;i<p;i++)
        {
            for (j=0;j<s;j++)
            {
                prodmat[i][j]=0;
                for (k=0;k<q;k++)
                {
                    prodmat[i][j] += mat1[i][k]*mat2[k][j];
                }
                printf("%4.2f  ",prodmat[i][j]);
            }
            printf("\n");
        }
    }

}
