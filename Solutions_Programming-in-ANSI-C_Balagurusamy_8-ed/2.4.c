void main()
{
    float a,b,c,x;
    scanf("%f %f %f",&a,&b,&c);
    if(b-c!=0)
    {
        printf("%.2f",a/(b-c));
    }
    else
    {
        printf("Zero as the denominator!");
    }
}
