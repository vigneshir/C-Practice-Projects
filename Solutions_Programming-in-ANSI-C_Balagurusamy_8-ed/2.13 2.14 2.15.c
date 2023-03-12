#include<stdio.h>
#include<math.h>

#define PI 3.1417
float distance(float x1, float y1,float x2, float y2);

void main()
{
    float x1,y1,x2,y2,radius1,radius2;
    scanf("%f %f",&x1,&y1);
    scanf("%f %f",&x2,&y2);
    radius1 = distance(x1,y1,x2,y2);
    radius2 = distance(x1,y1,x2,y2)/2;
    printf("Perimeter: %.2f\nArea: %.2f",2*PI*radius1,PI*radius1*radius1);
    printf("\n\nArea:%.2f",PI*radius2*radius2);
}

float distance(float x1,float y1,float x2,float y2)
{
    float distance = pow( pow(x2-x1,2)+pow(y2-y1,2) , 0.5);
    return distance;
}
