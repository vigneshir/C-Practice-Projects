#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

void Dec_To_UnsignedBin(int num, char *unsigned_bin);
void add( char *n1, char *n2, char *sum );
void BinMult_Basic ( char *m_cand, char *m_plier);
int UnsignedBin_To_Dec (char *twoscompbin);

void main(){
    int n1, n2;

    printf("Enter the positive decimal numbers (less than 32767) to be multiplied (multiplicand multiplier): ");
    scanf("%d %d",&n1,&n2);

    // the program can only multiply numbers with max 16 bits in 2's complement system.
    char *m_cand = (char *)malloc(17*sizeof(char));
    char *m_plier= (char *)malloc(17*sizeof(char));

    Dec_To_UnsignedBin(n1, m_cand);
    Dec_To_UnsignedBin(n2, m_plier);

    printf("m_cand = %s\n", m_cand);
    printf("m_plier = %s\n", m_plier);

    BinMult_Basic(m_cand, m_plier);

    return;

}


void Dec_To_UnsignedBin(int num, char *unsigned_bin){

        char answer[17];                // this function can 'store' max 16 bit binaries, but can 'calculate' any binary form.
        answer[16]='\0';

        int i=15, unsigned_digits, index_first_garbage_bit ;
        int tempnum = num;
        while(tempnum>0){
            (tempnum%2 == 0)?(answer[i]='0'):(answer[i]='1');
            tempnum /= 2;
            i--;
        }
        int index_first_useful_bit = i+1;
        for (i=index_first_useful_bit; i<=16; i++){
            unsigned_bin[i-index_first_useful_bit] = answer[i];
        }

        return ;

}



void BinMult_Basic ( char *m_cand, char *m_plier){
    int i,j;
    int m = strlen(m_cand);
    int q = strlen(m_plier);
    int anslength = m + q-1 + 1;

    char *partial_pdt = (char *)malloc( (anslength+1)*sizeof(char) );
    char extension[anslength-m+1] ;

    char *sum = (char*)malloc((anslength+1)*sizeof(char));
    for (i=0;i<anslength; i++){ sum[i]='0';}
    sum[anslength]='\0';

    printf("%30s\n", m_cand);
    printf("%2sx%27s\n", " ",m_plier);
    for(i=0; i<=33; i++){ printf("-");}
    printf("\n");

    for(i=q-1; i>=0; i--){

        strcpy(partial_pdt, ""); strcpy(extension, "");

        if(m_plier[i]=='0'){
            for(j=0; j<anslength; j++){ strcat(partial_pdt, "0"); }
            // no addition to 'sum' required
        }

        else if (m_plier[i]=='1'){
            for( j=0; j<anslength-m-(q-1-i); j++){ strcat(extension,"0"); }
            strcat(extension, m_cand);
            for(j=0; j<(q-1-i); j++){ strcat(extension,"0"); }
            strcpy(partial_pdt, extension);

            char *tempsum = (char *)malloc((anslength+1)*sizeof(char));
            add(sum, partial_pdt,tempsum);
            strcpy(sum, tempsum);

            free(tempsum);
        }

        if(i==q-1){ printf("%3s" ," "); }
        else { printf("%2s+", " "); }
        printf("%27s\n", partial_pdt);
    }

    for(i=0; i<=33; i++){ printf("-");}
    printf("\n%30s\n", sum);
    for(i=0; i<=33; i++){ printf("-");}

    printf("\n\nProduct in decimal form: %d\n", UnsignedBin_To_Dec(sum));

}


void add( char *n1, char *n2, char *sum ){

    int i;
    int n = strlen(n1);

    static char carry;
    carry = '0';

    for(i=n-1 ; i>=0; i--){

        switch ( (n1[i]-'0') + (n2[i]-'0') ){
            case 0 : // 0 and 0
                sum[i]=carry;
                carry='0';
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
