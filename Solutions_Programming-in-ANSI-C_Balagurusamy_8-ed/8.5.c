void main()
{
    int n,i,j;
    printf("Number of students: ");
    scanf("%d",&n);
    float results[n][4], totmarks[n], highest[4]={0}, hroll[4]={0} ;
    printf("\nRoll number  Subject1  Subject2  Subject3\n");
    for (i=0;i<n;i++)
    {
        scanf("%f %f %f %f",&results[i][0], &results[i][1], &results[i][2], &results[i][3]);
    }
    printf("\n\nRESULTS:\n");
    printf("\nRoll Number   Total Marks");
    for (i=0;i<n;i++)
    {
        totmarks[i]= results[i][1] + results[i][2] + results[i][3];
        for (j=1;j<=3;j++)
        {
            if (results[i][j]>highest[j-1])
            {
                highest[j-1]=results[i][j];
                hroll[j-1]=results[i][0];
            }
        }
        if (totmarks[i]>highest[3])
        {
            highest[3]=totmarks[i];
            hroll[3]=results[i][0];
        }
        printf("\n%11.0f   %3.2f",results[i][0],totmarks[i]);
    }
    printf("\n");
    printf("\n              Highest Marks   Roll Number");
    printf("\n   Subject1:  %10.2f   %11.0f",highest[0],hroll[0]);
    printf("\n   Subject2:  %10.2f   %11.0f",highest[1],hroll[1]);
    printf("\n   Subject3:  %10.2f   %11.0f",highest[2],hroll[2]);
    printf("\nTotal Marks:  %10.2f   %11.0f",highest[3],hroll[3]);


}
