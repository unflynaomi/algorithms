#include<stdio.h>
//按照字典序排序 产生1-n的全排列 
int n;
void permutation(int* permute,int size)
{
	if(size==n)
	{
		for(int i=0; i<size; i++)
			printf("%d ",permute[i]);
		printf("\n");
	}
	else
	{

		for(int i=1; i<=n; i++ )
		{
			bool flag=false;//看看新加入的数，之前有没有出现过
			for(int j=0; j<size; j++)
			{
				if(permute[j]==i)
				{
					flag=true;
					break;
				}
			}
			if(!flag)
			{
				permute[size]=i;			
				permutation(permute,size+1);
			}

		}

	}
}

int main()
{
	n=5;
	int permute[n];
	permutation(permute,0);
}
