/* #strcmp, #strcat, , #strlen, #strcpy, #strncpy, #strrev, #check string2 substring of 1 if yes return first matching position, #slicing,
    #frequency of substring in main string */

#include<stdio.h>
#include<stdlib.h>

int lengthstr( char *str );
int cmpstr( char *str1, char *str2 );   // 1 if equal
void concatstr( char *str1, char *str2 );
void cpystr( char *str1, char *str2);
void cpystrn( char *str1, char *str2, int n );
void revstr( char *str ); // reverses original string, without creating new string
int substr( char *str1, char *str2); // -1 if not found, otherwise index of first matching letter
int freq_substr( char *str1, char *str2);
void slicestr( char *str1, int startindex, int excl_endindex, char* sliced);

void main(){
    printf("--------String ADT--------\n\n");
    printf("String Operations:\n");
    printf("1. Find the length of the string.\n");
    printf("2. Compare two strings (returns 1 for equal strings and 0 otherwise).\n");
    printf("3. Concatenate one string to another.\n");
    printf("4. Copy one entire string to another.\n");
    printf("5. Copy first 'n' letters from one string to another.\n");
    printf("6. Reverse a string.\n");
    printf("7. Check if a substring is present in the main string (returns -1 if absent, index of first character of substring in main string otherwise).\n");
    printf("8. Find the frequency of occurrence of a substring in the main string.\n");
    printf("9. Obtain a sliced string.\n\n");

    int choice;

    for(;;){
        printf("Enter the operation to be performed (enter -1 to exit): ");
        scanf("%d", &choice);
        switch(choice){
            case 1:{
                char *str = (char*)malloc(500*sizeof(char));
                printf("Enter the string whose length is to be found: ");
                scanf("%s", str);
                printf("Length of string = %d\n\n",lengthstr(str));
                free(str);
                break;
            }

            case 2:{
                char *str1 = (char*)malloc(500*sizeof(char));
                char *str2 = (char*)malloc(500*sizeof(char));
                printf("Enter first string: ");
                scanf("%s",str1);
                printf("Enter second string: ");
                scanf("%s",str2);
                printf("Result: %d\n\n",cmpstr(str1, str2));
                free(str1); free(str2);
                break;
            }

            case 3:{
                char *str1 = (char*)malloc(500*sizeof(char));
                char *str2 = (char*)malloc(500*sizeof(char));
                printf("Enter base string: ");
                scanf("%s",str1);
                printf("\nEnter string to be concatenated: ");
                scanf("%s",str2);
                concatstr(str1, str2);
                printf("Result of concatenation: %s\n\n",str1);
                free(str1); free(str2);
                break;
            }

            case 4:{
                char *str1 = (char*)malloc(500*sizeof(char));
                char *str2 = (char*)malloc(500*sizeof(char));
                printf("Enter base string: ");
                scanf("%s",str1);
                printf("\nEnter string to be copied: ");
                scanf("%s",str2);
                cpystr(str1, str2);
                printf("Result after copying: string 1 = %s\n\n",str1);
                free(str1); free(str2);
                break;
            }

            case 5:{
                char *str1 = (char*)malloc(500*sizeof(char));
                char *str2 = (char*)malloc(500*sizeof(char));
                int n;
                printf("Enter base string: ");
                scanf("%s",str1);
                printf("Enter string containing characters to be copied: ");
                scanf("%s",str2);
                printf("Enter number of characters of second string to be copied: ");
                scanf("%d", &n);
                cpystrn(str1, str2,n);
                printf("Result: str1 = %s\n\n",str1);
                free(str1); free(str2);
                break;
            }

            case 6:{
                char *str = (char*)malloc(500*sizeof(char));
                printf("Enter the string to be reversed: ");
                scanf("%s", str);
                revstr(str);
                printf("Reversed string = %s\n\n",str);
                free(str);
                break;
            }

            case 7:{
                char *str1 = (char*)malloc(500*sizeof(char));
                char *str2 = (char*)malloc(500*sizeof(char));
                int n;
                printf("Enter main string: ");
                scanf("%s",str1);
                printf("Enter substring to be searched: ");
                scanf("%s",str2);
                printf("Result: %d\n\n",substr(str1, str2));
                free(str1); free(str2);
                break;
            }

            case 8:{
                char *str1 = (char*)malloc(500*sizeof(char));
                char *str2 = (char*)malloc(500*sizeof(char));
                int n;
                printf("Enter main string: ");
                scanf("%s",str1);
                printf("Enter substring to be searched: ");
                scanf("%s",str2);
                printf("Frequency of substring in main string: %d\n\n",freq_substr(str1, str2));
                free(str1); free(str2);
                break;
            }

            case 9:{
                char *str = (char*)malloc(500*sizeof(char));
                char *sliced = (char *)malloc(500*sizeof(char));
                int startindex, excl_endindex;
                printf("Enter the main string: ");
                scanf("%s", str);
                printf("Enter the starting index and exclusive final index of sliced string: ");
                scanf("%d %d", &startindex, &excl_endindex);
                slicestr(str, startindex, excl_endindex, sliced);
                printf("Sliced string = %s\n\n",sliced);
                free(str); free(sliced);
                break;
            }

            case -1:
                printf("Exiting...\n\n");
                exit(0);

            default:
                printf("Please enter the correct number.\n\n");
        }

    }
}


