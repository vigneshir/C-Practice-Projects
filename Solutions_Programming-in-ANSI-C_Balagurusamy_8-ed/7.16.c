void main()
{
    int a,i,sum=0,c=0;
    for (i=0;i<10;i++)
    {
        scanf("%d",&a);
        getchar();
        if (sum<=600)
        {
            if (a>0)
            {
                sum+=a;
                c++;
            }
        }
    }
    printf("%d %d",sum,c);
}
