//����������������ȣ�ʹ��һ����
//����GraphRecursion2.txt����123ҳ�ϵ�ͼ 
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
	
	printf("��ȱ�������Ϊ��\n");
	for(int i=0;i<graph.vertexNum;i++)
	{
		if(visited[i]==0)
		   bfs(i);
	}
	printf("\n");
}  

//bfs����һ����ͨ���� 
void bfs(int curVex)
{
	int queue[MAX];
	//int top,back=0;//���׺Ͷ�β����0 ����д��Ȼ���У� topָ��ָ�����Ԫ�� 
	int top=0;
	int back=0; 
	queue[back++]=curVex;//��βָ�����һ��Ԫ�ص���һ��λ��	
	visited[curVex]=1;
	while(top!=back)//�����в�Ϊ��ʱ	 
	{
		int v=queue[top];
		printf("%d ",v);//���ӵ�ʱ�����,Ҳ���������ʱ���ʣ���һ��	
		for(int i=0;i<graph.vertexNum;i++) 
		   if(graph.matrix[v][i]==1&&visited[i]==0)
		   {
		   	   queue[back++]=i;
		   	   visited[i]=1;//����������ͷԪ�ص�ʱ�򣬰�����Ϊ�ѷ��ʣ�����Ҫ������ӵ�ʱ�򣬱�Ϊ�ѷ��ʣ�������ظ���� 
		   }		      
		top++;      
	 } 
	 
}
