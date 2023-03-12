#include<stdlib.h>
void main(){
    int n,i;
    struct student{
        int rollno;
        char name[25];
        float percent;
    };
    printf("Enter number of students: ");
    scanf("%d",&n);
    struct student studs[n],*ptr;
    ptr = (struct student *)calloc(n, sizeof(struct student));
    printf("Enter student details ( Roll No.  Name  Percentage ) :\n");
    for (ptr=studs ; ptr<studs+n ; ptr++){
        scanf("%d %s %f", &(ptr->rollno) , ptr->name , &(ptr->percent) );
    }
    printf("\n\nRoll No.          \t\tName          Percentage\n");
    for (ptr=studs ; ptr<studs+n ; ptr++){
        printf("  %4d        %15s        %.2f\n", ptr->rollno , ptr->name , ptr->percent );
    }
    free(ptr);
}
