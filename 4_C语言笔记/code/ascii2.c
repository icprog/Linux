/***************************************************************************
输出结果：
a=0x0,b=0x0,c=0x30,d=0x0,e=0x0
***************************************************************************/
#include<stdio.h>

int main(void)
{
	char a=0;
	char b='\0';
	char c='0';
	char d=a;
	char e;

	printf("a=0x%x,b=0x%x,c=0x%x,d=0x%x,e=0x%x\n",a,b,c,d,e);
	return 0;
}
