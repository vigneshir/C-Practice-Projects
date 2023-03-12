struct time_struct
{
    int hour;
    int minute;
    int second;
};

struct time_struct readtime()
{
    struct time_struct time;
    scanf("%d %d %d",&time.hour,&time.minute,&time.second);
    return time;
}

void printtime(struct time_struct time)
{
    printf("%02d:%02d:%02d\n",time.hour,time.minute,time.second);
}

struct time_struct modifytime(struct time_struct time)
{
    if (time.second==59)
    {
        time.second=00;
        if (time.minute == 59)
        {
            time.minute=00;
            if (time.hour==23)
            {
                time.hour=00;
            }
            else
            {
                time.hour+=1;
            }

        }
        else
        {
            time.minute+=1;
        }
    }
    else
    {
        time.second+=1;
    }
    return time;
}

void main()
{
    struct time_struct time,newtime;
    printf("Enter the time as hours minutes seconds : ");
    time = readtime();
    printtime(time);
    newtime = modifytime(time);
    printtime(newtime);
}
