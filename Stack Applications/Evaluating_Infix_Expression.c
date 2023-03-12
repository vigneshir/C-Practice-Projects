#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

struct flt_stack{
        int MAXSIZE;
        int top;
        float *elements;
    };

void createflt(int maxsize, struct flt_stack *stackptr);
int isemptyflt(struct flt_stack *stackptr);  // 1 if empty
int popflt(struct flt_stack *stackptr, float *poppedptr);
int isfullflt(struct flt_stack *stackptr);
int pushflt(struct flt_stack *stackptr, float new_elem);
int peekflt(struct flt_stack *stackptr, float *peekedptr);
int displayflt(struct flt_stack *stackptr);

float operate(float oprnd1, float oprnd2, char oprtor);

struct chr_stack{
        int MAXSIZE;
        int top;
        char *elements;
    };

struct chr_stack *create_chrstack(int maxsize);
int isEmptychr(struct chr_stack *ptr_chrstack);  // 1 if empty
int popchr(struct chr_stack *ptr_chrstack, char *poppedptr);
int isFullchr(struct chr_stack *ptr_chrstack);
int pushchr(struct chr_stack *chr_stack, char new_elem);
int peekchr(struct chr_stack *chr_stack, char *peekedptr);
int displaychr(struct chr_stack *ptr_chrstack);

float eval_infix(char *infix_exp);


