#include<stdio.h>
int main()
{
	int n=6;//һ����n���� 
	int m=5;//����mΪֹ
	int ifEliminated[n];
	for(int i=0;i<n;i++)
	  ifEliminated[i]=0;
	int josephus[n];
	for(int i=0;i<n;i++)
	  josephus[i]=i+1;
	int  eliminated=0;//Ŀǰ��ɱ������ 
	int p=0;//��������� 
	int count=0;
	while(eliminated<n-1)
	{
		if(ifEliminated[p]==0)
		   count++;
		if(count==m)
		{
			printf("%d��ɱ!\n",josephus[p]);
			ifEliminated[p]=1;
			eliminated++;
			count=0;
		}   
		p=(p+1)%n;
	}    
	for(int i=0;i<n;i++)
	  if(ifEliminated[i]==0)
	    printf("%d��������!\n",josephus[i]);
	
}
