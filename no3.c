#include <stdio.h>
#include <stdlib.h>

//�����ַ����ĳ���
int str_len(char *a)
{
    int count = 0;
    while(a[count++] != '\0');
    return count-1;
}

//�Ƚ������ַ�������ͬ����1�����򷵻�0
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

//�ú����������ַ���a�е�һ�γ���b�ַ�����λ�ã����δ�ҵ��򷵻� null
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

//��b�ַ��������ݸ��Ƶ�a��
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

//���ַ���b��n���ȵ����ݸ��Ƶ�a��
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

//���ַ���in�е�src�ַ����滻Ϊdst�ַ����������޸ĺ�����ַ�����ַ
char *str_replace(char*in,char*src,char*dst)
{
    char *tem_in = in,*out, *out_head,*p;
    //in��out_head����ԭ�ַ������޸ĺ��ַ����ĵ�ַ
    //tem_in��out�ں����лᱻ�޸ģ�p��������in�е�src�ַ�����ַ
    int in_len,src_len,dst_len,len;
    //�ֱ𴢴�ԭ�ַ������޸�Դ��Ŀ��ĳ����Լ�ָ��p��ԭ�ַ�����ͷ�ĳ���
    in_len = str_len(in);
    src_len = str_len(src);
    dst_len = str_len(dst);

    out = (char*)calloc(in_len, sizeof(char*));
    //����޸ĺ��ַ�����ԭ�ַ�����С���
    out_head = out;
    p = str_str(tem_in, src);

    while(p)
    {
        if(dst_len > src_len)
        {
            //����޸��곤�����ӣ�ÿ���޸������ڴ�ռ�
            in_len += (dst_len - src_len);
            out_head = (char*)realloc(out_head, in_len * sizeof(char*));
        }
        len = (int)(p - tem_in);
        mem_cpy(out,tem_in,len);
        //�Ƚ��޸Ĳ���ǰ���ַ����ƽ����ַ�����
        mem_cpy(out + len, dst, dst_len);
        //Ȼ����dst�ַ���
        tem_in = p + src_len;
        //���Ű�ԭ�ַ���ָ�������޸����ݺ�
        out += len + dst_len;
        //�ٰ����ַ���ָ��Ҳ�����޸����ݺ�
        p = str_str(tem_in, src);
        //�ٴμ���Ƿ�����Ҫ�޸Ĳ���
    }
    str_cpy(out, tem_in);
    //��ʣ�ಿ�ֽ��и���
    return out_head;
}

//��ȡ�ļ��������ַ�����������
char *file_get()
{
    FILE *fp1;
    char ch, *file;
    int len = 4, i=0;
    file = (char*)calloc(len, sizeof(char*));

    //��Clion�ڣ��ļ�no3_1.txt��exe�ļ������·��ӦΪ../no3_1.txt
    //Ӧ����exe����·�������ļ����·��
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

//�����ļ���д��ָ���ַ���
void file_write(char *str)
{
    FILE *fp2 = fopen("../no3_2.txt","w");
    if (fp2 == NULL) puts("Fail to create file.");
    else{
        fputs(str, fp2);
    }
    fclose(fp2);
}

//�ַ������뺯��
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

//��д��ĸתСд
char to_lower(char ch)
{
    if (ch >='A' && ch <='Z')
        return ch += 32;
    return ch;
}

//ͳ����ĸ�����������ִ�Сд
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

    puts("�����뱻�滻�ַ�:");
    src = str_input();
    puts("�������滻�ַ�:");
    dst = str_input();

    out = str_replace(file,src,dst);
    puts(file);
    puts(out);
    file_write(out);
    alpha_sum(a,file);
    free(file); free(src); free(dst); free(out);
    return 0;
}

