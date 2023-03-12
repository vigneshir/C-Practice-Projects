void main()
{
    int i,arr[5];
    printf("5 array elements: ");
    for (i=0;i<5;i++)
    {
        scanf("%d",(arr+i));
    }
    printf("\nentered array: ");
    for (i=0;i<5;i++)
    {
        printf("%d ",*(arr+i));
    }
}
