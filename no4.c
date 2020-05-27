#include <stdio.h>
#include <stdlib.h>

//返回字符串的长度
int str_len(char const *a)
{
    int count = 0;
    while(a[count++] != '\0');
    return count-1;
}

//比较两个字符串，相同返回1，否则返回0
int str_cmp(char const *a, char const *b)
{
    int i;
    for(i = 0;a[i]!='\0' && b[i]!='\0';i++)
    {
        if(a[i]!=b[i])
            return 0;
    }
    return 1;
}

//该函数返回在字符串a中第一次出现b字符串的位置，如果未找到则返回 null
char *str_str(char *a,char *b)
{
    int i;
    for(i=0;a[i]!='\0';i++)
    {
        if(str_cmp(&a[i],b)) {
            return (char*)&a[i];
        }
    }
    return NULL;
}

char *del_space(char *a,char *b)
{
    int i=0,j=0,len;
    len = str_len(a);
    while(a[i]==' ') i++;
    for(;i<len;i++)
    {
        if(a[i] != ' ')
            b[j++] = a[i];
        else if (a[i-1]!= ' ')
            b[j++] = a[i];
    }
    if (b[j-1] == ' ') b[j-1] = '\0';
    return b;
}

int word_cal(char *a, char *b)
{
    char *temp = a,*p;
    int len = str_len(b), count = 0;
    p = str_str(temp,b);
    while(p)
    {
        if(*(p-1)==' ' && *(p+len)==' '
           ||p==temp && *(p+len)==' '
           ||*(p-1)==' ' && *(p+len)=='\0')
            count++;
        temp = p + len;
        p = str_str(temp,b);
    }
    return count;
}

char *str_input()
{
    int count =0,len = 10;
    char *a,ch;
    a = (char*)calloc(len,sizeof(char*));
    setbuf(stdin, NULL);
    while(ch != '\n')
    {
        a[count] = ch;
        count++;
        if (count >= len)
            a = (char*)realloc(a, sizeof(char*) * (++len));
    }
    return a;
}

char *file_get()
{
    FILE *fp1;
    char ch, *file;
    int len = 4, i=0;
    file = (char*)calloc(len, sizeof(char*));

    //在Clion内，文件no4_1.txt与exe文件的相对路径为../no4_1.txt
    //根据exe生成路径调整文件相对路径
    if ((fp1 = fopen("../no4_1.txt", "r"))  == NULL)
    {
        printf("Can't open it");
    }
    while ((ch = getc(fp1)) != EOF)
    {
        file[i] = ch;
        i++;
        if (i >= len)
            file = (char*)realloc(file, sizeof(char*) * (++len));
    }
    fclose(fp1);
    return file;
}

int main()
{
    int n = 0, cal;
    char *a,*w;

    a = file_get();
    puts(a);
    char *b = (char*)calloc(str_len(a), sizeof(char*));
    puts("1.Clean spaces\n2.Words sum\n3.exit");

    do{
        scanf("%d",&n);
        switch (n) {
            case 1:
                b = del_space(a, b);
                puts("Spaces deleted:");
                puts(b);
                break;
            case 2:
                puts("PLease input the word to search:");
                w = str_input();
                cal = word_cal(a, w);
                puts(w);
                printf("There are %d word(s).\n", cal);
                free(w);
                break;
            case 3:
                break;
            default:
                puts("wrong command");
                break;
        }
    }while(n!=3);
    free(b);
    return 0;
}