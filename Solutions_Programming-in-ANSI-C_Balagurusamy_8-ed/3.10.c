void main()
{
    int days, years, wd,weeks,remdays;
    printf("Enter the number of days: ");
    scanf("%d",&days);
    years = days/365;
    wd = days%365;
    weeks = wd/7;
    remdays = wd%7;
    printf("\n\nYears: %d\nWeeks: %d\nDays: %d\n\n\n",years,weeks,remdays);

}
