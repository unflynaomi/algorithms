//ʹ��kosaraju�㷨(����dfs)������ͼ��ǿ��ͨ����
//input:Kosaraju.txt ����ս������ƾ��� p320�ϵ�ͼ
//��һ��3 3 ��ʾ�м����� �� ������ �ڶ��п�ʼ �����˱�
#include<stdio.h> 
#include <stdlib.h>
int vertexNum=10000; 
typedef struct Edge
{
	int id;
	struct Edge* next;
}Edge;

int visited[10000];
Edge* graph[10000];//ȫ�ֱ�����ָ���ʼ��ΪNULL ʹ��%p������printf�����ָ�� 
Edge* reverseGraph[10000];//һ��ʼ�ͻ������ͼ������ 
int stack[10000];
int stackTop=-1;
void dfs(int curVex);
void reverseDfs(int curVex);

int main()
{
	
	int edgeNum;//�ܱ��� 
    FILE *fp;
	if((fp=fopen("kosaraju.txt","r"))==NULL)
	{
		printf("Cannot open file !");
		exit(1);
	}

	fscanf(fp,"%d %d",&vertexNum,&edgeNum);//ԭ��д���� #define vertexNum 10000 int tmp��������  vertexNum=tmp �ܻ��� ��Ϊ vertexNum ֻ��10000�Ĵ����ʶ��� 
	
	int from=0;
	int to=0;
	
	while(edgeNum--)
	{
		Edge* newEdge=(Edge*)malloc(sizeof(Edge));//��ȫ�ֱ������� newEdge->next��ʼ����ΪNULL���ǲ�ȷ����ָ�� 		
		Edge* reverseNewEdge=(Edge*)malloc(sizeof(Edge));
		newEdge->next=NULL;
		reverseNewEdge->next=NULL;
		
		
		fscanf(fp,"%d %d",&from,&to);
		newEdge->id=to;//from->to
		reverseNewEdge->id=from;//to->from
	
	    if(graph[from]==NULL)//ԭ��д����   Edge* p=graph[from]; p=newEdge ����û�ã�ֻ�ǳ�ʼ������ʱ���� 
	    {
	    	graph[from]=newEdge;	    	
		}	       
	    else
		{		    
		    Edge* p=graph[from];
			while(p->next!=NULL)
			{
				p=p->next;
				
			}
			p->next=newEdge;
		}   
		
		//��������ͼ		
		if(reverseGraph[to]==NULL)//ԭ��д����   Edge* p=graph[from]; p=newEdge ����û�ã�ֻ�ǳ�ʼ������ʱ���� 
	    {
	    	reverseGraph[to]=reverseNewEdge;	    	
		}	       
	    else
		{		    
		    Edge* p=reverseGraph[to];
			while(p->next!=NULL)
			{
				p=p->next;
				
			}
			p->next=reverseNewEdge;
		}   
		
		
		
		
	}
	
	printf("ͼΪ:\n");
	for(int i=0;i<vertexNum;i++)
	{
		Edge* p=graph[i];
		printf("%d: ",i);
		while(p!=NULL)
		{
			printf("%d ",p->id);
			p=p->next;
		}
		printf("\n");
	}
	
	printf("����ͼΪ:\n");
		for(int i=0;i<vertexNum;i++)
	{
		Edge* p=reverseGraph[i];
		printf("%d: ",i);
		while(p!=NULL)
		{
			printf("%d ",p->id);
			p=p->next;
		}
		printf("\n");
	}
	//ͼ�Ѿ�������ڽӱ�
	
	for(int i=0;i<vertexNum;i++)
	{
		if(visited[i]==0)
		   dfs(i);
	}
	
	printf("stack����Ϊ:\n");
	for(int i=stackTop;i>=0;i--)
	{
		visited[i]=0;//����visited���� 
		printf("%d\n",stack[i]);
	}
	
	printf("����ͼ����ͨ����Ϊ:\n");
	//����dfs��ʼ
	 for(int i=stackTop;i>=0;i--)//ע�����ﲻ�����һ��dfs���������ն�����ŵĴ�С˳�����������ʹ��stack����dfsջ���ģ���dfs�����˳��
	 	 //����������˳�����������ͨ�������Ǵ�� 
	{
		if(visited[stack[i]]==0)
		{
			reverseDfs(stack[i]);//���ʵľ�����stack[i]��ͷ����ͨ���� 
			printf("\n");
		} 
		   
	}
	 
}

void dfs(int curVex)
{
	visited[curVex]=1;
	Edge* p=graph[curVex];
	while(p!=NULL)
	{
		if(visited[p->id]==0)
		   dfs(p->id);
		p=p->next;   
	}
	stack[++stackTop]=curVex;	
	
}

void reverseDfs(int curVex)
{
	visited[curVex]=1;
	printf("%d ",curVex);
	Edge* p=reverseGraph[curVex];
	while(p!=NULL)
	{
		if(visited[p->id]==0)
		   reverseDfs(p->id);
		p=p->next;   
	}
}
