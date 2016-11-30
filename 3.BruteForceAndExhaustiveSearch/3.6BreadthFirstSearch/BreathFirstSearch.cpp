//基本纯正的深度优先，使用一个队
//输入GraphRecursion2.txt是书123页上的图 
#include<stdio.h>
#include <stdlib.h>
#define MAX 50
struct Graph
{
	int matrix[MAX][MAX];
	int vertexNum;
}graph;
int visited[MAX];
void bfs(int curVex);

int main()
{
	
	FILE *fp;
	if((fp=fopen("GraphRecursion2.txt","r"))==NULL)
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
	
	printf("宽度遍历序列为：\n");
	for(int i=0;i<graph.vertexNum;i++)
	{
		if(visited[i]==0)
		   bfs(i);
	}
	printf("\n");
}  

//bfs访问一个连通分量 
void bfs(int curVex)
{
	int queue[MAX];
	//int top,back=0;//队首和队尾都是0 这样写竟然不行！ top指针指向队首元素 
	int top=0;
	int back=0; 
	queue[back++]=curVex;//队尾指向最后一个元素的下一个位置	
	visited[curVex]=1;
	while(top!=back)//当队列不为空时	 
	{
		int v=queue[top];
		printf("%d ",v);//出队的时候访问,也可以在入队时访问，都一样	
		for(int i=0;i<graph.vertexNum;i++) 
		   if(graph.matrix[v][i]==1&&visited[i]==0)
		   {
		   	   queue[back++]=i;
		   	   visited[i]=1;//不是在它当头元素的时候，把它标为已访问，而是要在它入队的时候，标为已访问，否则会重复入队 
		   }		      
		top++;      
	 } 
	 
}
