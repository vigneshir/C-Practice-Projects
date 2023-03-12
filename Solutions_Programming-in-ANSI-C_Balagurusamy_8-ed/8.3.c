void main()
{
    int count[6]={0,0,0,0,0,0},a,i;
    printf("Enter the ballot readings (enter an alphabet after completion):\n");
    while( scanf("%d\n",&a)==1 )
    {
        if (a>=1 && a<=5)
        {
            ++count[a-1];
        }
        else
        {
            ++count[5];
        }
    }
    printf("\nRESULTS:");
    for (i=1;i<=5;i++)
    {
        printf("\nCandidate %d   : %2d votes",i,count[i-1]);
    }
        printf("\nSpoilt Ballots: %2d",count[5]);

}