int lengthstr( char *str ){
    int i=0;
    while(str[i]!='\0'){ i++; }
    return i;
}

int cmpstr( char *str1, char *str2 ){
    int i;
    for(i=0; ;i++){
        if(str1[i]==str2[i]){
            if(str1[i]=='\0'){ return 1; }
        }
        else{ return 0; }
    }
}

void concatstr( char *str1, char *str2 ){
    int i, p=lengthstr(str1);
    for(i=p; str2[i-p]!='\0'; i++){
        str1[i]=str2[i-p];
    }
    str1[i]='\0';
}

void cpystr( char *str1, char *str2){
    int i, p=lengthstr(str2);
    for(i=0; i<=p; i++){ str1[i] = str2[i]; }
}

void cpystrn( char *str1, char *str2, int n){
    int i;
    for(i=0; i<n; i++){ str1[i] = str2[i]; }
    str1[i]='\0';
}

void revstr( char *str ){
    int i, p=lengthstr(str); char temp;
    if(p>1){
        for(i=0;i<p/2;i++){
            temp=str[i];
            str[i]=str[p-1-i];
            str[p-1-i]=temp;
        }
    }
}

int substr( char *str1, char *str2 ){

    int i,j, strlen_mainstr=lengthstr(str1), strlen_substr=lengthstr(str2);

    for(i=0, j=0; i<strlen_mainstr, j!=strlen_substr; i++){
        if(str2[j]==str1[i]){
            j++;
        }
        else{
            if(j>0){ i=i-1; }
            j=0;
            if(i>=strlen_mainstr-strlen_substr){ break; }
        }
    }
    if (j==strlen_substr){
        return i-strlen_substr;
    }
    else{
        return -1;
    }

}

int freq_substr( char *str1, char *str2 ){
    int i, j, count=0, strlen_mainstr=lengthstr(str1), strlen_substr=lengthstr(str2);

    for(i=0, j=0; i<strlen_mainstr; i++){
        if(str2[j]==str1[i]){
            j++ ;
            if (j==strlen_substr){
                ++count;
                j=0;
                i=i-1;
            }
        }
        else{
            if(j>0){ i=i-1; }
            j=0;
            if(i>=strlen_mainstr-strlen_substr){ break; }
        }
    }

    return count;
}

void slicestr( char *str1, int startindex, int excl_endindex, char *sliced){
    if( startindex<0 || startindex>lengthstr(str1)-1 || excl_endindex<0 || excl_endindex>lengthstr(str1)){ printf("Invalid index\n\n."); }
    if(startindex>excl_endindex){ printf("End index should be greater than start index. If required, reverse the string separately.\n\n"); }
    else{
        int i;
        for(i=startindex; i<excl_endindex; i++){
            sliced[i-startindex]=str1[i];
        }
    }
}
