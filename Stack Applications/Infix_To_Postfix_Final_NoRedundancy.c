// refer Infix_To_Postfix_1 for instructive comments and printf statements
// Assumed Precedence or Arithmetic Operators:
//       $              Exponentiation
//      / *             Division   Multiplication
//      + -             Addition   Subtraction
// Same priority operators adjacent to each other are evaluated from left to right, except for $
// Adjacent $ operations are evaluated from right to left.  E.g.:  a$b$c = a$(b$c)

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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

void infix_to_postfix(char *infix, char *postfix);

void main(){
    char response[10] ;
    for( ; ; ){
        printf("\nWant to convert an infix expression to a postfix expression? ");
        scanf("%s",response);
        if(strcmp(response, "yes")==0){
            char *infix = (char *)malloc(sizeof(char)*200);          // expects max 149 tokens in infix
            printf("\nEnter the infix expression to be converted to a postfix expression (no space between any two tokens and tokens are either operators or alphabet operands):\n");
            scanf("%s", infix);

            char *postfix = (char *)malloc(sizeof(char)*150);      // expects max 149 tokens in postfix

            infix_to_postfix(infix, postfix);
            printf("\nEquivalent postfix expression:\n");
            printf("%s\n\n", postfix);

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
        *poppedptr = (*ptr_chrstack).elements[(ptr_chrstack->top)--] ;  // reason for above comment: RHS is a ' ' char
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
        printf("\n");
        return 1;
    }
}


void infix_to_postfix(char *infix, char *postfix){
    struct chr_stack *oprtorstk = create_chrstack(50);

    char *temp = (char *)malloc(sizeof(char)*200);
    temp[0]='\0';
    strcpy(temp, infix);
    infix[0]='(';
    infix[1]='\0';
    strcat(infix,temp);
    strcat(infix,")");
    printf("\nEntered Infix: %s\n", infix);
    free(temp);

    int i;
    strcpy(postfix, "");
    char token[2];

    for(i=0; infix[i]!='\0'; i++){
        token[0] = infix[i];
        token[1] = '\0';
        printf("\nToken read from infix expression: %s\n", token);

        if(token[0]=='('){               // opening brace
            pushchr(oprtorstk,token[0]);
        }

        else if(token[0]>='A'&& token[0]<='z'){        // operand
            strcat(postfix, token);
        }

        else if(token[0]=='+'||token[0]=='-'||token[0]=='*'||token[0]=='/'||token[0]=='$'){  // known operator
            if(isEmptychr(oprtorstk)==1){      // e.g. after reading 1 of 2 brackets:    (a+b-c*d) / (e/f/g-h+i)
                pushchr(oprtorstk, token[0]);
            }
            else{
                char peekedoprtor;
                peekchr(oprtorstk, &peekedoprtor);
                printf("Operator visible on peeking into stack of operators: %c\n", peekedoprtor);

                if(token[0]=='$'){                // new operator read is '$'
                    pushchr(oprtorstk, token[0]);   // since it has the highest precedence, no need to compare with previous operator
                }

                else if(token[0]=='/'||token[0]=='*'){     // new operator read is '/' or '*'
                    if(peekedoprtor=='+'||peekedoprtor=='-'|| peekedoprtor=='('){
                        pushchr(oprtorstk, token[0]);
                    }

                    else if(peekedoprtor=='*' || peekedoprtor=='/' || peekedoprtor=='$'){  // redundant, can use just 'else'
                        char poppedoprtor;
                        char poppedoprtor_str[2];
                        int flag;
                        do{
                            popchr(oprtorstk, &poppedoprtor);
                            poppedoprtor_str[0] = poppedoprtor;
                            poppedoprtor_str[1] = '\0';
                            strcat( postfix, poppedoprtor_str);
                            displaychr(oprtorstk);
                            flag = peekchr(oprtorstk, &peekedoprtor);
                            if(flag==1){ printf("Operator visible on peeking into stack of operators: %c\n", peekedoprtor); }
                        }
                        while(flag==1 && (peekedoprtor=='*' || peekedoprtor=='/' || peekedoprtor=='$') );
                        pushchr(oprtorstk,token[0]);
                    }
                }

                else if(token[0]=='+'||token[0]=='-'){  // new operator read is '+' or '-'
                    char poppedoprtor;
                    char poppedoprtor_str[2];
                    int flag=1;
                    while(flag==1 && peekedoprtor!='('){    // note that peekedoprtor is declared and defined above case where token is $
                        popchr(oprtorstk, &poppedoprtor);
                        poppedoprtor_str[0] = poppedoprtor;
                        poppedoprtor_str[1] = '\0';
                        strcat( postfix, poppedoprtor_str);
                        flag = peekchr(oprtorstk, &peekedoprtor);
                        displaychr(oprtorstk);
                        if(flag==1){ printf("Operator visible on peeking into stack of operators: %c\n", peekedoprtor); }
                    }
                    pushchr(oprtorstk,token[0]);
                }
            }
        }

        else if(token[0]==')'){
            char peekedoprtor;
            peekchr(oprtorstk, &peekedoprtor);
            printf("Operator visible on peeking into stack of operators: %c\n", peekedoprtor);

            char poppedoprtor;
            char poppedoprtor_str[2];

            while(peekedoprtor!='('){
                popchr(oprtorstk, &poppedoprtor);
                poppedoprtor_str[0] = poppedoprtor;
                poppedoprtor_str[1] = '\0';
                strcat(postfix, poppedoprtor_str);

                printf("\nPostfix expression constructed till now:  %s\n", postfix);
                displaychr(oprtorstk);

                peekchr(oprtorstk, &peekedoprtor);
                printf("Operator visible on peeking into stack of operators: %c\n", peekedoprtor);
            }

            popchr(oprtorstk, &poppedoprtor);

            printf("\nPostfix expression constructed till now:  %s\n", postfix);
            displaychr(oprtorstk);

        }

        else{
            printf("\nUnknown token found in the entered infix expression.\n");
            break;
        }

        printf("\nPostfix expression constructed till now:  %s\n", postfix);
        displaychr(oprtorstk);

    }


}

//a/b$(c+d*e-(f$g*h/i/(j+k$l)+m*n)$o/p)*q$r$s      =>      abcde*+fg$h*i/jkl$+/mn*+o$p/-$/qrs$$*
//          = ((a/(b$((c+(d*e))-(((((((f$g)*h)/i)/(j+(k$l)))+(m*n))$o)/p))))*(q$(r$s)))
// obtained from postfixtoinfix program if you convert above postfix to infix (extraneous brackets necessary since precedence not defined in postfix->infix program

//(a/(b+c)+d)$e  =>  abc+/d+e$
