#include <stdio.h>
#include <stdlib.h>

//返回字符串的长度
int str_len(char *a)
{
    int count = 0;
    while(a[count++] != '\0');
    return count-1;
}

//比较两个字符串，相同返回1，否则返回0
int str_cmp(char *a, char *b)
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
        if(*(p-1)==' ' && *(p+len)==' ')
            count++;
        temp = p + len;
        p = str_str(temp,b);
    }
    return count;
}

//字符串输入函数
char *str_input()
{
    int count =0,len = 10;
    char *a,ch;
    a = (char*)calloc(len,sizeof(char*));
    while((ch =getchar()) != '\n')
    {
        a[count] = ch;
        count++;
        if (count >= len)
            a = (char*)realloc(a, sizeof(char*) * (++len));
    }
    return a;
}

int main()
{
    char *a,*w;

    puts("Please input the sentence:");
    a = str_input();
    char *b = (char*)calloc(str_len(a), sizeof(char*));
    b = del_space(a,b);
    puts("Spaces deleted:"); puts(b);

    puts("PLease input the word to search:");
    w = str_input();
    int cal;
    cal = word_cal(a,w);
    printf("There are %d words.",cal);

    free(a);
    free(w);
    return 0;
}