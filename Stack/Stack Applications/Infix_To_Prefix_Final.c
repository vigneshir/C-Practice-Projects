// Assumed Precedence or Arithmetic Operators:
//       $              Exponentiation
//      / *             Division   Multiplication
//      + -             Addition   Subtraction
// Same priority operators adjacent to each other are evaluated from left to right, except for $
// Adjacent $ operations are evaluated from right to left.  E.g.:  a$b$c = a$(b$c)


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct str_stack{
    int MAXSIZE;
    int top;
    char **ptr_charptr;
};

struct str_stack *create_strstack(int maxsize);
int isEmptystr(struct str_stack *ptr_strstack);
int isFullstr(struct str_stack *ptr_strstack);
int pushstr(char *new_elem, struct str_stack *ptr_strstack);
int popstr(struct str_stack *ptr_strstack, char *popped);
int peekstr(struct str_stack *ptr_strstack, char *peeked);
int displaystr(struct str_stack *ptr_strstack);
void destroystr(struct str_stack *ptr_strstack);

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

void infix_to_prefix(char *infix, char *prefix);

void main(){
    char response[10] ;
    for( ; ; ){
        printf("\nWant to convert an infix expression to a prefix expression? ");
        scanf("%s",response);
        if(strcmp(response, "yes")==0){
            char *infix = (char *)malloc(sizeof(char)*200);          // expects max 149 tokens in infix
            printf("\nEnter the infix expression to be converted to a prefix expression:\n");
            scanf("%s", infix);

            char *prefix = (char *)malloc(sizeof(char)*150);      // expects max 149 tokens in prefix

            infix_to_prefix(infix, prefix);
            printf("\nEquivalent prefix expression:\n");
            printf("%s\n\n", prefix);

            free(prefix); free(infix);
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


struct str_stack *create_strstack(int maxsize){
    struct str_stack *ptr_strstack = (struct str_stack *)malloc(sizeof(struct str_stack));
    ptr_strstack -> MAXSIZE = maxsize;
    ptr_strstack -> top = -1;
    ptr_strstack -> ptr_charptr = (char **)malloc(maxsize*sizeof(char *));

    return ptr_strstack;
}

int isEmptystr(struct str_stack *ptr_strstack){
    if(ptr_strstack->top==-1){ return 1; }
    else{ return -1; }
}

int isFullstr(struct str_stack *ptr_strstack){
    if(ptr_strstack->top == (ptr_strstack->MAXSIZE)-1){ return 1; }
    else{ return -1; }
}

int pushstr(char *new_elem, struct str_stack *ptr_strstack){
    if(isFullstr(ptr_strstack) == 1){return -1; }
    else{
        ptr_strstack->ptr_charptr[++(ptr_strstack->top)] = (char *)malloc(sizeof(char)*(strlen(new_elem)+1));
        strcpy( ptr_strstack->ptr_charptr[ptr_strstack->top] , new_elem ) ;

        return 1;
    }
}


int popstr(struct str_stack *ptr_strstack, char *popped){
    if(isEmptystr(ptr_strstack)==1){ return -1 ; }
    else{
        popped[0] = '\0';
        strcpy(popped, ptr_strstack->ptr_charptr[(ptr_strstack->top)--]);
        free(ptr_strstack->ptr_charptr[ (ptr_strstack->top)+1 ]);
        return 1;
    }
}

int peekstr(struct str_stack *ptr_strstack, char *peeked){
    if(isEmptystr(ptr_strstack)==1){ return -1 ; }
    else{
        peeked[0]='\0';
        strcpy( peeked, ptr_strstack->ptr_charptr[(ptr_strstack->top)] );
        return 1;
    }
}

int displaystr(struct str_stack *ptr_strstack){
    if(isEmptystr(ptr_strstack)==1){ return -1; }
    else{
        int i;
        printf("\nSolution Stack Contents:\n");
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

void destroystr(struct str_stack *ptr_strstack){
    int i;
    for(i=0; i < ptr_strstack->top ; i++){
        free(ptr_strstack->ptr_charptr[i]);
    }
    free(ptr_strstack->ptr_charptr);
    free(ptr_strstack);
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
        printf("\nOperator stack contents:\n");
        printf(" |%3s|\n"," ");
        for( i=(*ptr_chrstack).top; i>=0; i--){
            printf( " | %c |\n",(*ptr_chrstack).elements[i] );
        }
        printf(" ");
        for(i=0;i<5;i++){ printf("%c",'-'); }
        return 1;
    }
}


void infix_to_prefix(char *infix, char *prefix){
    struct str_stack *solstk = create_strstack(20);
    struct chr_stack *oprtorstk = create_chrstack(50);

//    if(infix[0]!='('){     // problem when '(' present at start but not at end (but still valid infix):  e.g.:  (a/(b+c)+d)$e
                                               // so add '(' and ')' to every input expression, since extra braces won't foil the algorithm
        char *temp = (char *)malloc(sizeof(char)*200);
        temp[0]='\0';
        strcpy(temp, infix);
        infix[0]='(';
        infix[1]='\0';
        strcat(infix,temp);
        strcat(infix,")");
        printf("\nEntered Infix: %s\n", infix);
        free(temp);
//    }

    int i;
    char token[2];

    for(i=0; infix[i]!='\0'; i++){
        token[0] = infix[i];
        token[1] = '\0';
        printf("\nToken read: %s", token);

        if(token[0]=='('){      // opening brace
            pushchr(oprtorstk,token[0]);

            pushstr("",solstk);
// use only this method to put '\0' in new cell. Don't do as following commented out code after printf stmt,
// because the pointers to strings in the string stack are INITIALIZED (point to valid memory locations) only in the push().
//       Till then they point to random locations.

            //(solstk->ptr_charptr[solstk->top])[0] = '\0';
            //printf("\nAssigned null character to new top of solstk.\n");
        }

        else if(token[0]>='A'&& token[0]<='z'){  // operand
            pushstr(token, solstk);
        }

        else if(token[0]=='+'||token[0]=='-'||token[0]=='*'||token[0]=='/'||token[0]=='$'){  // known operator
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
                        char *oprnd1 = (char *)malloc(sizeof(char)*200);
                        char *oprnd2 = (char *)malloc(sizeof(char)*200);
                        int flag;
                        do{
                            popchr(oprtorstk, &poppedoprtor);
                            poppedoprtor_str[0] = poppedoprtor;
                            poppedoprtor_str[1] = '\0';
                            popstr(solstk, oprnd2);
                            popstr(solstk, oprnd1);
                            strcat(poppedoprtor_str, oprnd1);
                            strcat(poppedoprtor_str, oprnd2);
                            pushstr(poppedoprtor_str, solstk);

                            flag = peekchr(oprtorstk, &peekedoprtor);
                        }
                        while(flag==1 && (peekedoprtor=='*' || peekedoprtor=='/' || peekedoprtor=='$') );
                        pushchr(oprtorstk,token[0]);
                    }
                }

                else if(token[0]=='+'||token[0]=='-'){  // new operator read is '+' or '-'
                    char poppedoprtor;
                    char poppedoprtor_str[200];
                    char *oprnd1 = (char *)malloc(sizeof(char)*200);
                    char *oprnd2 = (char *)malloc(sizeof(char)*200);

                    int flag=1;
                    while(flag==1 && peekedoprtor!='('){    // note that peekedoprtor is declared and defined above case where token is $
                        popchr(oprtorstk, &poppedoprtor);
                        poppedoprtor_str[0] = poppedoprtor;
                        poppedoprtor_str[1] = '\0';
                        popstr(solstk, oprnd2);
                        popstr(solstk, oprnd1);
                        strcat(poppedoprtor_str, oprnd1);
                        strcat(poppedoprtor_str, oprnd2);
                        pushstr(poppedoprtor_str, solstk);

                        flag = peekchr(oprtorstk, &peekedoprtor);
                        displaystr(solstk);
                    }
                    pushchr(oprtorstk,token[0]);
                }
            }
        }

        else if(token[0]==')'){
            char peekedoprtor;
            peekchr(oprtorstk, &peekedoprtor);
            printf("\nPeeked Operator: %c\n", peekedoprtor);

            char poppedoprtor;
            char poppedoprtor_str[200];
            char *oprnd1 = (char *)malloc(sizeof(char)*200);
            char *oprnd2 = (char *)malloc(sizeof(char)*200);

            while(peekedoprtor!='('){
                popchr(oprtorstk, &poppedoprtor);
                poppedoprtor_str[0] = poppedoprtor;
                poppedoprtor_str[1] = '\0';

                popstr(solstk, oprnd2);
                popstr(solstk, oprnd1);
                strcat(poppedoprtor_str, oprnd1);
                strcat(poppedoprtor_str, oprnd2);
                pushstr(poppedoprtor_str, solstk);

                displaychr(oprtorstk);
                displaystr(solstk);
                peekchr(oprtorstk, &peekedoprtor);
                printf("\nPeeked Operator: %c", peekedoprtor);
            }

            popchr(oprtorstk, &poppedoprtor);
            displaychr(oprtorstk);

            if( (solstk->top)>=1 ){
                char *poppedexpr = (char *)malloc(150*sizeof(char));
                popstr(solstk, poppedexpr);
                strcat((solstk->ptr_charptr)[solstk->top], poppedexpr);
                displaystr(solstk);
                free(poppedexpr);
            }
        }

        else{
            printf("\nUnknown token found in the entered infix expression.\n");
            break;
        }

        displaychr(oprtorstk);
        displaystr(solstk);
    }
    strcpy(prefix, solstk->ptr_charptr[0]);
}
