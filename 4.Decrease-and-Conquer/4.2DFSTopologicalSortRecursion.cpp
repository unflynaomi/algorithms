//图的深度优先搜索递归版，图保存在邻接矩阵里， 来源：http://codeup.cn/problem.php?cid=100000480&pid=0
#include<stdio.h>
#include <stdlib.h>
#define MAX 50
int visited[MAX];//0表示没访问过，1表示正在访问，还有它的邻接结点没访问完，-1表示该结点已经访问结束
int topology[MAX];//拓扑排序
int index=0; //拓扑排序的索引 
struct Graph
{
	int matrix[MAX][MAX];
	int vertexNum;
}graph;
bool dfs(int currentVex);

int main() 
{
	
	FILE *fp;
	if((fp=fopen("topology1.txt","r"))==NULL)
	{
		printf("Cannot open file !");
		exit(1);
	}
	fscanf(fp,"%d",&graph.vertexNum);
	for(int i=0;i<graph.vertexNum;i++)
	   for(int j=0;j<graph.vertexNum;j++)
	      fscanf(fp,"%d",&graph.matrix[i][j]);
	      
	printf("有%d个结点\n",graph.vertexNum);
	for(int i=0;i<graph.vertexNum;i++)
	{	
	   for(int j=0;j<graph.vertexNum;j++)
	      printf("%d ",graph.matrix[i][j]);    
	   printf("\n");   
    }
    printf("\n");
    
    for(int i=0;i<graph.vertexNum;i++)
        visited[i]=0;
    
   
	for(int i=0;i<graph.vertexNum;i++)
	{
		if(visited[i]==0)
		   if(!dfs(i))//一枝连通分量 
		   {
		   	   printf("此图有环路！\n");
		       return 0;
		   }
	}    
	
	
	printf("拓扑排序为:");
	for(int i=index-1;i>=0;i--)
	  printf("%d ",topology[i]);
	printf("\n");
}

bool dfs(int currentVex)
{
	visited[currentVex]=1;//把visited改为1表示我正在访问它 
	
	for(int j=0;j<graph.vertexNum;j++)
	{
		if(graph.matrix[currentVex][j]==1)//对于全部的邻接顶点深度遍历 
		{
			if(visited[j]==1)
			   return false;//有环路
			else
			  if(visited[j]==0)    
			     if(!dfs(j))//如果dfs(j)返回的是true的话，不能也return true了事，因为我还要访问其它的邻接结点 
				    return false;
					 
		}
	}
	visited[currentVex]=-1;//它的邻接结点全部访问完了，就变成了-1 
	topology[index++]=currentVex;
	return true;//只有当所有的邻接结点都访问完了，我才可以返回真 
	
}
