//ͼ��������������ݹ�棬ͼ�������ڽӾ���� ��Դ��http://codeup.cn/problem.php?cid=100000480&pid=0
#include<stdio.h>
#include <stdlib.h>
#define MAX 50
int visited[MAX];//0��ʾû���ʹ���1��ʾ���ڷ��ʣ����������ڽӽ��û�����꣬-1��ʾ�ý���Ѿ����ʽ���
int topology[MAX];//��������
int index=0; //������������� 
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
    
   
	for(int i=0;i<graph.vertexNum;i++)
	{
		if(visited[i]==0)
		   if(!dfs(i))//һ֦��ͨ���� 
		   {
		   	   printf("��ͼ�л�·��\n");
		       return 0;
		   }
	}    
	
	
	printf("��������Ϊ:");
	for(int i=index-1;i>=0;i--)
	  printf("%d ",topology[i]);
	printf("\n");
}

bool dfs(int currentVex)
{
	visited[currentVex]=1;//��visited��Ϊ1��ʾ�����ڷ����� 
	
	for(int j=0;j<graph.vertexNum;j++)
	{
		if(graph.matrix[currentVex][j]==1)//����ȫ�����ڽӶ�����ȱ��� 
		{
			if(visited[j]==1)
			   return false;//�л�·
			else
			  if(visited[j]==0)    
			     if(!dfs(j))//���dfs(j)���ص���true�Ļ�������Ҳreturn true���£���Ϊ�һ�Ҫ�����������ڽӽ�� 
				    return false;
					 
		}
	}
	visited[currentVex]=-1;//�����ڽӽ��ȫ���������ˣ��ͱ����-1 
	topology[index++]=currentVex;
	return true;//ֻ�е����е��ڽӽ�㶼�������ˣ��Ҳſ��Է����� 
	
}
