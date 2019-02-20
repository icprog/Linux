/***************************************************************************
输出结果：
sizeof(*p)=32
p=0x0,p+1=0x20
sizeof(unsigned long)=8, sizeof(unsigned int)=4, (unsigned long)p+1=0x1, (unsigned int *)p+1=0x4
***************************************************************************/
#include<stdio.h>

struct test{
	int Num;
	char *pcName;
	short Sdate;
	char cha[2];
	short sBa[4];
}*p;

int main(void)
{
	printf("sizeof(*p)=%d\n",sizeof(*p));
	printf("p=0x%x,p+1=0x%x\n",p,p+1);
	printf("sizeof(unsigned long)=%d, sizeof(unsigned int)=%d, (unsigned long)p+1=0x%x, (unsigned int *)p+1=0x%x\n",
			sizeof(unsigned long), sizeof(unsigned int), (unsigned long)p+1, (unsigned int *)p+1);
	return 0;
}
