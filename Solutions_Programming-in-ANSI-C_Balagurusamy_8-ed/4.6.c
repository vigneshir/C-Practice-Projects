void main()
{
    float u,a,s,t1,t2;
    printf("Initial Velocity: ");
    scanf("%f",&u);
    printf("\nAcceleration: ");
    scanf("%f",&a);
    printf("\nEnter the time interval (initial and final instants,separated by a blank space): ");
    scanf("%f %f",&t1,&t2);
    s = u*(t2-t1) + 0.5*a*(t2*t2-t1*t1);
    printf("\nDisplacement in given time interval: %.2f",s);
}
