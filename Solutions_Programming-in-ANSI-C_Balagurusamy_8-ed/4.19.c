#include<stdio.h>

int isleap(int year);
int validdate(int day, int month, int year);

void main()
{
    int day,month,year;
    printf("Date (day month year)(separated by blank spaces and without unnecessary zeros): ");
    scanf("%d %d %d",&day,&month,&year);
    if ( validdate(day,month,year) )
    {
        printf("\nValid Date.");
    }
    else
    {
        printf("\nInvalid Date.");
    }
}

int isleap(int year)
{
    if ( (year%100 == 0 && year%400 == 0) || (year%100 != 0 && year%4 == 0) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int validdate(int date,int month,int year)
{
    if ( month==(1||3||5||7||8||10||12) && date>=1 && date<=31 )
        return 1;
    else if ( month==(4||6||9||11) && date>=1 && date<=30 )
        return 1;
    else if (month==2)
    {
        if ( isleap(year) )
        {
            if (date>=1 && date<=29)
                return 1;
            else
                return 0;
        }
        else
        {
            if (date>=1 && date<=28)
                return 1;
            else
                return 0;
        }
    }
    else
        return 0;
}




