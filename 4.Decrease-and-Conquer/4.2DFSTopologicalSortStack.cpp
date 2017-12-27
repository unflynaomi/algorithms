//使用图的深度优先搜索非递归版，使用stack完成拓扑排序 
//GraphRecursion2.txt是书上p123的图 
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
bool dfs(int startPoint);
int firstNonVisitedVertex(int currentVertex);
void printTopology(int current);

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
		   if(!dfs(i))
		    {
		    	printf("此图有环路！\n");
		    	return 0;//每次都能访问一个连通分量 
			}   
	}    
	
	printf("拓扑排序为:");
	for(int i=index-1;i>=0;i--)
	  printf("%d ",topology[i]);
	printf("\n");
        
}

//每次都把栈顶的未访问过的邻接结点放入栈顶，并访问，若没有邻接结点没被访问过，就弹栈，这样往复操作直到栈为空，再访问下一个连通分量 
//这个其实比递归实现还要直观，一个邻接结点翻出下一个，一个找一个，找不到了以后，就回到第一个还有未访问的邻接结点的结点，再访问
bool dfs(int startPoint)
{
	int stack[MAX];
	int top=-1;
	stack[++top]=startPoint;
	visited[startPoint]=1;
	//printf("%d ",startPoint);
	int neighbour=-3;
	while(top!=-1)//当栈不为空 
	{
		neighbour=firstNonVisitedVertex(stack[top]);
		if(neighbour==-2)
		   return false;
		if(neighbour==-1)//要弹栈了 
		{
			visited[stack[top]]=-1;
			topology[index++]=stack[top];
			top--;
		} 
		else
		{
			visited[neighbour]=1;
			//printf("%d ",neighbour);
			stack[++top]=neighbour;
			
		}    
		
	 } 
	 return true;

}

int firstNonVisitedVertex(int currentVertex)//返回currentVertex的第一个未被访问过的邻接结点，如果不存在就返回-1 
{
	int result=0; 
		for(;result<graph.vertexNum;result++)
	{
		if(graph.matrix[currentVertex][result]==1)
		{
			if(visited[result]==1)//如果遇到的是正在访问的结点，则说明遇到了回路
			   return -2; 
			else 
			   if(visited[result]==0)
			     return result;   
		}
	}
	
	if(result==graph.vertexNum)
	   return -1;
	
}


