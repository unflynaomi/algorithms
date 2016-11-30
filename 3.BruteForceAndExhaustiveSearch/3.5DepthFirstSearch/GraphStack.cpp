//ͼ��������������ǵݹ�棬ʹ��stack,ͼ�������ڽӾ���� ��Դ��http://codeup.cn/problem.php?cid=100000480&pid=0 
//GraphRecursion2.txt������p123��ͼ 
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
		   dfs(i);//ÿ�ζ��ܷ���һ����ͨ���� 
	}    
	printf("\n");  
        
}

//ÿ�ζ���ջ����δ���ʹ����ڽӽ�����ջ���������ʣ���û���ڽӽ��û�����ʹ����͵�ջ��������������ֱ��ջΪ�գ��ٷ�����һ����ͨ���� 
//�����ʵ�ȵݹ�ʵ�ֻ�Ҫֱ�ۣ�һ���ڽӽ�㷭����һ����һ����һ�����Ҳ������Ժ󣬾ͻص���һ������δ���ʵ��ڽӽ��Ľ�㣬�ٷ���
void dfs(int startPoint)
{
	int stack[MAX];
	int top=-1;
	stack[++top]=startPoint;
	visited[startPoint]=1;
	printf("%d ",startPoint);
	int neighbour=0;
	while(top!=-1)//��ջ��Ϊ�� 
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

int firstNonVisitedVertex(int currentVertex)//����currentVertex�ĵ�һ��δ�����ʹ����ڽӽ�㣬��������ھͷ���-1 
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
