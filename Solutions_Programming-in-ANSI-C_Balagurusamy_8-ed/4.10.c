void main()
{
    int a,b,c,largest;
    scanf("%d %d %d",&a,&b,&c);
    largest = (a>b)?((a>c)?a:c):((b>c)?b:c)  ;
    printf("\n%d",largest);
}
