// method 1 :  entire stack structure is stored in heap.   here only 1 variable is stored in memory stack: address of (stack structure in heap)
// method 2 :  array of stack structure is stored in heap. here three variables are stored in memory stack: int MAXSIZE, int top, address of pointer to char pointer
// method 3 :  entire stack structure is stored in memory stack.  here above three variables + all strings stored in stack structure are stored
// here method 1 is followed


// working as expected only in online compiler (programiz), not in codeblocks....why???


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct string_stack{
    int MAXSIZE;
    int top;
    char **ptr_charptr;
};

struct string_stack *create_strstack(int maxsize);
int isEmpty(struct string_stack *ptr_strstack);
int isFull(struct string_stack *ptr_strstack);
int push(char *new_elem, struct string_stack *ptr_strstack); // new_elem[] istead of char *new_elem because input string is taken into " "(???)
int pop(struct string_stack *ptr_strstack, char *popped);


void main(){
    struct string_stack *ptr_strstack1;
    int maxsize=10;
    char *pushed = (char *)malloc(sizeof(char)*30); // in this example a string can be of max 29 chrs
    char *popped = (char *)malloc(sizeof(char)*30);

    ptr_strstack1 = create_strstack(maxsize);

    printf("      &maxsize = %llu  (stack memory)\n", &maxsize);
    printf("       &pushed = %llu  (stack memory)\n", &pushed);
    printf("       &popped = %llu  (stack memory)\n", &popped);
    printf("        pushed = %llu  (heap memory)\n", pushed);
    printf("        popped = %llu  (heap memory)\n\n", popped);

    strcpy(pushed, "string 0");    // push 1
    push(pushed, ptr_strstack1);
    pop(ptr_strstack1,popped);     // pop 1
    strcpy(pushed, "string 1");    // push 2
    push(pushed, ptr_strstack1);
    strcpy(pushed, "string 2");    // push 3
    push(pushed, ptr_strstack1);
    pop(ptr_strstack1,popped);     // pop 2
    strcpy(pushed, "string 3");
    push(pushed, ptr_strstack1);   // push 4
    strcpy(pushed, "string 4");
    pop(ptr_strstack1, popped);    // pop 3
    strcpy(pushed, "string 5");    // push 5
    push(pushed, ptr_strstack1);
    strcpy(pushed, "string 6");    // push 6
    push(pushed, ptr_strstack1);

}


struct string_stack *create_strstack(int maxsize){
    struct string_stack *ptr_strstack = (struct string_stack *)malloc(sizeof(struct string_stack));
    ptr_strstack -> MAXSIZE = maxsize;
    ptr_strstack -> top = -1;
    ptr_strstack -> ptr_charptr = (char **)malloc(maxsize*sizeof(char *));
    printf("\nStructure members storage in heap:\n");
    printf("               &ptr_strstack = %llu  (stack memory)\n", &ptr_strstack);
    printf("                ptr_strstack = %llu  (heap memory section 1)\n", ptr_strstack );
    //printf("      sizeof(*ptr_strstack)  = %d\n\n", sizeof(*ptr_strstack) ); // in C cannot obtain size of block pointed to by a pointer

    printf("    &(ptr_strstack->MAXSIZE) = %llu  (heap memory section 1)\n", &(ptr_strstack->MAXSIZE));
    printf("        &(ptr_strstack->top) = %llu  (heap memory section 1)\n", &(ptr_strstack->top));
    printf("&(ptr_strstack->ptr_charptr) = %llu  (heap memory section 1)\n\n", &(ptr_strstack->ptr_charptr));

    //printf("      sizeof(*(ptr_strstack->ptr_charptr))  = %d\n", sizeof(*(ptr_strstack->ptr_charptr)) ); // in C cannot obtain size of block pointed to by a pointer

    int i;
    for(i=0; i<(ptr_strstack->MAXSIZE); i++){
        printf("&(ptr_strstack->ptr_charptr[%d]) = %llu  (heap memory section 2)\n", i,&(ptr_strstack->ptr_charptr[i]) );
    }
    printf("\n");
    return ptr_strstack;
}


int isEmpty(struct string_stack *ptr_strstack){
    if(ptr_strstack->top==-1){ return 1; }
    else{ return -1; }
}


int isFull(struct string_stack *ptr_strstack){
    if(ptr_strstack->top == (ptr_strstack->MAXSIZE)-1){ return 1; }
    else{ return -1; }
}


int push(char *new_elem, struct string_stack *ptr_strstack){
    if(isFull(ptr_strstack) == 1){return -1; }
    else{
        ptr_strstack->ptr_charptr[++(ptr_strstack->top)] = (char *)malloc(sizeof(char)*(strlen(new_elem)+1));
        strcpy( ptr_strstack->ptr_charptr[ptr_strstack->top] , new_elem ) ;
        int i;

        printf("\nAfter push:  ");
        //printf("Memory allocated to each string to which each element of array of char pointers points:\n");
        //for(i=0; i<(ptr_strstack->MAXSIZE); i++){
            //printf("sizeof[*(ptr_strstack->ptr_charptr[%d])] = %d\n", i, sizeof( *(ptr_strstack->ptr_charptr[i]) ) ); // in C cannot obtain size of block pointed to by a pointer
        //}
        //printf("\n\n");

        printf("Addresses stored in array of strings of stack (addresses contained in pointers to string):\n");
        for(i=0; i<(ptr_strstack->MAXSIZE); i++){
            printf( "ptr_strstack->ptr_charptr[%d] = %llu  (heap memory section 3)\n", i, ptr_strstack->ptr_charptr[i] );
        }
        printf("\n");
        return 1;
    }
}


int pop(struct string_stack *ptr_strstack, char *popped){
    if(isEmpty(ptr_strstack)==1){ return -1 ; }
    else{
        strcpy(popped , ptr_strstack->ptr_charptr[(ptr_strstack->top)--]);

        free(ptr_strstack->ptr_charptr[ (ptr_strstack->top)+1 ]);

        return 1;
    }
}
