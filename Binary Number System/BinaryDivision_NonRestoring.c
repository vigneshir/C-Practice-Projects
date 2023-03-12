#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

void Dec_To_2sCompBin(int num, char *twos_comp_bin);
void twos_comp( char *num, char *twos_complement );
void LeftShift( char *A, char *Q);
void bin_add( char *n1, char *n2, char *sum );
int UnsignedBin_To_Dec ( char *unsignedbin );
void BinDiv_NonRestoring( char *Q, char *M);

void main(){
    int divd, divr;
    printf("Enter the positive decimal dividend and divisor: ");
    scanf("%d %d", &divd, &divr);
    char *Q = (char *)malloc( 25*sizeof(char));
    char *M = (char *)malloc( 25*sizeof(char));
    Dec_To_2sCompBin(divd, Q);
    Dec_To_2sCompBin(divr, M);

    BinDiv_NonRestoring( Q, M);

    free(Q); free(M);
    return;
}


void Dec_To_2sCompBin(int num, char *twos_comp_bin){
    if (num>0){
        char answer[25];                // this function can 'store' max 16 bit binaries, but can 'calculate' any binary form.
        answer[24]='\0';
        int i=23, unsigned_digits, index_first_garbage_bit ;
        int tempnum = num;
        while(tempnum>0){
            (tempnum%2 == 0)?(answer[i]='0'):(answer[i]='1');
            tempnum /= 2;
            i--;
        }

        // now answer[i] contains garbage value, number of unsigned digits = 15-i

        index_first_garbage_bit = i;  // used so that current value in i can be preserved and i freed for other work

        unsigned_digits = 24-i; // number of digits obtained by double dabble

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

        // truncate garbage values (index 0 to index_first_useful_digit-1) and give remaining digits to twos_comp_bin
        for(i=index_first_useful_digit; i<25; i++){
            twos_comp_bin[i-index_first_useful_digit] = answer[i];
        }

        return ;
    }
    else if (num==0) { for(int i=0; i<4;i++){ twos_comp_bin[i]='0';}  twos_comp_bin[4]='\0' ; }
    else{   // i.e. if num<0
        printf("\nNon-Restoring Division algorithm cannot be applied on negative dividends or divisors and zero divisor.\n\n");
        exit(-1);
    }

}

void twos_comp( char num[], char *twos_complement ){  // accepts binary of number whose two's compl is to be found

    int n = strlen(num);
    int i=n-1;
    for( ;num[i]=='0';i--){
        twos_complement[i]=num[i];  // these digits are 0
    }
    twos_complement[i--]='1';

    for(;i>=0;i--){
        if (num[i]=='0'){ twos_complement[i]='1'; }
        else { twos_complement[i]='0' ; }
    }
    twos_complement[n]='\0';

    return;
}

void LeftShift( char *A, char *Q){
    int i;
    int n = strlen(A);
    for(i=0;i<n-1;i++){ A[i] = A[i+1] ; }
    A[n-1]=Q[0];
    for(i=0;i<n-1;i++){ Q[i] = Q[i+1] ; }
    Q[n-1]='_';
    A[n] = '\0';
    Q[n] = '\0';

    return;
}

void bin_add( char *n1, char *n2, char *sum ){

    int i;
    int n = strlen(n1);  // = strlen(n2)
    //printf("\nInside add(). n = %d\n", n);
    static char carry;
    carry = '0';
    for(i=n-1 ; i>=0; i--){

        switch ( (n1[i]-'0') + (n2[i]-'0') ){
            case 0 : // 0 and 0
                //printf("\nReached 0 and 0 sum case.   ");
                //printf("\nsum[%d] = %c", i, sum[i]);
                sum[i]=carry;
                carry='0';
                //printf("sum[i] = %c\n", sum[i]);
                break;

            case 1: // 0 and 1  or 1 and 0
                if (carry == '1'){   // sum = 10
                    sum[i]='0';
                    //carry='1';
                }
                else if (carry == '0'){  // sum=0
                    sum[i]='1';
                    //carry='0';
                }
                break;

            case 2:  // 1 and 1
                if (carry=='1'){
                    sum[i]='1';
                }
                else if (carry=='0'){
                    sum[i]='0';
                }
                carry='1';
                break;

        }
    }
    sum[n]='\0';
    //printf("\nsum inside add() = %s\n", sum);

    return ;
}

int UnsignedBin_To_Dec ( char *unsignedbin ){
    int i, ln, dec=0;

    ln = strlen(unsignedbin);  // number of 'digits' in unsignedbin (excluding '\0').   unsignedbin[ln] = '\0'

    for (i=ln-1;i>=0;i--){
        if (unsignedbin[i]=='1'){
            dec += (int) pow(2.0,(float)(ln-1-i));
        }
    }
    return dec;

}

void BinDiv_NonRestoring( char *Q, char *M){
    int m = strlen(M);
    int n = strlen(Q);
    int i, count=n;

    if(m < n){
        char *padded = (char *)malloc((n+1)*sizeof(char));
        for(i=0;i<n-m;i++){ padded[i] = '0';}
        padded[n-m]='\0';
        strcat(padded, M);
        strcpy(M,padded);
        free(padded);
    }
    else if (m > n){
        printf("\n Quotient = 0000  (unsigned binary)  or  0 (decimal)\nRemainder = %s  (unsigned binary)  or  %d (decimal)\n\n", Q,UnsignedBin_To_Dec(Q));
        return;
    }

    char *A = (char *)malloc((n+1)*sizeof(char));
    for(i=0; i<n; i++){ A[i]='0'; }
    A[n]='\0';

    char *twos_comp_M = (char *)malloc((n+1)*sizeof(char));
    twos_comp(M, twos_comp_M);

    printf("\nDividend (Q) = %s\nDivisor (M) = %s\t\t-M = %s\n", Q, M, twos_comp_M);
    printf("\n%25s%28s%28s%10s\n", "Operation","A","Q","Count");
    printf("\n%25s%28s%28s%10d", "Initialization", A, Q, count);

    char *temp = (char *)malloc((n+1)*sizeof(char));

    while(count>0){
        if ( A[0]=='0'){
            LeftShift(A,Q);
            printf("\n%25s%28s%28s%10d", "Left Shift A, Q", A, Q, count);
            bin_add(A, twos_comp_M, temp);
            strcpy(A, temp);
            printf("\n%25s%28s%28s%10d", "A <- A-M", A, Q, count);
        }
        else if ( A[0]=='1'){
            LeftShift(A,Q);
            printf("\n%25s%28s%28s%10d", "Left Shift A, Q", A, Q, count);
            bin_add(A, M, temp);
            strcpy(A, temp);
            printf("\n%25s%28s%28s%10d", "A <- A+M", A, Q, count);
        }
        if (A[0]=='0'){
            Q[n-1]='1';
            printf("\n%25s%28s%28s%10d", "Q_0 <- 1", A, Q, --count);
        }
        else if (A[0]=='1'){
            Q[n-1]='0';
            printf("\n%25s%28s%28s%10d", "Q_0 <- 0", A, Q, --count);
        }
    }
    if (A[0]=='0'){;}
    else if (A[0]=='1'){
        bin_add(A,M,temp);
        strcpy(A, temp);
        printf("\n%25s%28s%28s%10d", "A <- A+M", A, Q, count);
    }
    free(temp);

    printf("\n\nUnsigned Binary -   Quotient Q = %s     Remainder A = %s", Q, A);
    printf(  "\n        Decimal -   Quotient Q = %*d     Remainder A = %*d\n\n", n, UnsignedBin_To_Dec(Q), n, UnsignedBin_To_Dec(A));

    return;

}
