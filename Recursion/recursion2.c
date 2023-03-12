int i=1;
void main()
{
    if(i<=50)
    {
        printf("%d\n",i++);
        main();
    }
}

// another way, without using global variable
//void printnum(int i);
//
//void main()
//{
//    int i=1;
//    printnum(i);
//}
//
//void printnum(int i)
//{
//    if (i<=50)
//    {
//        printf("%d\n",i);
//        printnum(i+1);
//    }
//}
