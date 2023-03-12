void main()
{
    int m=10,*p;
    p=&m;
    printf(    "p = %u",p);

    printf("\n\np = %x",p);
    printf(  "\np = %#x",p);
    printf(  "\np = %#X",p);

    printf("\n\np = %o",p);
    printf(  "\np = %#o",p);
    printf(  "\np = %#O",p);

    printf("\n\n*p = %d",*p);

}
