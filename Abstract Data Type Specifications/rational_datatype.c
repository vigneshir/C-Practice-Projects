// using structure
// drawback of array: the identifiers 'num' and 'den' cannot be used.

#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int numr; int denr;
    } RATIONAL;

void reducedform(RATIONAL r1, RATIONAL *redform);
void addrat(RATIONAL r1, RATIONAL r2, RATIONAL *sum);
void subrat(RATIONAL r1, RATIONAL r2, RATIONAL *diff);
void mulrat(RATIONAL r1, RATIONAL r2, RATIONAL *prod);
void divrat(RATIONAL r1, RATIONAL r2, RATIONAL *div);

void main(){
    int choice;
    RATIONAL r1, r2;
    RATIONAL answer;

    void (*funcptrarr[4])(RATIONAL r1, RATIONAL r2, RATIONAL *answerptr); // array of pointers to functions.
    //funcptrarr[] = { addrat, subrat, mulrat, divrat }; // note that this is invalid since array can only be initialized during declaration
    funcptrarr[0] = addrat;
    funcptrarr[1] = subrat;
    funcptrarr[2] = mulrat;
    funcptrarr[3] = divrat;

    printf("Operations on Rational Numbers:");
    printf("\n1. Addition.");
    printf("\n2. Subtraction.");
    printf("\n3. Multiplication.");
    printf("\n4. Division.");
    printf("\n5. Reducing to Lowest Form.");

    for(;;){
        printf("\n\nEnter the operation to be performed (enter -1 to exit): ");
        scanf("%d", &choice);

        if(choice>=1 && choice<=4){
            printf("Rational number 1(num den): ");
            scanf("%d %d", &r1.numr, &r1.denr);
            printf("Rational number 2(num den): ");
            scanf("%d %d", &r2.numr, &r2.denr);
            (funcptrarr[choice-1])(r1, r2, &answer);
        // or (*funcptrarr[choice-1])(r1, r2, &answer);  // since function name and function address are interchangeable, just like array
        }
        else if (choice==5){
            RATIONAL r, redform;
            printf("Rational number to be reduced(num den): ");
            scanf("%d %d", &r.numr, &r.denr);
            reducedform(r, &redform);
            printf("Lowest form of %d/%d   = %d/%d", r.numr, r.denr, redform.numr, redform.denr);
        }
        else if( choice==-1){
            printf("Exiting...");
            exit(0);
        }
        else{
            printf("Please enter a valid number.");
        }
    }
}

void reducedform(RATIONAL r1, RATIONAL *redform){
    int a,b,temp;
    (r1.numr>r1.denr)?(a=r1.numr, b=r1.denr):(a=r1.denr, b=r1.numr);
    while(b>0){
        temp = a%b;
        a=b;
        b=temp;
    }
    redform->numr = r1.numr / a ;
    redform->denr = r1.denr / a ;
}

void addrat(RATIONAL r1, RATIONAL r2, RATIONAL *sum){
    RATIONAL tempsum;
    tempsum.numr = r1.numr*r2.denr+r2.numr*r1.denr;
    tempsum.denr = r1.denr*r2.denr;
    reducedform(tempsum, sum);
    printf("%d/%d + %d/%d = %d/%d", r1.numr, r1.denr, r2.numr, r2.denr, sum->numr, sum->denr);
}

void subrat(RATIONAL r1, RATIONAL r2, RATIONAL *diff){
    RATIONAL tempdiff;
    tempdiff.numr = r1.numr*r2.denr-r2.numr*r1.denr;
    tempdiff.denr = r1.denr*r2.denr;
    reducedform(tempdiff, diff);
    printf("%d/%d - %d/%d = %d/%d", r1.numr, r1.denr, r2.numr, r2.denr, diff->numr, diff->denr);
}

void mulrat(RATIONAL r1, RATIONAL r2, RATIONAL *prod){
    RATIONAL tempprod;
    tempprod.numr = r1.numr*r2.numr;
    tempprod.denr = r1.denr*r2.denr;
    reducedform(tempprod, prod);
    printf("%d/%d * %d/%d = %d/%d", r1.numr, r1.denr, r2.numr, r2.denr, prod->numr, prod->denr);
}

void divrat(RATIONAL r1, RATIONAL r2, RATIONAL *div){
    RATIONAL tempdiv;
    tempdiv.numr = r1.numr*r2.denr;
    tempdiv.denr = r1.denr*r2.numr;
    reducedform(tempdiv, div);
    printf("%d/%d / %d/%d = %d/%d", r1.numr, r1.denr, r2.numr, r2.denr, div->numr, div->denr);
}
