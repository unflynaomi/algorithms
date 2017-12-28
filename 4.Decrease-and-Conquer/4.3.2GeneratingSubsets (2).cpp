#include<stdio.h>
//使用产生组合数的方法产生子集，使用一个数组就可以表示所有的子集 
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
		int max=0;//目前组合中最大的数，再往组合中加数字，只能加比当前的max还大的数 ，否则会产生重复 
		//因为size一开始是空的，所以max设置成了一个很小的值 
		if(size!=0)
		  max=comb[size-1];//最大的元素就是comb里最后一个元素 
	
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
	printf("共有%d条\n",count);
}
