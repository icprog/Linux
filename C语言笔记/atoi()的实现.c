
```c
һ��ʵ��C�����ַ��� atoi ����

1�����ܣ���һ���ַ���ת�������͡�

2��ԭ�ͣ� int atoi(const char *str);

3���ַ�ת�������͵�ԭ��
char str = '1';
int i,j;
i=str;
j='1'-'0';
����� str='1',i=49,j=1;
�������ַ�'1'��ASCII��Ϊ49���ַ�'0'��ASCII��Ϊ48��
�ַ����ڴ��д洢��������ASCII���Ӧ�Ķ����ơ�
ASCII��ռ1���ֽڡ�
ASCII����ʮ���Ƶġ�
�ַ�'1'���ڴ��еĴ洢Ϊ(ռ1���ֽ�)�� 0011 0001
����1���ڴ��еĴ洢Ϊ(ռ4���ֽ�)��   0x00000001

4��ת���ַ�
�˽��ƣ�'\d'��'\dd'��'\ddd'����ʾ1��3λ�˽��Ƶ�ASCII�롣
ʮ�����ƣ�'\xh'��'\xhh'��'\xhhh'����ʾ1��3λʮ�����Ƶ�ASCII�롣
������'\n'��ʾ���з��� '\0'��ASCII��Ϊ0����ʾ���ַ���

5��ʵ��atoi()


#include<stdio.h>

int atoi(const char *str)
{
	int num=0;
	int flag=1;
	
	if( (str == NULL) || (*str == '\0') ){
		return 0;
	}
	
	while(*str == ' '){
		str++;
	}

	if(*str == '\0'){
		return 0;
	}
	else if(*str == '-'){
		flag = -1;
		str++;
	}
	else if(*str == '+'){
		flag=1;
		str++;
	}

	while(*str != '\0'){
		if( (*str >= '0') && (*str <= '9') ){
			num = num*10 + (flag)*(*str - '0');
			if( ( (-1 == flag) && (num<(signed int)0x80000000) ) || ( (1 == flag) && (num>0x7fffffff) )){
				return 0;
			}
			str++;
		}
		else{
			break;
		}
	}

	return num;
}

int main(void)
{
	char *a=" 12345.67";
	char *b="-123 34";
	char *c="12344";
	char *d=" ";
	char *e="- 1";
	char *f=" +111 .";
	int i,j,k,l,m,n;
	i=atoi(a);
	j=atoi(b);
	k=atoi(c);
	l=atoi(d);
	m=atoi(e);
	n=atoi(f);
	printf("a=%s,b=%s,c=%s,d=%s,e=%s,f=%s\n",a,b,c,d,e,f);
	printf("i=%d,j=%d,k=%d,l=%d,m=%d,n=%d\n",i,j,k,l,m,n);
	return 0;
}
```

