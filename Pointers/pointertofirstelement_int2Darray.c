void main(){
    int arr[4][5] = { {1,2,3,4,5},{6,7,8,9,10},{11,12,13,14,15},{16,17,18,19,20} };
    int i,j;
    for (i=0;i<4;i++){
        for(j=0;j<5;j++){
            printf("%d\t",&arr[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");

    // array name when used in any expression, decomposes into a pointer to its first element and this pointer is used in the expression
    // only 2 exceptions to this rule: when array name is used as the operand for : 1) & operator  2) sizeof function.
    //                                                                        Here name of array refers to entire array object (not a pointer).


    printf("        &arr = %d           arr = %d\n",&arr,arr);
    printf("    (&arr)+1 = %d         arr+1 = %d\n",(&arr)+1,arr+1);
    printf("sizeof(&arr) = %d\n" , sizeof(&arr));   // returns size of address (int) of array object
    printf(" sizeof(arr) = %d\n\n", sizeof(arr));   // returns size of entire array object

    // left column: 'arr' refers to entire array of arrays object (i.e. 'arr' is not a pointer here.) (exception cases of & and sizeof())
    //right column: 'arr' is pointer to integer array arr[0]



    printf("   *(arr+1) = %d\n", *(arr+1));
    printf("*(arr[0]+1) = %d     *(*arr+1) = %d     *(*(arr+3)+4) = %d\n\n", *(arr[0]+1), *(*arr+1),*(*(arr+3)+4));



    printf("*(&arr) = %d     *arr = %d\n\n", *(&arr),*arr);

    // left column returns: address of arr[0] array
    // right column returns: address of arr[0][0] element
    // here left column should return arr object, i.e. entire array (since 'arr' refers to entire array object in &arr). This 'arr' gets decomposed into
                            // pointer to integer array arr[0], same as above first row right column
    // in right column arr[0] array should have been returned, but it decomposes to pointer to arr[0][0]
                                                //and this address of arr[0][0] is actually returned.


    printf("    *arr = %d       **arr = %d\n",*arr,**arr);
    printf("*(arr+1) = %d   **(arr+1) = %d\n\n",*(arr+1),**(arr+1));

    // shows decomposition of array name to pointer to its first member (only one * returns address, two *s return actual member value).

    // *arr should have returned arr[0], which itself is an array, but this arr[0] decomposes into a pointer to first element of arr[0], i.e. to arr[0][0]
    // and hence value of this pointer, i.e. &arr[0][0] is returned, instead of the arr[0] array.
    // **arr translates to *(*arr) and hence returns *( pointer to arr[0][0] ), i.e. value of arr[0][0] element



    printf("&arr[0][0] = %d\n",&arr[0][0]);
    printf("   &arr[0] = %d\n",&arr[0]);
    printf("      &arr = %d\n\n",&arr);

    // remember the three entities which contain the same address initially (point to same location initially) but behave differently on using arithmetic.
}

