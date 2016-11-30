//使用图的深度优先搜索输出无向图中的环，比如1->2-3->4 
#include<stdio.h>
#include <stdlib.h>
#include<vector>
#include<iostream>
#define MAX 50

using namespace std;
void dfsVisit(vector<vector<int> >&graph, int node, vector<int>&visit,
               vector<int>&father);
void dfs(vector<vector<int> >&graph);
int main() 
{
	
	FILE *fp;
	if((fp=fopen("GraphCycle.txt","r"))==NULL)
	{
		printf("Cannot open file !");
		exit(1);
	}
	int vertexNum=0;
	fscanf(fp,"%d",&vertexNum);
	vector<vector<int> >graph;
	graph.resize(vertexNum);
	
	int tmp=0;
	for(int i=0;i<vertexNum;i++)
	   for(int j=0;j<vertexNum;j++)
	   {
	   	   fscanf(fp,"%d",&tmp);
	   	   graph[i].push_back(tmp);
	   }
	      
	      
	printf("有%d个结点\n",vertexNum);
	for(int i=0;i<vertexNum;i++)
	{	
	   for(int j=0;j<vertexNum;j++)
	      printf("%d ",graph[i][j]);    
	   printf("\n");   
    }
    printf("\n");
    
    dfs(graph);
    
   
}

void dfsVisit(vector<vector<int> >&graph, int node, vector<int>&visit,
               vector<int>&father)
{
    int n = graph.size();
    visit[node] = 1;
    //cout<<node<<"-\n";
    for(int i = 0; i < n; i++)
        if(i != node && graph[node][i] != 0)
        {
            if(visit[i] == 1 && i != father[node])//找到一个环
            {
                int tmp = node;
                cout<<"cycle: ";
                while(tmp != i)
                {
                    cout<<tmp<<"->";
                    tmp = father[tmp];
                }
                cout<<tmp<<endl;
            }
            else if(visit[i] == 0)
            {
                father[i] = node;
                dfsVisit(graph, i, visit, father);
            }
        }
    visit[node] = 2;//把状态设置为2，是为了防止在回溯的时候，把已经计算过的环再计算一次 
}
 
void dfs(vector<vector<int> >&graph)
{
    int n = graph.size();
    vector<int> visit(n, 0); //visit 0表示没有访问过，1表示访问过，2表示它所有的邻接结点都访问过了，这个结点死了 
    vector<int> father(n, -1);// father[i] 记录遍历过程中i的父节点
    for(int i = 0; i < n; i++)
        if(visit[i] == 0)
            dfsVisit(graph, i, visit, father);
}
