struct segdate
{
    int day;
    int month;
    int year;
};

void main()
{
    struct segdate date;
    printf("Enter date as day month year: ");
    scanf("%d %d %d",&date.day,&date.month,&date.year);
    if ( isvaliddate(date.day,date.month,date.year))
    {
        printf("Valid date.");
    }
    else
    {
            printf("Invalid date.");
    }
    printf("\n");
    monthdd_yyyy(date);
}



int isleap(int year)
{
    return ( !((year%100)&&(year%400) ) ?  1  :  ( !(year%4) ? 1 : 0 ) );
}

int isvaliddate(int day, int month, int year)
{
    if ( month==1 || month==3 || month==5 || month==7 || month==8 || month==10 || month==12 )
    {
        if (day>=1 && day<=31)
        {return 1;}
        else
        {return 0;}
    }
    else if ( month==4 || month==6 || month==9 || month==11 )
    {
        if (day>=1 && day<=30)
        {return 1;}
        else
        {return 0;}
    }
    else if (month==2)
    {
        if (isleap(year) && day==29)
        {return 1;}
        else if (day>=1 && day<=28)
        {return 1;}
        else
        {return 0;}
    }
    else
    {return 0;}
}

void monthdd_yyyy(struct segdate date)
{
    char months[12][10]={"January","February","March","April","May","June","July","August","September","October","November","December"};
    printf("%s %d, %d\n", months[(date.month)-1], date.day, date.year);
}
