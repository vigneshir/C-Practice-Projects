void main()
{
    int n,modfn,count=0,i;
    scanf("%d",&n);
    printf("\n\n");
    modfn = n;
    while (modfn>0)
    {
        count+=1;
        modfn= modfn/10;
    }
    for(i=count;i>0;i--)
    {
        printf("%d\n", n%(long int)pow(10,i));
    }

}
