#include<stdio.h>
//������������Cnr�� ����n��r�Ƕ�ָ̬���ģ�������ʹ������Ƕ��forѭ���ķ��� 
int count=0;
void combination(int n,int r,int* comb,int size)
{
	if(size==r)
	{
		for(int i=0;i<size;i++)
		   printf("%d ",comb[i]);
		printf("\n");   
		count++;
	}
	else
	{
		int max=0;//Ŀǰ���������������������м����֣�ֻ�ܼӱȵ�ǰ��max������� �����������ظ� 
		//��Ϊsizeһ��ʼ�ǿյģ�����max���ó���һ����С��ֵ 
		for(int i=0;i<size;i++)
		{
			if(comb[i]>max)
			    max=comb[i];
		}
		for(int add=1;add<=n;add++)
		{
			if(add>max)
			{
				comb[size]=add;
				combination(n,r,comb,size+1);
			}
		 } 
		
	}
} 

int main()
{
	int comb[7];
	combination(7,4,comb,0);
	printf("����%d��\n",count);
}
