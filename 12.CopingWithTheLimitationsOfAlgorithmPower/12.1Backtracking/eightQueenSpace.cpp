//8皇后问题，简单回溯版本
#include<stdio.h>
#define N 8
int result[N];//存放每个皇后放的列号
int col[N];//如果这列被占了就设为1
int mainDiagonal[2*N-1];//主对角线是行减列+N-1
int minorDiagonal[2*N-1];//次对角线是行加列
int count;//统计解的数目
void  dfs(int curQueen);//i是当前我要放的皇后
bool ifCanLay(int curQueen,int tryCol);
int main()
{
	dfs(0);
	printf("共有%d个解",count);

}

void  dfs(int curQueen)//i是当前我要放的皇后
{
	printf("curQueen= %d\n",curQueen);
	if(curQueen==N)//全部放完以后就输出解
	{
		count++;
		for(int i=0; i<N; i++)
			printf("%d ",result[i]);
		printf("\n");

	}
	else
	{

		for(int tryCol=0; tryCol<N; tryCol++) //尝试放置的列
		{
			printf("try:%d %d\n",curQueen,tryCol);
			if(ifCanLay(curQueen,tryCol))//如果能放，就放，并搜索下一个皇后
			{
				printf("can lay! %d %d\n",curQueen,tryCol);
				result[curQueen]=tryCol;
				col[tryCol]=1;
				mainDiagonal[curQueen-tryCol+N-1]=1;
				minorDiagonal[curQueen+tryCol]=1;
				//dfs(++curQueen);//放下一个皇后
				//有人是这么写的，以4皇后为例，当搜到try[1][2]的时候，发现可以摆放的,dfs(2),curQueen=2
				//当你发现第2号皇后无论怎么摆都不行时，dfs(2)就结束了，tryCol=3,本来应该搜[1][3]的，但是因为你
				//没有回溯，没有把正在放的皇后号-1，搜的是[2][3],就错了
				dfs(curQueen+1);//我这层的curQueen没有变 
                 
                //有一个明显的回溯 
				//以4皇后为例，当搜到try[1][2]的时候，发现是可以摆放的，摆放，dfs(2),发现都不行，这时我要尝试摆放try[1][3]
				//但是这时第二列已经被你（1,2）给占上了，现在我们要把(1,2) 给撤了，就要消除它的影响，释放第二列
				//如果dfs递归的过程，不成功，那么我自然要撤销这步的走法，如果dfs的过程能找到解，那你也早就输出来了，撤销这步的走法
				//试试下一个位置，看看是不是一个解 
				col[tryCol]=0;
				mainDiagonal[curQueen-tryCol+N-1]=0;
				minorDiagonal[curQueen+tryCol]=0;


			}
		}



	}
}

//在eightQueenSpace.cpp里面，是无需翻遍以前所有皇后的，但需要额外的空间，判断与以前的皇后冲突与否，用了主次对角线的标志位 
bool ifCanLay(int curQueen,int tryCol)
{

	if(col[tryCol]||mainDiagonal[curQueen-tryCol+N-1]||minorDiagonal[curQueen+tryCol])//和一样说明和前面的皇后在一条次对角线上
		//差一样说明和前面的皇后在一条主对角线上
		return false;

	return true;
}


