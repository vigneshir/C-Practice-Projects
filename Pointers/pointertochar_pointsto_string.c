void main(){
    int arr[5]={ 1,2,3,4,5 };
    int i,j;
    for(i=0;i<5;i++){
        printf("%d\t",&arr[i]);
    }
    printf("\n\n");


    printf("&arr = %d\n",&arr);  // 'arr' is pointer to entire array (exception case as array name is used as operand to &)
    printf(" arr = %d\n\n",arr);    // 'arr' is pointer to arr[0] , i.e. element 1


    printf("   *arr = %d\n",*arr);
    // 'arr' is pointer to arr[0], so arr[0] is returned
    printf("*(&arr) = %d\n\n",*(&arr));
    // 'arr' is pointer to entire array. Hence entire array should have been returned. But this array decomposes into pointer to arr[0].
                           //Value of this pointer (address of arr[0]) is actually printed.



    printf("(&arr)+1 = %d\n",(&arr)+1); // 'arr' is pointer to entire array. Hence adding 1 to its value gives address of location
                                                                                           //after last byte of last member of array
    printf("   arr+1 = %d\n\n",arr+1); // 'arr' is pointer to arr[0], i.e. element 1. Hence adding value of this pointer by 1 gives address of element 2




    printf("sizeof(&arr) = %d\n", sizeof(&arr)); // 'arr' refers to entire array (i.e. 'arr' is not a pointer here)
    printf(" sizeof(arr) = %d\n\n", sizeof(arr)); // 'arr' is a pointer to an integer arr[0], i.e. element 1

}
