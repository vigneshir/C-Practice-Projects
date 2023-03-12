void main(){
    struct student{
        int rollno;
        char name[25];
        float percent;
    };
    struct student s1={34,"ABCDEFG",96.43}, *ptr;
    ptr=&s1;
    printf("Roll No.   Name      Percentage\n");
    printf("  %d     %s        %.2f",ptr->rollno,ptr->name,ptr->percent);

}
