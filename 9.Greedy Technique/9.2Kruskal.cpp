//��³˹�����㷨
//����ͨ���������С������

#include <stdio.h>
#include <stdlib.h>

#define MAXEDGE 20
#define MAXVEX  20
#define INFINITY 65535

typedef struct
{
	int arc[MAXVEX][MAXVEX];
	int numVertexes, numEdges;//������������
} MGraph;

typedef struct
{
	int begin;
	int end;
	int weight;
} Edge;  //�Ա߼�����Edge�ṹ�Ķ���

//����ͼ���ڽӾ���
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

//�������������
int cmp(const void* a, const void* b)
{
	return (*(Edge*)a).weight - (*(Edge*)b).weight;
}

//�ҵ����ڵ�
int Find(int *parent, int f)
{
	while ( parent[f] !=f)
	{
		f = parent[f];
	}
	return f;
}

// ������С������
void MiniSpanTree_Kruskal(MGraph G)
{
	int i, j, n, m;
	int k = 0;
	int parent[MAXVEX]; //����Ѱ�Ҹ��ڵ������

	Edge edges[MAXEDGE]; //����߼�����,edge�ĽṹΪbegin,end,weight,��Ϊ����

	// ���������߼����鲢����(���ڽӾ���ĶԽ����ұߵĲ��ִ���߼�������)
	for ( i = 0; i < G.numVertexes-1; i++)
	{
		for (j = i + 1; j < G.numVertexes; j++)
		{
			if (G.arc[i][j] < INFINITY)
			{
				edges[k].begin = i; //��Ž�С�Ľ��Ϊ��
				edges[k].end = j;   //��Žϴ�Ľ��Ϊβ
				edges[k].weight = G.arc[i][j];
				k++;
			}
		}
	}

	//Ϊ�߼�����Edge����
	qsort(edges, G.numEdges, sizeof(Edge), cmp);
	


	for (i = 0; i < G.numVertexes; i++)
		parent[i] = i;

	printf("��ӡ��С��������\n");
	for (i = 0; i < G.numEdges; i++)
	{
		n = Find(parent, edges[i].begin);//Ѱ�ұ�edge[i]�ġ��׽ڵ㡱������������
		m = Find(parent, edges[i].end);//Ѱ�ұ�edge[i]�ġ�β�ڵ㡱������������
		//printf("%d�ĸ��ڵ���%d,%d�ĸ��ڵ���%d\n",edges[i].begin,n,edges[i].end,m);

		//����n��m���ȣ�˵���������㲻��һ�����ڣ���������ߵļ��벻��ʹ�Ѿ�ѡ��ı߼�������·
		if (n != m)
		{
			//���µĴ����Ǵ���ģ�������end�ĸ�������ó�begin�����������������ϲ������ã� 
//			if(m<n)
//			{
//				parent[edges[i].begin]=edges[i].end;
//				printf("%d�ĸ��ڵ�Ϊ%d\n",edges[i].begin,edges[i].end);
//				
//			}
//		
//		    else
//		    {
//		    	parent[edges[i].end]=edges[i].begin;
//		    	printf("%d�ĸ��ڵ�Ϊ%d\n",edges[i].end,edges[i].begin);
//		    	
//			}
		       
			parent[n] = m;//������һ�����ĸ��ڵ���Ϊ��һ���������ӽ�㣬�����������ĺϲ� 
			printf("�����˱�: (%d, %d) %d\n", edges[i].begin, edges[i].end, edges[i].weight);
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
