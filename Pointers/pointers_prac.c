void main(){
    int a[4][5],*ptr;
    printf("%d",a);      // prints some address A1
    printf("\n%d",&a);   // prints address A1 too
    printf("\n%d   %d",sizeof(a), sizeof(int));   // prints 80 bytes ..... (4*5)*4.....(number of elements in array)*(bytes required for 1 int)
    printf("\n%d",sizeof(&a));  // prints 8 bytes (compiler specific size for a pointer)
    printf("\n%d  %d",a[1],&a[1]);   //
}
