//克鲁斯卡尔算法
//在连通网中求出最小生成树

#include <stdio.h>
#include <stdlib.h>

#define MAXEDGE 20
#define MAXVEX  20
#define INFINITY 65535

typedef struct
{
	int arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;//顶点数，边数
} MGraph;

typedef struct
{
	int begin;
	int end;
	int weight;
} Edge;  //对边集数组Edge结构的定义

//创建图的邻接矩阵
void CreateMGraph(MGraph *G)
{
	int i, j;

	G->numEdges=8;
	G->numVertexes=5;

	for (i = 0; i < G->numVertexes; i++)
	{
		for ( j = 0; j < G->numVertexes; j++)
		{
			if (i==j)
				G->arc[i][j]=0;
			else
				G->arc[i][j] = G->arc[j][i] = INFINITY;
		}
	}
	G->arc[0][1]=5;
	G->arc[0][2]=1;
	G->arc[1][2]=3;
	G->arc[2][3]=6;
	G->arc[1][4]=4;
	G->arc[2][4]=2;
	G->arc[0][3]=2;
	G->arc[3][4]=3;


	for(i = 0; i < G->numVertexes; i++)
	{
		for(j = i; j < G->numVertexes; j++)
		{
			G->arc[j][i] =G->arc[i][j];
		}
	}

}

//快速排序的条件
int cmp(const void* a, const void* b)
{
	return (*(Edge*)a).weight - (*(Edge*)b).weight;
}

//找到根节点
int Find(int *parent, int f)
{
	while ( parent[f] !=f)
	{
		f = parent[f];
	}
	return f;
}

// 生成最小生成树
void MiniSpanTree_Kruskal(MGraph G)
{
	int i, j, n, m;
	int k = 0;
	int parent[MAXVEX]; //用于寻找根节点的数组

	Edge edges[MAXEDGE]; //定义边集数组,edge的结构为begin,end,weight,均为整型

	// 用来构建边集数组并排序(将邻接矩阵的对角线右边的部分存入边集数组中)
	for ( i = 0; i < G.numVertexes-1; i++)
	{
		for (j = i + 1; j < G.numVertexes; j++)
		{
			if (G.arc[i][j] < INFINITY)
			{
				edges[k].begin = i; //编号较小的结点为首
				edges[k].end = j;   //编号较大的结点为尾
				edges[k].weight = G.arc[i][j];
				k++;
			}
		}
	}

	//为边集数组Edge排序
	qsort(edges, G.numEdges, sizeof(Edge), cmp);
	


	for (i = 0; i < G.numVertexes; i++)
		parent[i] = i;

	printf("打印最小生成树：\n");
	for (i = 0; i < G.numEdges; i++)
	{
		n = Find(parent, edges[i].begin);//寻找边edge[i]的“首节点”所在树的树根
		m = Find(parent, edges[i].end);//寻找边edge[i]的“尾节点”所在树的树根
		//printf("%d的父节点是%d,%d的父节点是%d\n",edges[i].begin,n,edges[i].end,m);

		//假如n与m不等，说明两个顶点不在一棵树内，因此这条边的加入不会使已经选择的边集产生回路
		if (n != m)
		{
			//以下的代码是错误的，仅仅把end的父结点设置成begin，并不能起到两棵树合并的作用， 
//			if(m<n)
//			{
//				parent[edges[i].begin]=edges[i].end;
//				printf("%d的父节点为%d\n",edges[i].begin,edges[i].end);
//				
//			}
//		
//		    else
//		    {
//		    	parent[edges[i].end]=edges[i].begin;
//		    	printf("%d的父节点为%d\n",edges[i].end,edges[i].begin);
//		    	
//			}
		       
			parent[n] = m;//必须是一棵树的根节点作为另一棵树结点的子结点，才能做到树的合并 
			printf("并入了边: (%d, %d) %d\n", edges[i].begin, edges[i].end, edges[i].weight);
		}
	}
}

int main(void)
{
	MGraph G;
	CreateMGraph(&G);
	MiniSpanTree_Kruskal(G);

	return 0;
}
