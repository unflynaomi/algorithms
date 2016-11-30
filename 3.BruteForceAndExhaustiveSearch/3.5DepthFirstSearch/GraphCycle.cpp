//ʹ��ͼ��������������������ͼ�еĻ�������1->2-3->4 
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
	      
	      
	printf("��%d�����\n",vertexNum);
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
            if(visit[i] == 1 && i != father[node])//�ҵ�һ����
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
    visit[node] = 2;//��״̬����Ϊ2����Ϊ�˷�ֹ�ڻ��ݵ�ʱ�򣬰��Ѿ�������Ļ��ټ���һ�� 
}
 
void dfs(vector<vector<int> >&graph)
{
    int n = graph.size();
    vector<int> visit(n, 0); //visit 0��ʾû�з��ʹ���1��ʾ���ʹ���2��ʾ�����е��ڽӽ�㶼���ʹ��ˣ����������� 
    vector<int> father(n, -1);// father[i] ��¼����������i�ĸ��ڵ�
    for(int i = 0; i < n; i++)
        if(visit[i] == 0)
            dfsVisit(graph, i, visit, father);
}
