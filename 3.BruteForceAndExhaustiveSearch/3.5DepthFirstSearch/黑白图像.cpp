//�㷨�������ž��� P106 ͼ �ڰ�ͼ������
#include<stdio.h>
#include <stdlib.h>
#define MAX 50
int graph[MAX][MAX];
int visited[MAX][MAX];
void dfs(int p,int q);
int main()
{
	int graphNum;
	FILE *fp;
	if((fp=fopen("�ڰ�ͼ��.txt","r"))==NULL)
	{
		printf("Cannot open file !");
		exit(1);
	}
	fscanf(fp,"%d",&graphNum);

	printf("����ĺڰ�ͼ�������ΧΪ��\n");

	//����ΧһȦ������0,��ֹ�������� û�б�Ҫ��0��ȫ�ֱ��������Ͷ���0��������Ҫ���ó�0������ʹ��
	//memset(graph,0,sizeof(graph)); 
//	for(int i=0; i<graphNum+2; i++)
//		graph[0][i]=0;
//
//	for(int i=0; i<graphNum+2; i++)
//		graph[graphNum+1][i]=0;
//
     
    
	for(int i=0; i<graphNum; i++)//����ÿ�ζ���һ�� 
	{
		//fscanf(fp,"%s",s); �������У������ո�Ҳ��һ���ַ�		 
		for(int j=0; j<graphNum; j++)
		    fscanf(fp,"%d",&graph[i+1][j+1]); //ƽ�ƣ�ԭ����(0,0)�Ƶ���(1,1) 
	}


	for(int i=0; i<graphNum+2; i++)
	{
		for(int j=0; j<graphNum+2; j++)
			printf("%d ",graph[i][j]);
		printf("\n");
	}

	int count=0;//���������Ŀ

	for(int i=1; i<graphNum+1; i++)
	{
		for(int j=1; j<graphNum+1; j++)
			if(graph[i][j]==1&&visited[i][j]==0)
			{
				count++;
				visited[i][j]=1;
				printf("��������(%d,%d)\n",i,j);
				dfs(i,j);

			}

	}

	printf("��%d��������\n",count);

}

void dfs(int p,int q)
{

	if(graph[p][q+1]==1&&visited[p][q+1]==0)//�ұ�
	{
		visited[p][q+1]=1;
		dfs(p,q+1);//�����ұߵĵ�Ϊ���ĵ㿪ʼ��չ����չ���˿�ʼ��չ���µĵ� 
	}

	if(graph[p+1][q-1]==1&&visited[p+1][q-1]==0)//����
	{
		visited[p+1][q-1]=1;
		dfs(p+1,q-1);
	}

	if(graph[p+1][q]==1&&visited[p+1][q]==0)//�±�
	{
		visited[p+1][q]=1;
		dfs(p+1,q);
	}

	if(graph[p+1][q+1]==1&&visited[p+1][q+1]==0)//����
	{
		visited[p+1][q+1]=1;
		dfs(p+1,q+1);
	}

}
