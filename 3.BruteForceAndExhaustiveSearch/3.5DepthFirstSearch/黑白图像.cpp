//算法竞赛入门经典 P106 图 黑白图像问题
#include<stdio.h>
#include <stdlib.h>
#define MAX 50
int graph[MAX][MAX];
int visited[MAX][MAX];
void dfs(int p,int q);
int main()
{
	int graphNum;
	FILE *fp;
	if((fp=fopen("黑白图像.txt","r"))==NULL)
	{
		printf("Cannot open file !");
		exit(1);
	}
	fscanf(fp,"%d",&graphNum);

	printf("输入的黑白图像加上外围为：\n");

	//把周围一圈都加上0,防止搜索过界 没有必要设0，全局变量本来就都是0，如果真的要设置成0，可以使用
	//memset(graph,0,sizeof(graph)); 
//	for(int i=0; i<graphNum+2; i++)
//		graph[0][i]=0;
//
//	for(int i=0; i<graphNum+2; i++)
//		graph[graphNum+1][i]=0;
//
     
    
	for(int i=0; i<graphNum; i++)//尝试每次读入一行 
	{
		//fscanf(fp,"%s",s); 这样不行，这样空格也算一个字符		 
		for(int j=0; j<graphNum; j++)
		    fscanf(fp,"%d",&graph[i+1][j+1]); //平移，原来的(0,0)移到了(1,1) 
	}


	for(int i=0; i<graphNum+2; i++)
	{
		for(int j=0; j<graphNum+2; j++)
			printf("%d ",graph[i][j]);
		printf("\n");
	}

	int count=0;//八连块的数目

	for(int i=1; i<graphNum+1; i++)
	{
		for(int j=1; j<graphNum+1; j++)
			if(graph[i][j]==1&&visited[i][j]==0)
			{
				count++;
				visited[i][j]=1;
				printf("正在搜索(%d,%d)\n",i,j);
				dfs(i,j);

			}

	}

	printf("有%d个八连块\n",count);

}

void dfs(int p,int q)
{

	if(graph[p][q+1]==1&&visited[p][q+1]==0)//右边
	{
		visited[p][q+1]=1;
		dfs(p,q+1);//以它右边的点为中心点开始拓展，拓展完了开始拓展左下的点 
	}

	if(graph[p+1][q-1]==1&&visited[p+1][q-1]==0)//左下
	{
		visited[p+1][q-1]=1;
		dfs(p+1,q-1);
	}

	if(graph[p+1][q]==1&&visited[p+1][q]==0)//下边
	{
		visited[p+1][q]=1;
		dfs(p+1,q);
	}

	if(graph[p+1][q+1]==1&&visited[p+1][q+1]==0)//右下
	{
		visited[p+1][q+1]=1;
		dfs(p+1,q+1);
	}

}
