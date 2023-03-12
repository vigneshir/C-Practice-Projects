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

void prefix_to_postfix( char *prefix, char *postfix);


void main(){
    char response[10] ;
    for( ; ; ){
        printf("\nWant to convert a prefix expression to a postfix expression? ");
        scanf("%s",response);
        if(strcmp(response, "yes")==0){
            char *prefix = (char *)malloc(sizeof(char)*200);          // expects max 149 tokens in prefix
            printf("\nEnter the prefix expression to be converted to a postfix expression:\n");
            scanf("%s", prefix);

            char *postfix = (char *)malloc(sizeof(char)*150);      // expects max 149 tokens in postfix

            prefix_to_postfix(prefix, postfix);
            printf("\nEquivalent postfix expression:\n");
            printf("%s\n\n", postfix);

            free(prefix); free(postfix);
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



void prefix_to_postfix( char *prefix, char *postfix){
    struct str_stack *solstk = create_strstack(150);
    int i;
    char token_str[2], tempstr[150];
    char *popped_oprnd1 = (char *)malloc(sizeof(char)*150);
    char *popped_oprnd2 = (char *)malloc(sizeof(char)*150);

    for(i=strlen(prefix)-1; i>=0; i--){
        token_str[0]=prefix[i];
        token_str[1]='\0';
        printf("\nToken read : %s", token_str);

        if(prefix[i]>='A' && prefix[i]<='z'){
            pushstr(token_str, solstk);
        }
        else{
            popstr(solstk, popped_oprnd1);
            popstr(solstk, popped_oprnd2);
            strcpy(tempstr, popped_oprnd1);
            strcat(tempstr, popped_oprnd2);
            strcat(tempstr, token_str);
            pushstr(tempstr, solstk);
        }
        displaystr(solstk);
    }
    strcpy(postfix, solstk->ptr_charptr[0]);
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
