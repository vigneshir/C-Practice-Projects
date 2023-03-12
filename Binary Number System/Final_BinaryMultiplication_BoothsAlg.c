// if you want a function that returns the answer string pointer to an argument, there are 2 equivalent ways:
//
// 1) Declare an additional char *answerpointer (it is not an array name - refer next line) as formal parameter and in function definition
//    at end copy answer string to answerpointer using strcpy().
//    In function call you will pass char *result after assigning to 'result' a copy of pointer to sufficient heap memory to hold all characters + '\0'
//    using malloc().
//    e.g.: sign_extension() in this program
//
// 2) Declare an additional char **answerpointer [or address of char *answerpointer (pointer that points to block assigned using malloc)] as formal parameter
//    and in function definition assign desired characters to *answerpointer[i] or entire string to *answerpointer.
//    In function call you will pass &result where 'result' is a char * copy of pointer pointing to sufficient memory in heap, obtained by malloc()
//    e.g.: twos_comp(), add(), Arith_RShift() in this program
//
//    NOTE: malloc() returns a pointer variable pointing to allocated block of memory in HEAP.
//          We assign a copy of this pointer to a pointer variable (char *variable) declared by us (of name of our choice). This variable POINTS
//          TO the same BLOCK IN HEAP.
//          But this variable itself is STORED IN STACK, i.e. &variable is a location in STACK. It just 'contains' (i.e. its 'value' is) the
//          address of first cell in block in HEAP.
//          So, we pass &variable (stack location where pointer variable's content is stored) to function, i.e. char **variable as argument.
//              And in function body we either assign required string to *variable (indirection operator) using "string" or assign chrs
//              on chr-by-chr basis using indexing like (*variable)[i].

// 'Passing an answerstring-holder' to function becomes necessary because, instead, if an answerstring-holder pointer is declared and assigned to in the
// function body itself and this pointer returned by the function, then effectively the function returns a destroyed pointer,
// i.e. a pointer which may or may not still be pointing to the same location,
// since all variables declared in a function are 'auto' - they get destroyed after function returns.

// IMPORTANT: Stick to only 1 approach for all functions. Here both used just for demonstration.


// ??????????should you pass char[] or char * as function argument ????????

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

void Dec_To_2sCompBin(int n, int num, char *twos_comp_bin);  // should add 0 as sign extension to first bit if number positive but first bit 1 initially 1 (overflow)
void sign_extension( int n, char num[], char *sign_extended );
void twos_comp( int n, char num[], char **twos_complement );
void add( int n, char n1[], char n2[], char **addrsum );
void twoscompBin_To_Dec ( char twoscompbin[], int *ptrdec );
void Arith_RShift( int n, char **addrA, char **addrQ, char **addrQ_1);
void BoothImplm( int n, char n1[], char n2[]);



void main(){
    int n1, n2, n;

    printf("Enter the decimal numbers (representable by max 16 bits in 2's complement binary form) to be multiplied (multiplicand multiplier): ");
    scanf("%d %d",&n1,&n2);
    printf("Enter number of bits to be used in the algorithm: ");
    scanf("%d",&n);

    char *m_cand = (char *)malloc((n+1)*sizeof(char));
    char *m_plier= (char *)malloc((n+1)*sizeof(char));

    Dec_To_2sCompBin(n,n1, m_cand);

    Dec_To_2sCompBin(n,n2, m_plier);

    BoothImplm(n,m_cand,m_plier);

    free(m_cand);
    free(m_plier);

    return;

}

