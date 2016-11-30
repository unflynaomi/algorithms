//使用kosaraju算法(两次dfs)解决 POJ No.2186 Popular Cows问题  用于向oj提交的版本 
//input:Kosaraju.txt 是挑战程序设计竞赛 p320上的图
//第一行3 3 表示有几个点 和 几条边 第二行开始 描述了边 注意顶点标号从1开始，我们要换算成从0开始 
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
Edge* graph[10000];//全局变量，指针初始化为NULL 使用%p可以在printf中输出指针 
Edge* reverseGraph[10000];//一开始就会把逆向图构建好 
int stack[10000];
int topology[10000];//记录了每个顶点的拓扑序 
int stackTop=-1;
void dfs(int curVex);
void reverseDfs(int curVex,int curTopology); 

int main()
{
	
	int edgeNum;//总边数 
    

	scanf("%d %d",&vertexNum,&edgeNum);//原来写的是 #define vertexNum 10000 int tmp读入结点数  vertexNum=tmp 很荒谬 因为 vertexNum 只是10000的代名词而已 
	
	int from=0;
	int to=0;
	
	while(edgeNum--)
	{
		Edge* newEdge=(Edge*)malloc(sizeof(Edge));//非全局变量，其 newEdge->next初始化不为NULL，是不确定的指向 		
		Edge* reverseNewEdge=(Edge*)malloc(sizeof(Edge));
		newEdge->next=NULL;
		reverseNewEdge->next=NULL;
		
		
		scanf("%d %d",&from,&to);
		from--;to--;//换算成编号从0开始 
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
	
	//printf("图为:\n");
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
//	printf("逆向图为:\n");
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
	//图已经变成了邻接表
	
	for(int i=0;i<vertexNum;i++)
	{
		if(visited[i]==0)
		   dfs(i);
	}
	
//	printf("stack内容为:\n");
	for(int i=stackTop;i>=0;i--)//stackTop指向栈顶元素 
	{
		visited[i]=0;//重设visited数组 
//		printf("%d\n",stack[i]);
	}
	
//	printf("有向图的连通分量为:\n");
	int curTopology=0; 
	//反向dfs开始
	 for(int i=stackTop;i>=0;i--)//注意这里不是像第一次dfs那样，按照顶点序号的大小顺序遍历，而是使用stack，先dfs栈顶的，再dfs下面的顺序
	 	 //如果不是这个顺序，求出来的连通分量就是错的,如果还按顶点序来，那么结点8，就会和9一个连通分量 
	{
		if(visited[stack[i]]==0)
		{
			reverseDfs(stack[i],curTopology++);//访问的就是以stack[i]打头的连通分量 
//			printf("\n");
		} 
		   
	}
	
	int num=0;
	int candidateComponet=0;
	
	for(int i=0;i<vertexNum;i++)
	{
		if(topology[i]==curTopology-1)
		{
			candidateComponet=i;//i是我的拓扑序最高的，也就是出度为0的连通分量里的一个顶点
			num++; 
		}
		
	} 
	
	//检测在反向图中，从candidateComponet能不能到达其它所有顶点，如果在反向图中可以，那么在正向图中，从其它顶点也能到达 candidateComponet
	//说明它就是把强连通分量缩点后，得到的DAG图中，唯一出度为0的连通分量 
	memset(visited,0,sizeof(visited));//不用for循环，也可以把visited都置为0
//	printf("\n从candidateComponet开始dfs:\n");
	reverseDfs(candidateComponet,0);//从 candidateComponet开始在反向图中dfs遍历,第二个参数没用
	
	for(int i=0;i<vertexNum;i++)
	{
		if(visited[i]==0)//如果有 没有访问到的结点
		{
			num=0;
			break; 
		} 
	}
	//printf("\npopular cows的数目为：%d\n",num);
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
	topology[curVex]=curTopology;//记录下当前结点的拓扑序 
	//printf("%d ",curVex);
	Edge* p=reverseGraph[curVex];
	while(p!=NULL)
	{
		if(visited[p->id]==0)
		   reverseDfs(p->id,curTopology);//同一个强连通分量具有一样的拓扑序 
		p=p->next;   
	}
}
