//图的深度优先搜索非递归版，使用stack,图保存在邻接矩阵里， 来源：http://codeup.cn/problem.php?cid=100000480&pid=0 
//GraphRecursion2.txt是书上p123的图 
#include<stdio.h>
#include <stdlib.h>
#define MAX 50
int visited[MAX];
struct Graph
{
	int matrix[MAX][MAX];
	int vertexNum;
}graph;
void dfs(int startPoint);
int firstNonVisitedVertex(int currentVertex);

int main()
{
	FILE *fp;
	if((fp=fopen("GraphRecursion.txt","r"))==NULL)
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
    
	printf("深度优先遍历序列为： ");    
    for(int i=0;i<graph.vertexNum;i++)
	{
		if(visited[i]==0)
		   dfs(i);//每次都能访问一个连通分量 
	}    
	printf("\n");  
        
}

//每次都把栈顶的未访问过的邻接结点放入栈顶，并访问，若没有邻接结点没被访问过，就弹栈，这样往复操作直到栈为空，再访问下一个连通分量 
//这个其实比递归实现还要直观，一个邻接结点翻出下一个，一个找一个，找不到了以后，就回到第一个还有未访问的邻接结点的结点，再访问
void dfs(int startPoint)
{
	int stack[MAX];
	int top=-1;
	stack[++top]=startPoint;
	visited[startPoint]=1;
	printf("%d ",startPoint);
	int neighbour=0;
	while(top!=-1)//当栈不为空 
	{
		neighbour=firstNonVisitedVertex(stack[top]);
		if(neighbour!=-1)
		{
			visited[neighbour]=1;
			printf("%d ",neighbour);
			stack[++top]=neighbour;
		} 
		else
		    top--;
		
	 } 

}

int firstNonVisitedVertex(int currentVertex)//返回currentVertex的第一个未被访问过的邻接结点，如果不存在就返回-1 
{
	int result=0; 
		for(;result<graph.vertexNum;result++)
	{
		if(graph.matrix[currentVertex][result]==1)
		{
			if(visited[result]!=1)
			   return result; 
		}
	}
	
	if(result==graph.vertexNum)
	   return -1;
	
}
