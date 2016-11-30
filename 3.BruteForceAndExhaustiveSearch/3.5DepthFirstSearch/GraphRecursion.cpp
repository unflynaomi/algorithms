//ͼ��������������ݹ�棬ͼ�������ڽӾ���� ��Դ��http://codeup.cn/problem.php?cid=100000480&pid=0
#include<stdio.h>
#include <stdlib.h>
#define MAX 50
int visited[MAX];
struct Graph
{
	int matrix[MAX][MAX];
	int vertexNum;
}graph;
void dfs(int currentVex);

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
	      
	printf("��%d�����\n",graph.vertexNum);
	for(int i=0;i<graph.vertexNum;i++)
	{	
	   for(int j=0;j<graph.vertexNum;j++)
	      printf("%d ",graph.matrix[i][j]);    
	   printf("\n");   
    }
    printf("\n");
    
    for(int i=0;i<graph.vertexNum;i++)
        visited[i]=0;
    
    printf("������ȱ�������Ϊ�� "); 
	for(int i=0;i<graph.vertexNum;i++)
	{
		if(visited[i]==0)
		   dfs(i);
	}    
	printf("\n");
}

void dfs(int currentVex)
{
	visited[currentVex]=1;
	printf("%d ",currentVex);
	for(int j=0;j<graph.vertexNum;j++)
	{
		if(graph.matrix[currentVex][j]==1)//����ȫ�����ڽӶ�����ȱ��� 
		{
			if(visited[j]!=1)
			   dfs(j); 
		}
	}
	
}
