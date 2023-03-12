#define ACCURACY 0.00001

double invfact(int n);

void main()
{
    double e=0.0; int i;
    for (i=0 ; invfact(i)>=ACCURACY ; i++)
    {
        e += invfact(i);
    }
    printf("%lf   %d",e,i);

}

double invfact(int n)
{
    int f=1;
    for (int i=1;i<=n;i++)
    {
        f = f*i;
    }
    return 1.0/f;
}
