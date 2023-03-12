#include<stdio.h>

void main(){
    struct nameformat{
        char fname[20];
        char lname[20];
        int age;
    };
    struct student{
        int rollno;
        char div;
        struct nameformat name;
        float avgmarks;
    };

    //int x,y,z;
    //printf("%d %d %d\n",&x,&y, &z);
    struct student stud1;
    printf("           &stud1 = %u\n", &stud1);
    printf("    &stud1.rollno = %u\n", &stud1.rollno);
    printf("       &stud1.div = %u\n", &stud1.div);
    printf("      &stud1.name = %u\n", &stud1.name);
    printf("&stud1.name.fname = %u\n", &stud1.name.fname);
    printf("&stud1.name.lname = %u\n", &stud1.name.lname);
    printf("  &stud1.name.age = %u\n", &stud1.name.age);
    printf("  &stud1.avgmarks = %u\n\n", &stud1.avgmarks);

}
