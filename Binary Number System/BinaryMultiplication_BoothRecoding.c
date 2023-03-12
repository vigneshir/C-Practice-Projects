#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

void Dec_To_2sCompBin(int num, char *twos_comp_bin);  // modify so that min number of bits present
void twos_comp( char *num, char *twos_complement );
void add( char *n1, char *n2, char *sum );
int twoscompBin_To_Dec ( char *twoscompbin );
void BoothRecoding( char *m_cand, char *raw_m_plier);

void main(){
    int n1, n2;

    printf("Enter the decimal numbers (representable by max 16 bits in 2's complement binary form) to be multiplied (multiplicand multiplier): ");
    scanf("%d %d",&n1,&n2);

    char *m_cand = (char *)malloc(17*sizeof(char));
    char *raw_m_plier= (char *)malloc(17*sizeof(char));

    Dec_To_2sCompBin(n1, m_cand);
    Dec_To_2sCompBin(n2, raw_m_plier);

    BoothRecoding( m_cand, raw_m_plier);

    free(m_cand); free(raw_m_plier);

    return;
}


void Dec_To_2sCompBin(int num, char *twos_comp_bin){
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

        // truncate garbage values (index 0 to index_first_useful_digit-1) and give remaining digits to twos_comp_bin

        for(i=index_first_useful_digit; i<17; i++){
            twos_comp_bin[i-index_first_useful_digit] = answer[i];
        }
        twos_comp_bin[orig_answer_length]='\0';

        return ;

    }

    else{   // i.e. if num<0
        int mod_num = -1*num ;

        char *bin_mod_num = (char *)malloc(17*sizeof(char));

        Dec_To_2sCompBin(mod_num, bin_mod_num);  // bin_mod_num = binary form of mod_num so that it can be passed to 2s_comp() to find its 2s complement

        twos_comp( bin_mod_num, twos_comp_bin );  // bin_num will now contain 2s complement binary of mod_num, i.e. binary of n (since n<0)

        free(bin_mod_num);

        return ;
    }

}

