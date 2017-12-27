#include<stdio.h>
//按序产生组合数Cnr， 但是n和r是动态指定的，不可以使用那种嵌套for循环的法子 
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
		int max=0;//目前组合中最大的数，再往组合中加数字，只能加比当前的max还大的数 ，否则会产生重复 
		//因为size一开始是空的，所以max设置成了一个很小的值 
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
	printf("共有%d条\n",count);
}