void main(){
    char response[10] ;
    for( ; ; ){
        printf("\nWant to evaluate an infix expression?  ");
        scanf("%s",response);
        if(strcmp(response, "yes")==0){
            char *infix = (char *)malloc(sizeof(char)*200);          // expects max 149 tokens in infix
            printf("\nEnter the infix expression to be evaluated (each token separated by space, except unary + and -):\n");
            char garbage;
            scanf("%c%[^\n]", &garbage, infix);

            float result;
            result = eval_infix(infix);
            printf("\nEvaluated value of given infix expression: %f\n", result);

            free(infix);
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


float eval_infix(char *infix_exp){
    struct flt_stack *solstk;
    createflt(150, solstk);

    struct chr_stack *oprtorstk = create_chrstack(200);

    char *temp = (char *)malloc(sizeof(char)*200);    // adding '(' and ')' to original expression
    temp[0]='\0';
    strcpy(temp, infix_exp);
    strcpy(infix_exp,"( ");
    strcat(infix_exp,temp);
    strcat(infix_exp," )");
    printf("\nEntered Infix: %s\n", infix_exp);
    free(temp);

    char token[10];
    static int index_to_read = 0;
    int token_length;
    int i,k;

    while(infix_exp[index_to_read]!='\0'){
        i=0;
        while(infix_exp[index_to_read]!=' ' && infix_exp[index_to_read]!='\0'){
            token[i]=infix_exp[index_to_read];
            i++, index_to_read++;
        }
        if(infix_exp[index_to_read]!='\0'){ index_to_read++ ; }   // now index_to_read contains index of next useful character ( white space between two tokens is jumped over )
        token_length = i;  // just to give current value of i a meaningful name:  token consists of token_length number of characters(excluding final ' ')
        token[token_length] = ' ' ;   // to distinguish between unary and binary operators

        printf("\nToken read: ");  // printing the token
        for(i=0;i<token_length; i++){
            printf("%c", token[i]);
        }


        if(token[0]=='('){      // opening brace
            pushchr(oprtorstk,token[0]);
        }

        else if( (token[0]=='+'||token[0]=='-'||token[0]=='*'||token[0]=='/'||token[0]=='$')&&token[1]==' ' ){  // known operator
            if(isEmptychr(oprtorstk)==1){  // e.g. after reading 1 of 2 brackets:    (a+b-c*d) / (e/f/g-h+i)
                pushchr(oprtorstk, token[0]);
            }
            else{
                char peekedoprtor;
                peekchr(oprtorstk, &peekedoprtor);
                printf("\nPeeked Operator: %c\n", peekedoprtor);

                if(token[0]=='$'){                 // new operator read is '$'
                    pushchr(oprtorstk, token[0]);    // since it has the highest precedence no need to compare with previous operator
                }

                else if(token[0]=='/'||token[0]=='*'){     // new operator read is '/' or '*'
                    if(peekedoprtor=='+'||peekedoprtor=='-'|| peekedoprtor=='('){
                        pushchr(oprtorstk, token[0]);
                    }

                    else if(peekedoprtor=='*' || peekedoprtor=='/' || peekedoprtor=='$'){  // redundant, can use just 'else'
                        char poppedoprtor;
                        char poppedoprtor_str[200];
                        float oprnd1, oprnd2;
                        int flag;
                        do{
                            popchr(oprtorstk, &poppedoprtor);
                            popflt(solstk, &oprnd2);
                            popflt(solstk, &oprnd1);
                            pushflt(solstk, operate(oprnd1, oprnd2, poppedoprtor));

                            flag = peekchr(oprtorstk, &peekedoprtor);
                            displayflt(solstk);
                        }
                        while(flag==1 && (peekedoprtor=='*' || peekedoprtor=='/' || peekedoprtor=='$') );
                        pushchr(oprtorstk,token[0]);
                    }
                }

                else if(token[0]=='+'||token[0]=='-'){  // new operator read is '+' or '-'
                    char poppedoprtor;
                    char poppedoprtor_str[200];
                    float oprnd1, oprnd2;
                    int flag=1;
                    while(flag==1 && peekedoprtor!='('){    // note that peekedoprtor is declared and defined above case where token is $
                        popchr(oprtorstk, &poppedoprtor);
                        popflt(solstk, &oprnd2);
                        popflt(solstk, &oprnd1);
                        pushflt(solstk, operate(oprnd1, oprnd2, poppedoprtor));
                        flag = peekchr(oprtorstk, &peekedoprtor);
                        displayflt(solstk);
                    }
                    pushchr(oprtorstk,token[0]);
                }
            }
        }

        else if(token[0]==')'){    // closing brace
            char peekedoprtor;
            peekchr(oprtorstk, &peekedoprtor);
            printf("\nPeeked Operator: %c\n", peekedoprtor);

            char poppedoprtor;
            float oprnd1, oprnd2;

            while(peekedoprtor!='('){
                popchr(oprtorstk, &poppedoprtor);

                popflt(solstk, &oprnd2);
                popflt(solstk, &oprnd1);

                pushflt(solstk, operate(oprnd1, oprnd2, poppedoprtor));

                displaychr(oprtorstk);
                displayflt(solstk);
                peekchr(oprtorstk, &peekedoprtor);
                printf("\nPeeked Operator: %c", peekedoprtor);
            }

            popchr(oprtorstk, &poppedoprtor);
            displaychr(oprtorstk);

        }

        else if ( token[0]=='+'||token[0]=='-'||(token[0]>='0'&&token[0]<='9') ){    // case where operand (number) is read
            float operand=0;
            int flag, index_dec_point=-1;

            for(i=1;i<token_length;i++){                   // decimal point present or absent
                if( token[i]=='.'){ index_dec_point=i; break; }
            }

            if(token[0]=='+' || token[0]=='-'){ flag=1; }  // signed number
            else{ flag=0; }                                // unsigned number (positive number)

            if(index_dec_point==-1){                       // no decimal point in operand
                for(i=flag; i<token_length; i++){
                    operand += (token[i]-'0') * pow(10.0,token_length-1-i) ;
                }
                if(token[0]=='-'){ operand = -1*operand ; }
                pushflt(solstk,operand);                     // later, if required, include code for what to do if stack overflow
            }

            else {                                         //  index_dec_point>0 : operand contains decimal point
                for(i=flag;i<index_dec_point;i++){
                    operand += (token[i]-'0') * pow(10.0, index_dec_point-1-i);
                }
                for(i=index_dec_point+1;i<token_length;i++){
                    operand += (token[i]-'0') * pow(10.0, -1*(i-index_dec_point));
                }
                if(token[0]=='-'){ operand = -1*operand ; }
                pushflt(solstk, operand);                    // later, if required, include code for what to do if stack overflow
            }
        }


        else{
            printf("\nUnknown token '%c' found in the entered infix expression.\n", token[0]);
            break;
        }

        displaychr(oprtorstk);
        displayflt(solstk);
    }
    return solstk->elements[0] ;
}





void createflt(int maxsize, struct flt_stack *stackptr){
    stackptr->top=-1;
    stackptr->MAXSIZE = maxsize;
    stackptr->elements = (float *)malloc(sizeof(float)*maxsize);
}
int isemptyflt(struct flt_stack *stackptr){
    if(stackptr->top==-1){ return 1; }
    else{ return -1; }
}

int popflt(struct flt_stack *stackptr, float *poppedptr){
    if(isemptyflt(stackptr)==1){
        return -1;
    }
    else{
        *poppedptr = (*stackptr).elements[(stackptr->top)--] ;
        return 1;
    }
}

int isfullflt(struct flt_stack *stackptr){
    if(stackptr->top==stackptr->MAXSIZE-1){ return 1; }
    else{ return -1; }
}

int pushflt(struct flt_stack *stackptr, float new_elem){
    if(isfullflt(stackptr)==1){ return -1; }
    else{
        (*stackptr).elements[++(stackptr->top)]=new_elem;
        return 1;
    }
}

int peekflt(struct flt_stack *stackptr, float *peekedptr){
    if(isemptyflt(stackptr)==1){ return -1 ;}
    else{
        *peekedptr = (*stackptr).elements[stackptr->top] ;
        return 1;
    }
}

int displayflt(struct flt_stack *stackptr){
    if(isemptyflt(stackptr)==1){ return -1 ;}
    else{
        int i;
        printf("\nSolution Stack Contents:\n");
        printf("|%15s|\n", " ");
        for( i=(*stackptr).top; i>=0; i--){
            printf( "| %13.6f |\n",(*stackptr).elements[i] );
        }
        printf(" ");
        for(int i=0; i<17;i++){ printf("-"); }
        printf("\n");
        return 1;
    }
}

struct chr_stack *create_chrstack(int maxsize){
    struct chr_stack *ptr_chrstack = (struct chr_stack *)malloc(sizeof(struct chr_stack));
    ptr_chrstack->top=-1;
    ptr_chrstack->MAXSIZE = maxsize;
    ptr_chrstack->elements = (char *)malloc(sizeof(char)*maxsize);
    return ptr_chrstack;
}

int isEmptychr(struct chr_stack *ptr_chrstack){
    if(ptr_chrstack->top==-1){ return 1; }
    else{ return -1; }
}

int popchr(struct chr_stack *ptr_chrstack, char *poppedptr){  // poppedptr expected to point to single character, i.e. &poppedchr is the actual argument
    if(isEmptychr(ptr_chrstack)==1){
        return -1;
    }
    else{
        *poppedptr = (*ptr_chrstack).elements[(ptr_chrstack->top)--] ;      // reason for above comment: RHS is a ' ' char
        return 1;
    }
}

int isFullchr(struct chr_stack *ptr_chrstack){
    if(ptr_chrstack->top==ptr_chrstack->MAXSIZE-1){ return 1; }
    else{ return -1; }
}

int pushchr(struct chr_stack *ptr_chrstack, char new_elem){
    if(isFullchr(ptr_chrstack)==1){ return -1; }
    else{
        (*ptr_chrstack).elements[++(ptr_chrstack->top)]=new_elem;
        return 1;
    }
}

int peekchr(struct chr_stack *ptr_chrstack, char *peekedptr){
    if(isEmptychr(ptr_chrstack)==1){ return -1 ;}
    else{
        *peekedptr = (*ptr_chrstack).elements[ptr_chrstack->top] ;
        return 1;
    }
}

int displaychr(struct chr_stack *ptr_chrstack){
    if(isEmptychr(ptr_chrstack)==1){ return -1 ;}
    else{
        int i;
        printf("\nOperator Stack Contents:\n");
        printf(" |%3s|\n"," ");
        for( i=(*ptr_chrstack).top; i>=0; i--){
            printf( " | %c |\n",(*ptr_chrstack).elements[i] );
        }
        printf(" ");
        for(i=0;i<5;i++){ printf("%c",'-'); }
        return 1;
    }
}

float operate(float oprnd1, float oprnd2, char oprtor){
    switch(oprtor){
        case '+':
            return oprnd1+oprnd2 ;

        case '-':
            return oprnd1-oprnd2;

        case '*':
            return oprnd1*oprnd2;

        case '/':
            return oprnd1/oprnd2;

        case '$':
            return pow(oprnd1,oprnd2);

    }
}
