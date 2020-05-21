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

//将b字符串的内容复制到a中
char *str_cpy(char *a,char*b)
{
    int i;
    for(i=0; b[i]!='\0';i++)
    {
        a[i]=b[i];
    }
    a[i] = '\0';
    return a;
}

//将字符串b中n长度的内容复制到a中
char *mem_cpy(char *a,char *b,int n)
{
    int i;
    for(i=0; b[i]!='\0' && i<n;i++)
    {
        a[i]=b[i];
    }
    a[i] = '\0';
    return a;
}

//将字符串in中的src字符串替换为dst字符串，返回修改后的新字符串地址
char *str_replace(char*in,char*src,char*dst)
{
    char *tem_in = in,*out, *out_head,*p;
    //in和out_head储存原字符串和修改后字符串的地址
    //tem_in和out在函数中会被修改，p用来储存in中的src字符串地址
    int in_len,src_len,dst_len,len;
    //分别储存原字符串，修改源和目标的长度以及指针p到原字符串开头的长度
    in_len = str_len(in);
    src_len = str_len(src);
    dst_len = str_len(dst);

    out = (char*)calloc(in_len, sizeof(char*));
    //最初修改后字符串与原字符串大小相等
    out_head = out;
    p = str_str(tem_in, src);

    while(p)
    {
        if(dst_len > src_len)
        {
            //如果修改完长度增加，每次修改增加内存空间
            in_len += (dst_len - src_len);
            out_head = (char*)realloc(out_head, in_len * sizeof(char*));
        }
        len = (int)(p - tem_in);
        mem_cpy(out,tem_in,len);
        //先将修改部分前的字符复制进新字符串内
        mem_cpy(out + len, dst, dst_len);
        //然后复制dst字符串
        tem_in = p + src_len;
        //接着把原字符串指针跳到修改内容后
        out += len + dst_len;
        //再把新字符串指针也跳到修改内容后
        p = str_str(tem_in, src);
        //再次检查是否有需要修改部分
    }
    str_cpy(out, tem_in);
    //将剩余部分进行复制
    return out_head;
}

//读取文件并生成字符串储存内容
char *file_get()
{
    FILE *fp1;
    char ch, *file;
    int len = 4, i=0;
    file = (char*)calloc(len, sizeof(char*));

    //在Clion内，文件no3_1.txt与exe文件的相对路径应为../no3_1.txt
    //应根据exe生成路径调整文件相对路径
    if ((fp1 = fopen("../no3_1.txt", "r"))  == NULL)
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

//生成文件，写入指定字符串
void file_write(char *str)
{
    FILE *fp2 = fopen("../no3_2.txt","w");
    if (fp2 == NULL) puts("Fail to create file.");
    else{
        fputs(str, fp2);
    }
    fclose(fp2);
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

//大写字母转小写
char to_lower(char ch)
{
    if (ch >='A' && ch <='Z')
        return ch += 32;
    return ch;
}

//统计字母个数，不区分大小写
void alpha_sum(int *a, char *str)
{
    int i;
    for(i=0;str[i]!='\0';i++)
        a[to_lower(str[i]) - 'a']++;
    for(i=0;i<26;i++)
        printf("%c : %d\n",'a'+i,a[i]);
}

int main()
{
    char *file,*src,*dst,*out;
    int a[26] = {0};
    file = file_get();

    puts("请输入被替换字符:");
    src = str_input();
    puts("请输入替换字符:");
    dst = str_input();

    out = str_replace(file,src,dst);
    puts(file);
    puts(out);
    file_write(out);
    alpha_sum(a,file);
    free(file); free(src); free(dst); free(out);
    return 0;
}

