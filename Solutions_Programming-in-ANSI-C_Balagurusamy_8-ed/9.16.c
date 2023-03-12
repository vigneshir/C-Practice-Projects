int strcmp(char str1[500],char str2[500]);

void main()
{
    char str1[500],str2[500];
    printf("Strings to be compared (non-blank): ");
    scanf("%s %s",str1,str2);
    printf("\n%d",strcmp(str1,str2));
}

int strcmp(char str1[500],char str2[500])
{
    int i=0,d;
    do
    {
        d = str1[i]-str2[i];
        if (d!=0)
        {
            return d;
        }
        else
        {
            if (str1[i]=='\0'||str2[i]=='\0')
            {
                return d;
            }
        }
        ++i;
    }
    while ( d==0 && (str1[i]!='\0'||str2[i]!='\0') );

}
