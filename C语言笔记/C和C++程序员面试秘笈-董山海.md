


```c
1.  i++ �� ++i ��Ч�ʣ�
ǰ׺ ++ ���Է��ض�������ã���׺ ++ ���뷵�ض����ֵ�����ԣ�
�ڽ��������͵���������ߵ�Ч��û������
�Զ����������͵������ ++iЧ�ʽϸߡ�



2�� �з��ź��޷��ŵ�ת��

���ӣ�
#include<stdio.h>
int main(void)
{
	int i=7, j=-7, k=-8;
	int m,n;
	unsigned int a=i;
	m=(a+j==0)?1:0;
	n=(a+k>0)?1:0;
	printf("m=%d,n=%d\n",m,n);
	return 0;
}

�����
m=1,n=1

������
a������Ϊunsigned��j������Ϊsigned��a��j���ʱ��j����ʽת����unsigned��
��Ϊint����Ϊ32λ��λ��̫�࣬���Խ�������8λ��char���������㣺
j=-7�Ĳ���Ϊ��
ԭ�룺1000 0111
���룺1111 1000
���룺1111 1001
j��ʽת����unsigned��
1111 1001
a�Ĳ��룺
0000 0111
a+j�Ĳ��룺
1 0000 0000
���һλ�����Ϊ0��
��unsigned��7����signed��-7�Ľ��Ϊ0.

k=-8�Ĳ���Ϊ��
ԭ�룺1000 1000
���룺1111 0111
���룺1111 1000
a�Ĳ��룺
0000 0111
a+k�Ĳ��룺
1111 1111
�������0.



3����ʹ����ʱ����������2��ֵ
void swap1(int& a, int& b)
{
	a=a+b;
	b=a-b;
	a=a-b;
}

void swap2(int& a, int& b)
{
	a ^= b;
	b ^= a;
	a ^= b;
}



4. ��ֵ���
char���͵ķ�Χ��-128~127��127+1=-128��-128-1=127��
unsigned char���͵ķ�Χ��0~255��255+1=0��0-1=255.
����ܽ᣺
���ֵ��1��������Сֵ��
��Сֵ-1���������ֵ��
-128�Ĳ���Ϊ 1000 0000,��û��ԭ��ͷ��롣



5�� ���� sizeof

���ӣ�
#include<stdio.h>
void func(char str[])
{
	printf("in func, sizeof(str)=%d\n",sizeof(str));
}
int main(void)
{
	char str[] = "abcde";
	printf("sizeof(str)=%d\n",sizeof(str));
	func(str);
	return 0;
}

�����
sizeof(str)=6
in func, sizeof(str)=8



6.
int(*a[10])(int);
a��һ����10��ָ��Ԫ�ص����飬ÿ��ָ��ָ��һ������Ϊint������ֵΪint�ĺ�����

int(*(*a)[5])(int *p);
a��һ��ָ�룬ָ����5��Ԫ�ص����飬�����ÿ��Ԫ���Ǻ���ָ�룬����ָ��ָ�򷵻�ֵΪint������Ϊint*�ĺ�����

int(*(*a)(int *p))[5];
a��һ������ָ�룬�������β�Ϊint *������ֵ��ָ�������ָ�룬���������5��int���͵�Ԫ�ء�


void(*signal(int signo, void(*func)(int)))(int);
==> 
typedef void(*signal_t)(int);
signal_t signal(int signal, signal_t func);


char (*(*x())[5])();
x��һ���޲����������������ú�������һ��ָ�룬���ָ��ָ��һ����5��ָ��Ԫ�ص����飬�������ÿ��Ԫ�ض�ָ��һ������ֵ������char���޲κ�����


������������ʱ���ȿ������ұ���ʲô���ţ��ٿ����������ʲô���š�
�����a[]��������һ�����顣
�����a()��������һ��������
�����*a��������һ��ָ�롣



7���ַ����Ĵ洢

���ӣ�
#include<stdio.h>
int main(void)
{
	char * str1 = "abc";
	printf("%p\n",str1);
	printf("%p\n","abc");
	printf("%p\n","abcd");
	return 0;
}

�����
0x400614
0x400614
0x40061c

�ַ��� "abc" ���ַ��� "abc" �ĵ�ַ��ͬ��
�ַ��� "abc" ���ַ��� "abcd" �ĵ�ַ��ͬ��



8�� ָ������
p+n=p+n*sizeof(*p)
p2-p1=(p2-p1)/sizeof(*p)

���ӣ�
#include<stdio.h>
int main(void)
{
	char * str[]={"welcome","to","fortemedia","nanjing"};
	char **p=str+1;
	str[0]=(*p++)+2;
	str[1]=*(p+1);
	str[2]=p[1]+3;
	str[3]=p[0]+(str[2]-str[1]);
	printf("str[0]=%s\n",str[0]);
	printf("str[1]=%s\n",str[1]);
	printf("str[2]=%s\n",str[2]);
	printf("str[3]=%s\n",str[3]);
	return 0;
}

�����
str[0]=
str[1]=nanjing
str[2]=jing
str[3]=g

������
�ַ������ʽ "welcome" �ȼ��������׵�ַ������str���������Щ�ַ������׵�ַ��



9�����õ�ַΪ0���ĳ���
(*((void(*)())0))();  �ȼ��ڣ�
typedef void(*func)();
(*((func)0))();



10. ����ָ��
void(*sigal(int, void(*)(int)))(int);  �ȼ��ڣ�
typedef void(*hander)(int);
hander sigal(int, hander);
```

