// prefix expression can contain signed or unsigned integers or fractional numbers
// two tokens should be separated by a space
// note that '$' stands for exponentiation operator

// also add function checking if entered prefix expression is correct or not

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

struct stack{
        int MAXSIZE;
        int top;
        float *elements;
    };

void create(int maxsize, struct stack *stackptr);
int isempty(struct stack *stackptr);  // 1 if empty
int pop(struct stack *stackptr, float *poppedptr);
int isfull(struct stack *stackptr);
int push(struct stack *stackptr, float new_elem);
int peek(struct stack *stackptr, float *peekedptr);
int display(struct stack *stackptr);
float operate(float oprnd1, float oprnd2, char oprtor);
float eval_prefix(char prefix_exp[]);

void main(){
    char inpstring[300];
    printf("Enter the prefix expression to be evaluated (space between two tokens, no space after unary +/-):\n");
    scanf("%[^\n]", inpstring);
    printf("\nValue of expression: %f\n", eval_prefix(inpstring));
}

float eval_prefix(char prefix_exp[]){

    int prefix_lastindex = strlen(prefix_exp)-1;
    char *rev_prefix_exp = (char *)malloc( sizeof(char)*( prefix_lastindex+2 ));
    for(int i=0; i<=prefix_lastindex; i++){
        rev_prefix_exp[prefix_lastindex-i] = prefix_exp[i];
    }
    rev_prefix_exp[prefix_lastindex+1] = '\0';

    static int index_to_read = 0;

    struct stack stack1 ;
    create(100, &stack1);

    char token[10];
    int token_length;
    int i,k;

    while(rev_prefix_exp[index_to_read]!='\0'){
        i=0;
        while(rev_prefix_exp[index_to_read]!=' ' && rev_prefix_exp[index_to_read]!='\0'){
            token[i]=rev_prefix_exp[index_to_read];     // token variable contains the token in reverse order
            i++, index_to_read++;
        }
        if(rev_prefix_exp[index_to_read]!='\0'){ index_to_read++ ; }   // now index_to_read contains index of next useful character ( white space between two tokens is jumped over )
        token_length = i;  // just to give current value of i a meaningful name:  token consists of token_length number of characters(excluding final ' ')
        token[token_length] = ' ' ;

        char temp;              // reversing the token to obtain the actual token
        for(i=0; i<=(token_length-1)/2; i++){
            temp = token[i];
            token[i] = token[token_length-1-i];
            token[token_length-1-i] = temp;
        }

        printf("\nToken read: ");  // printing the token
        for(i=0;i<token_length; i++){
            printf("%c", token[i]);
        }

        if( !( (token[0]=='+' || token[0]=='-' || token[0]=='*' || token[0]=='/' || token[0]=='$') && token[1]==' ') ){    // case where operand (number) is read
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
                push(&stack1,operand);                     // later, if required, include code for what to do if stack overflow
            }

            else {                                         //  index_dec_point>0 : operand contains decimal point
                for(i=flag;i<index_dec_point;i++){
                    operand += (token[i]-'0') * pow(10.0, index_dec_point-1-i);
                }
                for(i=index_dec_point+1;i<token_length;i++){
                    operand += (token[i]-'0') * pow(10.0, -1*(i-index_dec_point));
                }
                if(token[0]=='-'){ operand = -1*operand ; }
                push(&stack1, operand);                    // later, if required, include code for what to do if stack overflow
            }
        }

        else{                                            // case where an operator (+,-,*,/,^) is read
            float oprnd1, oprnd2;
            pop(&stack1, &oprnd1);
            pop(&stack1, &oprnd2);
            printf("\nOperation performed and result pushed into stack : %f %c %f\n", oprnd1, token[0], oprnd2);
            push(&stack1, operate(oprnd1, oprnd2, token[0]));
            display(&stack1);

        }
        display(&stack1);
    }

    return stack1.elements[0];
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


void create(int maxsize, struct stack *stackptr){
    stackptr->top=-1;
    stackptr->MAXSIZE = maxsize;
    stackptr->elements = (float *)malloc(sizeof(float)*maxsize);
}
int isempty(struct stack *stackptr){
    if(stackptr->top==-1){ return 1; }
    else{ return -1; }
}

int pop(struct stack *stackptr, float *poppedptr){
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

int push(struct stack *stackptr, float new_elem){
    if(isfull(stackptr)==1){ return -1; }
    else{
        (*stackptr).elements[++(stackptr->top)]=new_elem;
        return 1;
    }
}

int peek(struct stack *stackptr, float *peekedptr){
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
        printf("\nStack contents:\n");
        printf("|%15s|\n", " ");
        for( i=(*stackptr).top; i>=0; i--){
            printf( "| %13.6f |\n",(*stackptr).elements[i] );
        }
        printf(" ");
        for(int i=0; i<15;i++){ printf("-"); }
        printf("\n");
        return 1;
    }
}

//  + + 8 $ * 97.3 2 -3.1 * / -7.4 3 19.215 = -39.397
