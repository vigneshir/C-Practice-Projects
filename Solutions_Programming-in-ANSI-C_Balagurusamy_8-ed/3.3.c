void main()
{
    int p=0,n=0; float input=1.0;
    printf("Enter the numbers (each on a  new line):\n");
    while (input!=0)
    {
        scanf("%f",&input);
        if (input>0)
        {
            p+=1;
        }
        else if(input<0)
        {
            n+=1;
        }
    }
    printf("Number of positive numbers: %d\nNumber of negative numbers: %d",p,n);
}
