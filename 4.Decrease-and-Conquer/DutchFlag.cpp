#include<stdio.h>
//荷兰国旗问题
//int A[9]= {3,1,2,1,1,3,2,2,3};
int A[9]= {1,1,2,3,1,3,2,2,3};
//int A[10]= {1,2,3,2,2,3,1,3,2,1};
//int n=10;
int n=9;
void swap(int* a,int* b);
void LomutoDutchFlag();
void QuickPartitionDutchFlag();
int main()
{

	QuickPartitionDutchFlag();
	for(int i=0; i<n; i++)
		printf("%d ",A[i]);
}

void LomutoDutchFlag()
{
	int i=-1;//指向红的最后一个 1
	int j=-1;//指向白的最后一个 2
	int k=-1;//指向蓝的最后一个 3
	//必须保持i小于等于j小于等于k,当等于的时候说明某段为空
	while(k+1<=n-1)
	{
		if(A[k+1]==3)//如果目前判断的球是蓝色球 3
			k++;
		else if(A[k+1]==2) //如果目前判断的球是白色球 2
		{
			//如果有蓝色球的话，j+1就是第一个3 把第一个3和新发现的2交换
			if(j!=k)
			{
				swap(&A[j+1],&A[k+1]);
				j++;
				k++;

			}
			//如果没有蓝色球，但是发现了2，j和k直接涨1
			else
			{
				j++;
				k++;
			}

		}
		else //如果目前判断的球是红色 1
		{
			if(i<j&&j<k)//如果成了规模，每段都不为空
			{
				swap(&A[i+1],&A[k+1]);//把第一个2，和新发现的1互换
				swap(&A[j+1],&A[k+1]); //把第一个3和刚换过去的2互换
				k++;
				i++;
				j++;
			}
			else if(i==j&&j==k) //如果没有2也没有3
			{
				k++;
				i++;
				j++;
			}
			else if(i==j&&j<k) //没有2但是有3
			{
				swap(&A[j+1],&A[k+1]);//第一个3和 新发现的1互换
				k++;
				i++;
				j++;
			}
			else if(i<j&&j==k)//没有3，但是有2
			{
				swap(&A[i+1],&A[k+1]);//第一个2和 新发现的1互换
				k++;
				i++;
				j++;
			}

		}

	}
}

void QuickPartitionDutchFlag()
{
	
	int begin=-1;//begin指向最后一个红 0
	int end=n;//end 指向第一个蓝 1
	int current=0;//指向目前要判断的数
	while(current<end)
	{
       
		if(A[current]==2)//如果目前我要判断的是2
			current++;
		else if(A[current]==1)
		{
			swap(&A[current],&A[begin+1]);
			//把发现的1往前抛， A[begin+1]可能是1或者2，但是不可能是3，因为begin肯定小于current,
			//begin+1小于等于current,current扫过的地方，3肯定已经抛到了右边
			current++;
			begin++;
		}
		else if(A[current]==3)
		{
			swap(&A[current],&A[end-1]);//把发现的3往后抛
			end--;//但很有可能换过来的是1，那还需要进一步往前抛
		}
		

	}

}

void swap(int* a,int* b)
{
	int tmp=*a;
	*a=*b;
	*b=tmp;
}
