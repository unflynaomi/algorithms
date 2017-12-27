#include<stdio.h>
int main()
{
	int n=6;//一共有n个人 
	int m=5;//报到m为止
	int ifEliminated[n];
	for(int i=0;i<n;i++)
	  ifEliminated[i]=0;
	int josephus[n];
	for(int i=0;i<n;i++)
	  josephus[i]=i+1;
	int  eliminated=0;//目前被杀的人数 
	int p=0;//数组的索引 
	int count=0;
	while(eliminated<n-1)
	{
		if(ifEliminated[p]==0)
		   count++;
		if(count==m)
		{
			printf("%d被杀!\n",josephus[p]);
			ifEliminated[p]=1;
			eliminated++;
			count=0;
		}   
		p=(p+1)%n;
	}    
	for(int i=0;i<n;i++)
	  if(ifEliminated[i]==0)
	    printf("%d活了下来!\n",josephus[i]);
	
}
