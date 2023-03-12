#include<stdio.h>
#include<stdlib.h>

void main(){
    int *ptr_a = (int *)malloc(sizeof(int));
    *ptr_a = 10;
    test1(ptr_a);
    printf("*ptr_a = %d\n", *ptr_a);
}

void test1( int *ptr_x ){
    //*ptr_x = 20;   // changes value of ptr_a in main() to 20

    ptr_x = NULL;
    // this won't make the ptr_a inside main() a null pointer. It makes the copy of ptr_a in test1() a null pointer.
    // pointers are passed by value to functions, i.e. the function gets a copy of the pointer.
    // Remember that a copy of a pointer is another pointer pointing to same memory location as original (one which is in main()).
    // ****So we can modify the value of pointer in main() using this copy by using indirection operator, because copy pointer points to same memory as original.
    // ****However, we cannot change the 'type' of the pointer in main() by changing type of its copy in the function.
    // That's why ptr_a does not become a NULL pointer inside main()
}
