// method 1 :  entire stack structure is stored in heap.   here only 1 variable is stored in memory stack: address of (stack structure in heap)
// method 2 :  array of stack structure is stored in heap. here three variables are stored in memory stack: int MAXSIZE, int top, address of pointer to char pointer
// method 3 :  entire stack structure is stored in memory stack.  here above three variables + all strings stored in stack structure are stored
// here method 1 is followed

// note: the size of the string entered into the stack can be anything

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
int push(char *new_elem, struct string_stack *ptr_strstack); // what if arg is taken as new_elem[] instead of char * ?
int pop(struct string_stack *ptr_strstack, char *popped);
int peek(struct string_stack *ptr_strstack, char *peeked);
int display(struct string_stack *ptr_strstack);
void destroy(struct string_stack *ptr_strstack);

void main(){
    struct string_stack *ptr_strstack1;
    int maxsize;

    printf("------Stack of Strings-------\n");
    printf("\nEnter the maximum number of strings that the stack should be able to store: ");
    scanf("%d", &maxsize);
    ptr_strstack1 = create_strstack(maxsize);
    printf("Stack created successfully.\n");

    printf("\nStack Operations:\n");
    printf("1. Push a string into the stack\n2. Pop the topmost string\n3. Peek into the stack\n4. Display the entire stack\n");
    printf("Enter -1 to exit.\n\n");

    for( ; ; ){
        int choice;
        printf("\nEnter the operation to be performed: ");
        scanf("%d",&choice);
        switch(choice){
            case 1:
            {
                if(isFull(ptr_strstack1)==1){ printf("Stack overflow.\n"); }
                else{
                    char *new_elem = (char *)malloc(100*sizeof(char));
                    printf("Enter the string to be pushed into the stack (max 99 characters long): ");
                    scanf("%*c%[^\n]%*c", new_elem); // or gets
                    push(new_elem, ptr_strstack1);
                    printf("Element pushed successfully.\n");
                    free(new_elem);
                }
            }
            break;

            case 2:
            {
                if(isEmpty(ptr_strstack1)==1){ printf("Stack underflow.\n"); }
                else{
                    char *popped = (char *)malloc(100*sizeof(char));
                    pop(ptr_strstack1,popped);
                    printf("Element '%s' popped successfully.\n",popped);
                    free(popped);
                }
            }
            break;

            case 3:
            {
                char *peeked = (char *)malloc(100*sizeof(char));
                if(peek(ptr_strstack1, peeked)== -1){ printf("Stack is empty.\n"); }
                else{
                    printf("Topmost element of the stack: %s\n",peeked);
                }
                free(peeked);
            }
            break;

            case 4:
                if(display(ptr_strstack1)==-1){ printf("Stack is empty.\n"); }
                break;

            case -1:
                destroy(ptr_strstack1);
                printf("Exiting...");
                exit(0);

            default:
                printf("Invalid operation.\n");
                break;
        }
    }

}


struct string_stack *create_strstack(int maxsize){
    struct string_stack *ptr_strstack = (struct string_stack *)malloc(sizeof(struct string_stack));
    ptr_strstack -> MAXSIZE = maxsize;
    ptr_strstack -> top = -1;
    ptr_strstack -> ptr_charptr = (char **)malloc(maxsize*sizeof(char *));

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

        return 1;
    }
}


int pop(struct string_stack *ptr_strstack, char *popped){
    if(isEmpty(ptr_strstack)==1){ return -1 ; }
    else{
        popped[0]='\0';
        strcpy(popped , ptr_strstack->ptr_charptr[(ptr_strstack->top)--]);

        free(ptr_strstack->ptr_charptr[ (ptr_strstack->top)+1 ]);

        return 1;
    }
}


int peek(struct string_stack *ptr_strstack, char *peeked){
    if(isEmpty(ptr_strstack)==1){ return -1 ; }
    else{
        strcpy( peeked, ptr_strstack->ptr_charptr[(ptr_strstack->top)] );
        return 1;
    }
}


int display(struct string_stack *ptr_strstack){
    if(isEmpty(ptr_strstack)==1){ return -1; }
    else{
        int i;
        printf("Stack Contents:\n");
        printf(" |%30s|\n"," ");
        for(i=ptr_strstack->top; i>=0; i--){
            printf(" |%30s|\n",ptr_strstack->ptr_charptr[i]);
        }
        printf(" ");
        for(i=0;i<32;i++){ printf("%c",'-'); }
        printf("\n");
        return 1;
    }
}

void destroy(struct string_stack *ptr_strstack){
    int i;
    for(i=0; i < ptr_strstack->top ; i++){
        free(ptr_strstack->ptr_charptr[i]);
    }
    free(ptr_strstack->ptr_charptr);
    free(ptr_strstack);
}
