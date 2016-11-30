//8皇后问题，简单回溯版本 
#include<stdio.h>
#define N 4
int result[N];//存放每个皇后放的列号 
int count;//统计解的数目 
void  dfs(int curQueen);
bool ifCanLay(int curQueen,int tryCol);
int main()
{
	dfs(0);	
	printf("共有%d个解",count);
	
} 

void  dfs(int curQueen)//i是当前我要放的皇后 
{
	
	if(curQueen==N)//全部放完以后就输出解 
	{
		count++;
		for(int i=0;i<N;i++)
		  printf("%d ",result[i]);
	    printf("\n");	  
	}
	else
	{
		for(int tryCol=0;tryCol<N;tryCol++)//尝试放置的列
		{
			
			if(ifCanLay(curQueen,tryCol))//如果能放，就放，并搜索下一个皇后 
			{
				
				result[curQueen]=tryCol;
				//dfs(++curQueen);//放下一个皇后  
				//有人是这么写的，以4皇后为例，当搜到try[1][2]的时候，发现可以摆放的,dfs(2),curQueen=2 
				//当你发现第2号皇后无论怎么摆都不行时，dfs(2)就结束了，tryCol=3,本来应该搜[1][3]的，但是因为你
				//没有回溯，没有把正在放的皇后号-1，搜的是[2][3],就错了
				dfs(curQueen+1);//我这层的curQueen没有变 
				
			}
		} 
		
	}
}

//这个函数检查和以前的皇后冲不冲突，需要翻遍以前所有的皇后，在eightQueenSpace.cpp里面，是无需翻遍以前所有皇后的，但需要额外的空间 
bool ifCanLay(int curQueen,int tryCol)
{
	for(int k=0;k<curQueen;k++)//检查和以前放的所有的queen冲不冲突 
	{
		if(tryCol==result[k]||(curQueen+tryCol)==(k+result[k])||(curQueen-tryCol)==(k-result[k]))//和一样说明和前面的皇后在一条次对角线上
		//差一样说明和前面的皇后在一条主对角线上 
		      return false;
	}
	return true;
}


