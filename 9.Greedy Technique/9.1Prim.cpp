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
	
	int ifInTree[5];//是否已经加入树中
	memset(ifInTree,0,sizeof(ifInTree));
	
	ifInTree[0]=1;
	vector<int> inTree;
	inTree.push_back(0);
	
	int father[5];
	for(int i=0;i<5;i++)
	   father[i]=-1;
	
	while(inTree.size()<5)
	{
		int minWeight=100;
		int candidate=-1;
		int candidateFather=-1;
		for(int i=0;i<inTree.size();i++)//遍历所有最小生成树中的结点 
		{
			for(int j=0;j<graph[i].size();j++) //遍历某个结点的邻接结点 
			{
				if(!ifInTree[graph[i][j].vertex])
				{
					if(graph[i][j].weight<minWeight)
					{
						candidate=graph[i][j].vertex;
						minWeight=graph[i][j].weight;
						candidateFather=i;
					}
				}
			}
			
		}
		ifInTree[candidate]=1;
		inTree.push_back(candidate); 
		father[candidate]=candidateFather;
		cout<<"加入"<<candidate<<" 他的父亲为: "<<candidateFather<<endl;	
			
	 } 
}
