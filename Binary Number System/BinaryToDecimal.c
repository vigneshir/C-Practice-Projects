#include<string.h>
#include<math.h>

void main(){
    int i=0, ln, choice, dec=0;
    char bin[50];

    printf("1. Unsigned\n2. Sign Magnitude\n3. 2's Complement\n");
    printf("Enter the representation used: ");
    scanf("%d",&choice);
    printf("Enter the binary integer to be converted to decimal: ");
    scanf("%s", bin);
    printf("Decimal equivalent: ");

    ln = strlen(bin);

    strrev(bin);

    switch(choice){
        case 1 :
            for (i=0;i<ln;i++){
                if (bin[i]=='1'){
                    dec += pow(2.0,(float)i);
                }
            }
            printf("%d\n",dec);
            break;


        case 2:
            for (i=0;i<ln-1;i++){
                if (bin[i]=='1'){
                    dec += pow(2.0,(float)i);
                }
            }
            if(bin[ln-1]=='0'){
                printf("%d\n",dec);
            }
            else{
                printf("%d\n",(-1*dec));
            }
            break;


        case 3:
            for (i=0;i<ln-1;i++){
                if (bin[i]=='1'){
                    dec += pow(2.0,(float)i);
                }
            }
            if (bin[ln-1]=='1'){
                dec -= pow(2.0,(float)(ln-1));
            }
            printf("%d\n",dec);
            break;


        default:
            printf("Invalid type of representation.\n");
    }

}



