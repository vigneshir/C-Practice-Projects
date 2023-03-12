void main()
{
    float x[100],y[100],sumx=0,sumy=0,sumxy=0,sumxsq=0,m,c; int n,i;
    printf("Number of coordinates: ");
    scanf("%d",&n);
    printf("\nEnter the coordinates as x y : \n");
    for (i=0;i<n;i++)
    {
        scanf("%f %f",&x[i],&y[i]);
    }
    for (i=0;i<n;i++)
    {
        sumx += x[i];
        sumy += y[i];
        sumxy += x[i]*y[i];
        sumxsq += x[i]*x[i];
    }
    m = (n*sumxy - sumx*sumy)/(n*sumxsq - sumx*sumx);
    c = (sumy-m*sumx)/n;
    printf("\n\ny = %.3fx + %.3f\n\n",m,c);
}