void Dec_To_2sCompBin(int n, int num, char *twos_comp_bin){
    if (num>0){
        char answer[17];                // this function can 'store' max 16 bit binaries, but can 'calculate' any binary form.
        answer[16]='\0';

        int i=15, unsigned_digits, index_first_garbage_bit ;
        int tempnum = num;
        while(tempnum>0){
            (tempnum%2 == 0)?(answer[i]='0'):(answer[i]='1');
            tempnum /= 2;
            i--;
        }

        // now answer[i] contains garbage value, number of unsigned digits = 15-i

        index_first_garbage_bit = i;  // used so that current value in i can be preserved and i freed for other work

        unsigned_digits = 15-i; // number of digits obtained by double dabble

        int index_first_useful_digit , orig_answer_length;

        if (answer[index_first_garbage_bit+1]=='1'){    // overflow, in this case no need to call twos_complement() since n>0, just ensure MSB = 0
            answer[index_first_garbage_bit]='0';
            orig_answer_length = unsigned_digits+1 ; // number of bits in 2s compl of the positive num
            index_first_useful_digit = index_first_garbage_bit;
        }
        else{
            orig_answer_length = unsigned_digits;
            index_first_useful_digit = index_first_garbage_bit+1;
        }                           // orig_answer_length= number of digits obtained by double-dabble

        if( n < orig_answer_length ){ printf("\nNumber of bits entered insufficient to represent the binary of the decimal number %d or %d.\n",num,-1*num); exit(-1);}
        else{
            // truncate garbage values (index 0 to i-1) and give remaining digits to sign_extension
            char cleaned2scomp[orig_answer_length+1] ;
            cleaned2scomp[orig_answer_length]='\0';

            for(i=index_first_useful_digit; i<17; i++){
                cleaned2scomp[i-index_first_useful_digit]= answer[i];
            }

            sign_extension(n,cleaned2scomp, twos_comp_bin);

            return ;
        }
    }
    else if (num==0) { for(int i=0; i<4;i++){ twos_comp_bin[i]='0';}  twos_comp_bin[4]='\0' ; }
    else{   // i.e. if num<0
        int mod_num = -1*num ;

        char *bin_mod_num = (char *)malloc((n+1)*sizeof(char));
        char *bin_num = (char *)malloc((n+1)*sizeof(char));

        Dec_To_2sCompBin(n, mod_num, bin_mod_num);  // bin_mod_num = binary form of mod_num so that it can be passed to 2s_comp() to find its 2s complement

        twos_comp( n, bin_mod_num, &bin_num );  // bin_num will now contain 2s complement binary of mod_num, i.e. binary of n (since n<0)
        free(bin_mod_num);

        sign_extension(n, bin_num, twos_comp_bin); // final decoration: n bits long binary of entered n
        free(bin_num);

        return ;
    }

}




void sign_extension( int n, char num[], char *sign_extended ){  // returns a (2's complement system) binary number of n bits
    if (n < strlen(num)){ printf("\nError! Number of bits in result cannot be less than that in either operand.\n"); exit(-1); }
 //   else if (n==strlen(num)){ return num;}
    else{
        char *extension = (char *)malloc( (n+1)*sizeof(char) );       // actual length of sign_extension = ( n - strlen(num) ) digits + '\0' but later concatenation
        for(int i=0;i<n-strlen(num);i++){
            extension[i]=num[0];
        }
        extension[n-strlen(num)]='\0'; // till here 'extension' contains only the extended part, not the entire number
        strcat(extension,num);          // now 'extension' contains entire number along with extended part
        strcpy(sign_extended, extension);

        free(extension);

        return;
    }
}

void twos_comp( int n, char num[], char **twos_complement ){  // accepts binary of number whose two's compl is to be found

    //char numf[n+1];
    char *sign_extended = (char *)malloc((n+1)*sizeof(char));
    sign_extension(n,num,sign_extended);

    int i=n-1;
    for( ;sign_extended[i]=='0';i--){
        (*twos_complement)[i]=sign_extended[i];  // these digits are 0
    }
    (*twos_complement)[i--]='1';

    for(;i>=0;i--){
        if (sign_extended[i]=='0'){ (*twos_complement)[i]='1'; }
        else {(*twos_complement)[i]='0';}
    }
    (*twos_complement)[n]='\0';

    free(sign_extended);

    return;

}

void add( int n, char *n1, char *n2, char **addrsum ){

    int i;

    char *sxtendn1 = (char*)malloc((n+1)*sizeof(char));
    char *sxtendn2 = (char*)malloc((n+1)*sizeof(char));

    sign_extension(n,n1,sxtendn1);
    sign_extension(n,n2,sxtendn2);

    // free signextended n1 and n2

    static char carry;
    carry = '0';
    for(i=n-1 ; i>=0; i--){

        switch ( (sxtendn1[i]-'0') + (sxtendn2[i]-'0') ){
            case 0 : // 0 and 0
                (*addrsum)[i]=carry;
                carry='0';
                break;

            case 1: // 0 and 1  or 1 and 0
                if (carry == '1'){   // sum = 10
                    (*addrsum)[i]='0';
                    //carry='1';
                }
                else if (carry == '0'){  // sum=0
                    (*addrsum)[i]='1';
                    //carry='0';
                }
                break;

            case 2:  // 1 and 1
                if (carry=='1'){
                    (*addrsum)[i]='1';
                }
                else if (carry=='0'){
                    (*addrsum)[i]='0';
                }
                carry='1';
                break;

        }
    }
    (*addrsum)[n]='\0';

    free(sxtendn1);
    free(sxtendn2);

    return ;
}


