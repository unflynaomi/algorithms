#include<iostream>
#include<vector>
//#include<cstring>
#include <string.h>
using namespace std;
class Edge
{
	public:
		int vertex;
		int weight;
        Edge(int vertexp,int weightp):vertex(vertexp),weight(weightp){} 		
};

int main()
{
	vector<vector<Edge> >graph;
	graph.resize(5);
	graph[0].push_back(Edge(1,5));
	graph[0].push_back(Edge(2,1));
	graph[0].push_back(Edge(3,2));
	
	graph[1].push_back(Edge(0,5));
	graph[1].push_back(Edge(2,3));
	graph[1].push_back(Edge(4,4));
	
	graph[2].push_back(Edge(0,1));
	graph[2].push_back(Edge(1,3));
	graph[2].push_back(Edge(3,6));
	graph[2].push_back(Edge(4,2));
	
	graph[3].push_back(Edge(0,2));
	graph[3].push_back(Edge(2,6));
	graph[3].push_back(Edge(4,3));
	
	graph[4].push_back(Edge(1,4));
	graph[4].push_back(Edge(2,2));
	graph[4].push_back(Edge(3,3));
	
	int ifInTree[5];//�Ƿ��Ѿ���������
	memset(ifInTree,0,sizeof(ifInTree));
	
	int lowcost[5];
	for(int i=0;i<5;i++)
	   lowcost[i]=100;
	
	
	int father[5];
	for(int i=0;i<5;i++)
	   father[i]=-1;   
	
	int count=1;
	ifInTree[0]=1;
	lowcost[0]=0; 
	lowcost[1]=5;  father[1]=0;
	lowcost[2]=1;  father[2]=0; 
	lowcost[3]=2;  father[3]=0; 
	
	
	
	
	while(count<5)
	{
		int minWeight=100;
		int candidate=-1;
		
		
		//��lowcost��һ���ҵ���С��Ȩֵ ������չ�� 
		for(int i=0;i<5;i++)
		{
			if(!ifInTree[i]&&lowcost[i]<minWeight)
			{
				minWeight=lowcost[i];
				candidate=i;
			}
			
		}
		ifInTree[candidate]=1;
		count++;
		cout<<"����"<<candidate<<" ���ĸ���Ϊ: "<<father[candidate]<<endl;	
		
		//����lowcost: ������չ��Ĳ�������������ڽӽ�㣬������������������������·�� 
		for(int j=0;j<graph[candidate].size();j++)
		{
			int neighbor=graph[candidate][j].vertex;
			if(!ifInTree[neighbor]&&graph[candidate][j].weight<lowcost[neighbor])
			{
				lowcost[neighbor]=graph[candidate][j].weight;
				father[neighbor]=candidate;
			}
		}
			
	 } 
}
