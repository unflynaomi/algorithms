#include<stdio.h>
//ʹ�ò���������ķ��������Ӽ���ʹ��һ������Ϳ��Ա�ʾ���е��Ӽ� 
int count=0;
void combination(int n,int* comb,int size)
{
//	if(size==r)
//	{
      
		for(int i=0;i<size;i++)
		   printf("%d ",comb[i]);
		printf("\n");   
		count++;
//	}
//	else
//	{
		int max=0;//Ŀǰ���������������������м����֣�ֻ�ܼӱȵ�ǰ��max������� �����������ظ� 
		//��Ϊsizeһ��ʼ�ǿյģ�����max���ó���һ����С��ֵ 
		if(size!=0)
		  max=comb[size-1];//����Ԫ�ؾ���comb�����һ��Ԫ�� 
	
		for(int add=1;add<=n;add++)
		{
			if(add>max)
			{
				comb[size]=add;
				combination(n,comb,size+1);
			}
		 } 
		
//	}
} 

int main()
{
	int comb[5];
	combination(5,comb,0);
	printf("����%d��\n",count);
}
