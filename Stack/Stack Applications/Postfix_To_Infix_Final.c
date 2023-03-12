//  operands are single alphabets (a-z, A-Z)         operators are either of + - * / % $        no space in postfix expression
// note:  reading or storing '^' as an operator gives runtime error as it is an ASCII control character with a special meaning


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
int postfix_to_infix(char *postfix, char *infix);

void main(){
    char response[10] ;
    for( ; ; ){
        printf("\nWant to convert a postfix expression to an infix expression? ");
        scanf("%s",response);
        if(strcmp(response, "yes")==0){
            char *postfix = (char *)malloc(sizeof(char)*100);          // expects max 99 tokens in postfix
            printf("\nEnter the postfix expression to be converted to an infix expression:\n");
            scanf("%s", postfix);

            char *infix = (char *)malloc(sizeof(char)*200);      // expects max 199 tokens in infix

            if(postfix_to_infix(postfix, infix)==1){
                printf("\nEquivalent infix expression:\n");
                printf("%s\n\n", infix);
            }

            free(postfix); free(infix);
        }

        else if(strcmp(response,"no")==0){
            printf("\nExiting...\n");
            exit(0);
        }

        else{
            printf("Enter 'yes' for a positive response and 'no' for a negative response.\n");
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

int postfix_to_infix(char *postfix, char *infix){

    struct string_stack *ptr_strstack1;
    ptr_strstack1 = create_strstack(200);   // can fill upto 200 expressions of under_construction infix

    int i;

    char *token = (char *)malloc(sizeof(char)*2);
    char *oprnd1 = (char *)malloc(sizeof(char)*200);
    char *oprnd2 = (char *)malloc(sizeof(char)*200);
    char *opration_cum_oprnd = (char *)malloc(sizeof(char)*200);

    for(i=0; postfix[i]!='\0'; i++){
        token[0]= postfix[i];
        token[1]='\0';
        opration_cum_oprnd[0]='\0';

        if(token[0]>='A' && token[0]<='z'){    // token is an operand
            push(token, ptr_strstack1);
            if( display(ptr_strstack1)==-1){ printf("\nError: Empty Stack\n"); return -1; }
        }
        else if(token[0]=='+' || token[0]=='-' || token[0]=='*' || token[0]=='/' || token[0]=='%' || token[0]=='$'){  // token is a valid operator
            if( pop(ptr_strstack1, oprnd2) == -1){ printf("\nError: Invalid postfix expression. Remove extraneous operators.\n"); return -1; }

            else if( pop(ptr_strstack1, oprnd1) == -1){ printf("\nError: Invalid postfix expression. Remove extraneous operands.\n"); return -1; }

            else if( (strlen(oprnd1)+strlen(oprnd2)+4)>200 ){ printf("\nError: Postfix or corresponding infix expression too large to handle.\nExiting...\n"); return -1; }

            else{
                strcat(opration_cum_oprnd,"(");
                strcat(opration_cum_oprnd,oprnd1);
                strcat(opration_cum_oprnd, token);
                strcat(opration_cum_oprnd, oprnd2);
                strcat(opration_cum_oprnd, ")");

                push(opration_cum_oprnd, ptr_strstack1);

                if( display(ptr_strstack1)==-1){ printf("\nError: Empty Stack\n"); return -1;}
            }

        }
        else{
            printf("Error: Unknown token '%s' found in entered postfix expression.\n", token);
            return -1;
        }
    }
    strcpy(infix, ptr_strstack1->ptr_charptr[0]);

    free(token); free(oprnd1); free(oprnd2); free(opration_cum_oprnd);
    destroy(ptr_strstack1);
    return 1;
}
