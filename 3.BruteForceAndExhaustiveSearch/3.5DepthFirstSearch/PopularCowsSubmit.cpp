//ʹ��kosaraju�㷨(����dfs)��� POJ No.2186 Popular Cows����  ������oj�ύ�İ汾 
//input:Kosaraju.txt ����ս������ƾ��� p320�ϵ�ͼ
//��һ��3 3 ��ʾ�м����� �� ������ �ڶ��п�ʼ �����˱� ע�ⶥ���Ŵ�1��ʼ������Ҫ����ɴ�0��ʼ 
#include<stdio.h> 
#include <stdlib.h>
#include<string.h>
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
int topology[10000];//��¼��ÿ������������� 
int stackTop=-1;
void dfs(int curVex);
void reverseDfs(int curVex,int curTopology); 

int main()
{
	
	int edgeNum;//�ܱ��� 
    

	scanf("%d %d",&vertexNum,&edgeNum);//ԭ��д���� #define vertexNum 10000 int tmp��������  vertexNum=tmp �ܻ��� ��Ϊ vertexNum ֻ��10000�Ĵ����ʶ��� 
	
	int from=0;
	int to=0;
	
	while(edgeNum--)
	{
		Edge* newEdge=(Edge*)malloc(sizeof(Edge));//��ȫ�ֱ������� newEdge->next��ʼ����ΪNULL���ǲ�ȷ����ָ�� 		
		Edge* reverseNewEdge=(Edge*)malloc(sizeof(Edge));
		newEdge->next=NULL;
		reverseNewEdge->next=NULL;
		
		
		scanf("%d %d",&from,&to);
		from--;to--;//����ɱ�Ŵ�0��ʼ 
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
	
	//printf("ͼΪ:\n");
//	for(int i=0;i<vertexNum;i++)
//	{
//		Edge* p=graph[i];
//		printf("%d: ",i);
//		while(p!=NULL)
//		{
//			printf("%d ",p->id);
//			p=p->next;
//		}
//		printf("\n");
//	}
//	
//	printf("����ͼΪ:\n");
//		for(int i=0;i<vertexNum;i++)
//	{
//		Edge* p=reverseGraph[i];
//		printf("%d: ",i);
//		while(p!=NULL)
//		{
//			printf("%d ",p->id);
//			p=p->next;
//		}
//		printf("\n");
//	}
	//ͼ�Ѿ�������ڽӱ�
	
	for(int i=0;i<vertexNum;i++)
	{
		if(visited[i]==0)
		   dfs(i);
	}
	
//	printf("stack����Ϊ:\n");
	for(int i=stackTop;i>=0;i--)//stackTopָ��ջ��Ԫ�� 
	{
		visited[i]=0;//����visited���� 
//		printf("%d\n",stack[i]);
	}
	
//	printf("����ͼ����ͨ����Ϊ:\n");
	int curTopology=0; 
	//����dfs��ʼ
	 for(int i=stackTop;i>=0;i--)//ע�����ﲻ�����һ��dfs���������ն�����ŵĴ�С˳�����������ʹ��stack����dfsջ���ģ���dfs�����˳��
	 	 //����������˳�����������ͨ�������Ǵ��,�������������������ô���8���ͻ��9һ����ͨ���� 
	{
		if(visited[stack[i]]==0)
		{
			reverseDfs(stack[i],curTopology++);//���ʵľ�����stack[i]��ͷ����ͨ���� 
//			printf("\n");
		} 
		   
	}
	
	int num=0;
	int candidateComponet=0;
	
	for(int i=0;i<vertexNum;i++)
	{
		if(topology[i]==curTopology-1)
		{
			candidateComponet=i;//i���ҵ���������ߵģ�Ҳ���ǳ���Ϊ0����ͨ�������һ������
			num++; 
		}
		
	} 
	
	//����ڷ���ͼ�У���candidateComponet�ܲ��ܵ����������ж��㣬����ڷ���ͼ�п��ԣ���ô������ͼ�У�����������Ҳ�ܵ��� candidateComponet
	//˵�������ǰ�ǿ��ͨ��������󣬵õ���DAGͼ�У�Ψһ����Ϊ0����ͨ���� 
	memset(visited,0,sizeof(visited));//����forѭ����Ҳ���԰�visited����Ϊ0
//	printf("\n��candidateComponet��ʼdfs:\n");
	reverseDfs(candidateComponet,0);//�� candidateComponet��ʼ�ڷ���ͼ��dfs����,�ڶ�������û��
	
	for(int i=0;i<vertexNum;i++)
	{
		if(visited[i]==0)//����� û�з��ʵ��Ľ��
		{
			num=0;
			break; 
		} 
	}
	//printf("\npopular cows����ĿΪ��%d\n",num);
	printf("%d\n",num);
	 
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

void reverseDfs(int curVex,int curTopology)
{
	visited[curVex]=1;
	topology[curVex]=curTopology;//��¼�µ�ǰ���������� 
	//printf("%d ",curVex);
	Edge* p=reverseGraph[curVex];
	while(p!=NULL)
	{
		if(visited[p->id]==0)
		   reverseDfs(p->id,curTopology);//ͬһ��ǿ��ͨ��������һ���������� 
		p=p->next;   
	}
}
