/***************************************************************************
输出结果：
5 6 4 7 3 8 2 9 1 1 
1 1 2 3 4 5 6 7 8 9
***************************************************************************/
#include<stdio.h>

void sort(int a[], int len)
{
	int i=0,j=0,temp=0;
	for(i=0; i<len; i++){
		for(j=1;j<len-i;j++){
			if(a[j]<a[j-1]){
				temp=a[j];
				a[j]=a[j-1];
				a[j-1]=temp;
			}
		}
	}
}

int main(void)
{
	int i;
	int a[10]={5,6,4,7,3,8,2,9,1,1};
	for(i=0;i<10;i++)
		printf("%d ",a[i]);
	printf("\n");

	sort(a,10);

	for(i=0;i<10;i++)
		printf("%d ",a[i]);
	printf("\n");
	return 0;
}
