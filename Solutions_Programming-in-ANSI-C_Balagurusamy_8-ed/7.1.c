void main()
{
    int orignum,numcopy,revnum=0;
    scanf("%d",&orignum);
    numcopy=orignum;
    while (numcopy>0)
    {
        revnum = revnum*10 + numcopy%10 ;
        numcopy = numcopy/10 ;
    }
    printf("\n%d",revnum);
}