void add( char *n1, char *n2, char *sum ){

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

int twoscompBin_To_Dec ( char twoscompbin[] ){
    int i, ln, dec_result=0;

    ln = strlen(twoscompbin);  // in this program strlen unnecessary since arguments of twoscomp_Bin_To_Dec() in this program will always be n

    for (i=ln-1;i>=1;i--){
        if (twoscompbin[i]=='1'){
            dec_result += (int) pow(2.0,(float)(ln-1-i));
        }
    }
    if (twoscompbin[0]=='1'){
        dec_result -= (int) pow(2.0,(float)(ln-1));
    }

    return dec_result;
}


void BoothRecoding( char *m_cand, char *raw_m_plier){
    int i,j,m,q;

    m = strlen(m_cand);

    printf("\n%20s: %s", "Multiplier (M)", m_cand);
    printf("\n%20s: %s\n\n", "Multiplicand (Q)", raw_m_plier);
    //printf("m = strlen(m_cand) = %d\n",m);
    //printf("strlen(raw_m_plier) = %d\n", strlen(raw_m_plier));
    char *m_plier = (char *)malloc( (strlen(raw_m_plier)+2)*sizeof(char));
    if( strlen(raw_m_plier)%2 != 0){
        m_plier[0]=raw_m_plier[0];
        m_plier[1]='\0';
        strcat(m_plier, raw_m_plier);
    }
    else{
        m_plier[0]='\0';
        strcpy(m_plier, raw_m_plier);
    }
    q = strlen(m_plier);   // q is always even  q is the number of digits in multiplier with even number of digits
    //printf("m_plier = %s\n", m_plier);
    //printf("q = strlen(m_plier) = %d\n", q);

    // creating table of M
    char *M0 = (char *)malloc((m+1)*sizeof(char));
    for (i=0; i<m; i++){ M0[i] = '0'; }
    M0[m]='\0';

    char *M1 = (char *)malloc((m+1)*sizeof(char));
    strcpy(M1, m_cand);

    char *M_1 = (char *)malloc((m+1)*sizeof(char));
    twos_comp( m_cand, M_1);

    char *M2 = (char *)malloc((m+2)*sizeof(char));
    M2[0]='\0';
    strcpy(M2, m_cand);
    M2[m]='0';
    M2[m+1]='\0';

    char *M_2 = (char *)malloc((m+2)*sizeof(char));
    twos_comp( M2, M_2);

    // Table of M
    printf("\nStep 1] Table of M:\n%15s  %16s\n", "Code", "Value");

    printf("%15d  %16s\n",  0, M0  );
    printf("%15d  %16s\n",  1, M1  );
    printf("%15d  %16s\n", -1, M_1 );
    printf("%15d  %16s\n",  2, M2  );
    printf("%15d  %16s\n", -2, M_2 );


    // Operation on Q

    // encoding 1
    int encodedQ[q];
    (m_plier[q-1]=='0') ? ( encodedQ[q-1]=0 ) : ( encodedQ[q-1]=-1 );
    for(i=q-2; i>=0; i--){
        if (m_plier[i]==m_plier[i+1]) { encodedQ[i]=0 ; }
        else if (m_plier[i]=='1' && m_plier[i+1]=='0') { encodedQ[i]=-1 ; }
        else if (m_plier[i]=='0' && m_plier[i+1]=='1') { encodedQ[i]=1 ; }
    }

    // encoding 2
    int encodedQ_final[q/2];
    for(i=q-1 ; i>=1 ; i=i-2){
        encodedQ_final[(i-1)/2] = 2*encodedQ[i-1] + encodedQ[i];
    }


    printf("\nStep 2] Operation on Q:\n");
    printf("%18s%3s",   "Q: ", " ");
    for(i=0;i<q;i++){ printf(" %c",m_plier[i]) ; }

    printf("\n%18s%3s",   "Booth Encoding: "," ");
    for(i=0;i<q;i++){ printf("%2d",encodedQ[i]) ; }
    printf("\n");

    printf("%18s%2s", "Final Encoding: "," ");
    for(i=0; i< q/2; i++) { printf("%4d", encodedQ_final[i]) ; }
    printf("\n\n");


    // multiplication M * encodedQ_final

    printf("Step 3] M * Final Encoding of Q :\n");

    printf("%15s", " ");
    for (i=0;i<m;i++) { printf(" %c", m_cand[i]) ; }
    printf("\n");

    printf("%4sx%*s",  " ", 10+2*m-q, " ");
    for(i=0;i<q/2;i++) { printf("%2d",encodedQ_final[i]); }

    printf("\n%4s"," ");
    for(i=0;i<17+2*m;i++) { printf("-"); };
    printf("\n");


    int anslength = m + 1 + 2*(q/2-1);

    char *partial_pdt = (char *)malloc((anslength+1)*sizeof(char));
    //partial_pdt = "";     // why does this line give runtime error  ?????

    char *tempsum = (char *)malloc((anslength+1)*sizeof(char));
    for(i=0;i<=anslength-1; i++) { tempsum[i]='0';}
    tempsum[anslength]='\0';

    char *sum = (char *)malloc((anslength+1)*sizeof(char));
    for(i=0;i<=anslength-1; i++) { sum[i]='0';}
    sum[anslength]='\0';

    int k;

    for( i=q/2-1, j=0  ;  i>=0  ;   i--, j++ ){

        for(k=0;k<=anslength-1; k++) { tempsum[k]='0';}
        tempsum[anslength]='\0';

        switch(encodedQ_final[i]){
            case 0:{
                //printf("\nCase 0 executing.\n");
                int index_last_lpad = anslength - 2*j - strlen(M0) - 1 ;
                //printf("index_last_lpad = %d\n", index_last_lpad);
                for(k=0; k <= index_last_lpad; k++) { partial_pdt[k] = M0[0] ; }
                partial_pdt[k]='\0' ;
                strcat(partial_pdt, M0);
                //printf("Exiting Case 0.\n");
//                printf("\nCase 0 executing.\n");
//                for(k=0; k<anslength; k++){ partial_pdt[k] = '0' ; }
//                partial_pdt[anslength]='\0';
//                printf("Exiting Case 0.\n");
                break;
            }

            case 1:{
                int index_last_lpad = anslength - 2*j - strlen(M1) - 1 ;
                for(k=0; k <= index_last_lpad; k++) { partial_pdt[k] = M1[0] ; }
                partial_pdt[k]='\0' ;
                strcat(partial_pdt, M1);
                break;
            }

            case -1:{
                int index_last_lpad = anslength - 2*j - strlen(M_1) - 1 ;
                for(k=0; k <= index_last_lpad; k++) { partial_pdt[k] = M_1[0] ; }
                partial_pdt[k]='\0' ;
                strcat(partial_pdt, M_1);
                break;
            }

            case 2:{
                int index_last_lpad = anslength - 2*j - strlen(M2) - 1 ;
                for(k=0; k <= index_last_lpad; k++) { partial_pdt[k] = M2[0] ; }
                partial_pdt[k]='\0' ;
                strcat(partial_pdt, M2);
                break;
            }

            case -2:{
                int index_last_lpad = anslength - 2*j - strlen(M_2) - 1 ;
                for(k=0; k <= index_last_lpad; k++) { partial_pdt[k] = M_2[0] ; }
                partial_pdt[k]='\0' ;
                strcat(partial_pdt, M_2);
                break;
            }
        }
        //printf("\nJust before padding right 0s.\n");
        for(k=0; k<2*j; k++) { strcat(partial_pdt,"0") ; }
        //printf("\nJust before printing partial product.\n");

        if(j!=0){ printf("%5s%*s\n", "+",10+2*m, partial_pdt); }
        else{ printf("%*s\n",15+2*m, partial_pdt); }
        add( sum, partial_pdt, tempsum);
        strcpy( sum, tempsum);
        //printf("\nsum = %s\n",sum);

    }

    printf("%4s"," ");
    for(i=0;i<17+2*m;i++) { printf("-"); };
    printf("\n");

    printf("%*s\n", 15+2*m, sum);

    printf("%4s"," ");
    for(i=0;i<17+2*m;i++) { printf("-"); };
    printf("\n\n");

    printf("Product in Decimal Form: %d\n\n", twoscompBin_To_Dec (sum) );

    free(m_plier); free(M0); free(M1); free(M_1); free(M2); free(M_2); free(partial_pdt); free(tempsum); free(sum);

    return;
}

