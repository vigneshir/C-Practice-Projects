#include<stdio.h>
#include<stdlib.h>

struct stack{
        int MAXSIZE;
        int top;
        int *elements;
    };

void create(int maxsize, struct stack *stackptr);
int isempty(struct stack *stackptr);  // 1 if empty
int pop(struct stack *stackptr, int *poppedptr);
int isfull(struct stack *stackptr);
int push(struct stack *stackptr, int new_elem);
int peek(struct stack *stackptr, int *peekedptr);
int display(struct stack *stackptr);


void main(){
    int choice, maxsize;

    printf("------Stack Implemented Using Array------");
    printf("\n\nEnter the maximum possible size of the stack implementation: ");
    scanf("%d", &maxsize);

    struct stack stack1;
    create(maxsize, &stack1);

    int new_elem;
    printf("\n\nEnter the first element to be pushed: ");
    scanf("%d",&new_elem);
    push(&stack1, new_elem);
    printf("Element successfully pushed into stack.");

    printf("\n\nStack Operations:");
    printf("\n1. Push an element.");
    printf("\n2. Pop an element.");
    printf("\n3. Peek into the stack.");
    printf("\n4. Display stack contents.\n");

    for(;;){
        printf("\n\nEnter the operation to be performed (enter -1 to exit): ");
        scanf("%d", &choice);
        switch(choice){
            case 1:{
                if(isfull(&stack1)==1){ printf("Stack Overflow."); }
                // this check ensures element to be inserted not asked from user if stack overflow
                // the check inside push() and corresponding return value will be useful while checking for feasibility when
                //      new element is directly entered as argument in code rather than via input from user
                else{
                    int new_elem;
                    printf("Enter element to be pushed: ");
                    scanf("%d",&new_elem);
                    push(&stack1, new_elem);
                    printf("Element successfully pushed into stack.");
                }
                break;
            }

            case 2:{
                int popped;
                if(isempty(&stack1)==1){ printf("Stack Underflow."); }
                else{
                    pop(&stack1, &popped);
                    printf("Element %d successfully popped from stack.", popped);
                }
                break;
            }

            case 3:{
                int peeked;
                if(peek(&stack1,&peeked)==-1){ printf("Stack is empty."); }
                else{
                    peek(&stack1,&peeked);
                    printf("Element %d visible after peeking into stack.", peeked);
                }
                break;
            }

            case 4:{
                if(display(&stack1)==-1){ printf("Stack is empty, no element to display."); }
                break;
            }

            case -1:{
                printf("Exiting...");
                exit(0);
            }

            default:{
                printf("Please enter a valid number.");
            }
        }
    }
}

void create(int maxsize, struct stack *stackptr){
    stackptr->top=-1;
    stackptr->MAXSIZE = maxsize;
    stackptr->elements = (int *)malloc(sizeof(int)*maxsize);
}
int isempty(struct stack *stackptr){
    if(stackptr->top==-1){ return 1; }
    else{ return -1; }
}

int pop(struct stack *stackptr, int *poppedptr){
    if(isempty(stackptr)==1){
        return -1;
    }
    else{
        *poppedptr = (*stackptr).elements[(stackptr->top)--] ;
        return 1;
    }
}

int isfull(struct stack *stackptr){
    if(stackptr->top==stackptr->MAXSIZE-1){ return 1; }
    else{ return -1; }
}

int push(struct stack *stackptr, int new_elem){
    if(isfull(stackptr)==1){ return -1; }
    else{
        (*stackptr).elements[++(stackptr->top)]=new_elem;
        return 1;
    }
}

int peek(struct stack *stackptr, int *peekedptr){
    if(isempty(stackptr)==1){ return -1 ;}
    else{
        *peekedptr = (*stackptr).elements[stackptr->top] ;
        return 1;
    }
}

int display(struct stack *stackptr){
    if(isempty(stackptr)==1){ return -1 ;}
    else{
        int i;
        printf("Stack contents:\n");
        for( i=(*stackptr).top; i>=0; i--){
            printf( "%d\n",(*stackptr).elements[i] );
        }
        return 1;
    }
}
