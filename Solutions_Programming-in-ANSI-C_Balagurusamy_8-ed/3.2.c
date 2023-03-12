void main()
{
    float rice,sugar;
    printf("Price of Sugar (per kg): "); scanf("%f",&sugar);
    printf("Price of Rice (per kg): "); scanf("%f",&rice);
    printf("*******LIST OF ITEMS*******\n");
    printf("%-15s%-15s\n", "Item","Price");
    printf("%-15sRs %-15.2f\n","Rice",rice);
    printf("%-15sRs %-15.2f\n","Sugar", sugar);
}
