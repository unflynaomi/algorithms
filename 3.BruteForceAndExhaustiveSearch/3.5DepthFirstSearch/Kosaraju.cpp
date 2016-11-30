//使用kosaraju算法(两次dfs)求有向图的强连通分量
//input:Kosaraju.txt 是挑战程序设计竞赛 p320上的图
//第一行3 3 表示有几个点 和 几条边 第二行开始 描述了边
#include<stdio.h> 
#include <stdlib.h>
int vertexNum=10000; 
typedef struct Edge
{
	int id;
	struct Edge* next;
}Edge;

int visited[10000];
Edge* graph[10000];//全局变量，指针初始化为NULL 使用%p可以在printf中输出指针 
Edge* reverseGraph[10000];//一开始就会把逆向图构建好 
int stack[10000];
int stackTop=-1;
void dfs(int curVex);
void reverseDfs(int curVex);

int main()
{
	
	int edgeNum;//总边数 
    FILE *fp;
	if((fp=fopen("kosaraju.txt","r"))==NULL)
	{
		printf("Cannot open file !");
		exit(1);
	}

	fscanf(fp,"%d %d",&vertexNum,&edgeNum);//原来写的是 #define vertexNum 10000 int tmp读入结点数  vertexNum=tmp 很荒谬 因为 vertexNum 只是10000的代名词而已 
	
	int from=0;
	int to=0;
	
	while(edgeNum--)
	{
		Edge* newEdge=(Edge*)malloc(sizeof(Edge));//非全局变量，其 newEdge->next初始化不为NULL，是不确定的指向 		
		Edge* reverseNewEdge=(Edge*)malloc(sizeof(Edge));
		newEdge->next=NULL;
		reverseNewEdge->next=NULL;
		
		
		fscanf(fp,"%d %d",&from,&to);
		newEdge->id=to;//from->to
		reverseNewEdge->id=from;//to->from
	
	    if(graph[from]==NULL)//原来写的是   Edge* p=graph[from]; p=newEdge 这样没用，只是初始化了临时变量 
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
		
		//构建反向图		
		if(reverseGraph[to]==NULL)//原来写的是   Edge* p=graph[from]; p=newEdge 这样没用，只是初始化了临时变量 
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
	
	printf("图为:\n");
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
	
	printf("逆向图为:\n");
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
	//图已经变成了邻接表
	
	for(int i=0;i<vertexNum;i++)
	{
		if(visited[i]==0)
		   dfs(i);
	}
	
	printf("stack内容为:\n");
	for(int i=stackTop;i>=0;i--)
	{
		visited[i]=0;//重设visited数组 
		printf("%d\n",stack[i]);
	}
	
	printf("有向图的连通分量为:\n");
	//反向dfs开始
	 for(int i=stackTop;i>=0;i--)//注意这里不是像第一次dfs那样，按照顶点序号的大小顺序遍历，而是使用stack，先dfs栈顶的，再dfs下面的顺序
	 	 //如果不是这个顺序，求出来的连通分量就是错的 
	{
		if(visited[stack[i]]==0)
		{
			reverseDfs(stack[i]);//访问的就是以stack[i]打头的连通分量 
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
