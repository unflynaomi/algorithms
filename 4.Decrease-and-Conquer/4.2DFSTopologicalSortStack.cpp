//ʹ��ͼ��������������ǵݹ�棬ʹ��stack����������� 
//GraphRecursion2.txt������p123��ͼ 
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
		   if(!dfs(i))
		    {
		    	printf("��ͼ�л�·��\n");
		    	return 0;//ÿ�ζ��ܷ���һ����ͨ���� 
			}   
	}    
	
	printf("��������Ϊ:");
	for(int i=index-1;i>=0;i--)
	  printf("%d ",topology[i]);
	printf("\n");
        
}

//ÿ�ζ���ջ����δ���ʹ����ڽӽ�����ջ���������ʣ���û���ڽӽ��û�����ʹ����͵�ջ��������������ֱ��ջΪ�գ��ٷ�����һ����ͨ���� 
//�����ʵ�ȵݹ�ʵ�ֻ�Ҫֱ�ۣ�һ���ڽӽ�㷭����һ����һ����һ�����Ҳ������Ժ󣬾ͻص���һ������δ���ʵ��ڽӽ��Ľ�㣬�ٷ���
bool dfs(int startPoint)
{
	int stack[MAX];
	int top=-1;
	stack[++top]=startPoint;
	visited[startPoint]=1;
	//printf("%d ",startPoint);
	int neighbour=-3;
	while(top!=-1)//��ջ��Ϊ�� 
	{
		neighbour=firstNonVisitedVertex(stack[top]);
		if(neighbour==-2)
		   return false;
		if(neighbour==-1)//Ҫ��ջ�� 
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

int firstNonVisitedVertex(int currentVertex)//����currentVertex�ĵ�һ��δ�����ʹ����ڽӽ�㣬��������ھͷ���-1 
{
	int result=0; 
		for(;result<graph.vertexNum;result++)
	{
		if(graph.matrix[currentVertex][result]==1)
		{
			if(visited[result]==1)//��������������ڷ��ʵĽ�㣬��˵�������˻�·
			   return -2; 
			else 
			   if(visited[result]==0)
			     return result;   
		}
	}
	
	if(result==graph.vertexNum)
	   return -1;
	
}


