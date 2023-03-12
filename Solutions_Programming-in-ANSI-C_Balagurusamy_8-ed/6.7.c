void main()
#define BASE_PRICE 100
#define FIRST_200 0.8
#define NEXT_100 0.9
#define BEYOND_300 1
#define SURCHARGE_FRAC 0.15
{
    float pay; int units;
    printf("Total units consumed: ");
    scanf("%d",&units);
    pay = BASE_PRICE;
    if (units>200)
    {
        pay+=200*FIRST_200;
        if (units>300)
        {
            pay += 100*NEXT_100 + (units-300)*BEYOND_300;
            if (units>400)
            {
                pay+= pay*SURCHARGE_FRAC;
            }
        }
        else
        {
            pay+=(units-200)*NEXT_100;
        }
    }
    else
    {
        pay+=units*FIRST_200;
    }

    printf("Total Cost: %.2f\n\n",pay);


}