void Arith_RShift( int n, char **addrA, char **addrQ, char **addrQ_1){   // n is the number of bits in A and Q
    char temp_A[n+2], temp_Q[n+2];

    temp_A[0] = (*addrA)[0];
    temp_A[1] = '\0';

    temp_Q[0] = (*addrA)[n-1];
    temp_Q[1] = '\0';

    **addrQ_1 = (*addrQ)[n-1];

    strncat( temp_A, *addrA, n-1 ); // note that the function automatically appends '\0' at end

    strcpy( *addrA, temp_A );

    strncat( temp_Q, *addrQ, n-1 ); // note that the function automatically appends '\0' at end

    strcpy( *addrQ, temp_Q );

}

void twoscompBin_To_Dec ( char twoscompbin[], int *ptrdec ){
    int i, ln;

    ln = strlen(twoscompbin);  // in this program strlen unnecessary since arguments of twoscomp_Bin_To_Dec() in this program will always be n

    *ptrdec = 0;
    for (i=ln-1;i>=1;i--){
        if (twoscompbin[i]=='1'){
            *ptrdec += (int) pow(2.0,(float)(ln-1-i));
        }
    }
    if (twoscompbin[0]=='1'){
        *ptrdec -= (int) pow(2.0,(float)(ln-1));
    }

    return;
}

void BoothImplm( int n, char m_cand[], char m_plier[]){
    int i, count = n; char *temp;

    char *A = (char *)malloc((n+1)*sizeof(char));
    for (i=0; i<n; i++){ A[i]='0';}
    A[n]='\0';

    char *Q = (char *)malloc((n+1)*sizeof(char));
    strcpy(Q, m_plier);

    char *Q_1 = (char *)malloc(sizeof(char));
    *Q_1 = '0';

    char *M = (char *)malloc((n+1)*sizeof(char));
    strcpy( M, m_cand);

    char *twos_complementM = (char *)malloc((n+1)*sizeof(char));
    twos_comp(n,M,&twos_complementM);
    printf("\nM = %s\t-M = %s\n", M, twos_complementM);
    printf("Q = %s\n\n",m_plier);

    printf("%22s %18s %18s %10s %10s\n\n", "Operation", "A", "Q", "Q_1", "n");

    char op[32] = "Initialization";
    printf("%22s %18s %18s %10c %10d\n" , op, A, Q, *Q_1, n);

    for(count=n; count>0; ){
        if ( Q[n-1]==*Q_1 ){ ; }

        else if ( Q[n-1]=='1' && *Q_1=='0'){
            char *diff = (char *)malloc((n+1)*sizeof(char));
            add(n,A,twos_complementM,&diff);  // can you free(diff) without affecting further program ?
            strcpy(A,diff);
            free(diff);
            printf("%22s %18s %18s %10c %10d\n", "A <- A-M", A, Q, *Q_1, count);
        }

        else if ( Q[n-1]=='0' && *Q_1=='1'){
            char *sum = (char *)malloc((n+1)*sizeof(char));
            add(n,A,M,&sum);
            strcpy(A,sum);
            free(sum);
            printf("%22s %18s %18s %10c %10d\n", "A <- A+M", A, Q, *Q_1, count);
        }

        Arith_RShift(n, &A, &Q, &Q_1);
        --count;
        printf("%22s %18s %18s %10c %10d\n", "Arithmetic Right Shift", A, Q, *Q_1, count);
    }

    char * result = (char *)malloc((2*n+1)*sizeof(char));
    strcpy(result,A);
    strcat(result,Q);
    printf("\n\nProduct in binary system = %s\n" , result);
    int dec;
    twoscompBin_To_Dec(result, &dec);
    printf("Product in decimal form = %d\n\n" , dec);

    free(A); free(M); free(Q); free(Q_1); free(result); free(twos_complementM);

    return;
}















