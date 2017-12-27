//���η��������� 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 50

 
struct Graph
{
	int matrix[MAX][MAX];
	int vertexNum;
}graph;


int main() 
{
	
	FILE *fp;
	if((fp=fopen("topologyCircle.txt","r"))==NULL)
	{
		printf("Cannot open file !");
		exit(1);
	}
	
	
	fscanf(fp,"%d",&graph.vertexNum);
	int incoming[graph.vertexNum];//ͳ����ȵ����� 
	memset(incoming,0,sizeof(incoming));
	int sorted[graph.vertexNum]; //�Ƿ��Ѿ��Ź��� 
	memset(sorted,0,sizeof(sorted));
	int topology[graph.vertexNum];//��������
    int index=0; //�������������
	
	for(int i=0;i<graph.vertexNum;i++)
	   for(int j=0;j<graph.vertexNum;j++)
	   { 
	      fscanf(fp,"%d",&graph.matrix[i][j]);
	      if(graph.matrix[i][j]!=0)
	         incoming[j]++;
	    } 
	      
	printf("��%d�����\n",graph.vertexNum);
	for(int i=0;i<graph.vertexNum;i++)
	{	
	   for(int j=0;j<graph.vertexNum;j++)
	      printf("%d ",graph.matrix[i][j]);    
	   printf("\n");   
    }
    printf("\n");
    
    
    while(index<graph.vertexNum)
    {
    	int candidate=-1;
		for(int i=0;i<graph.vertexNum;i++)
		{
			if(sorted[i]==0&&incoming[i]==0)
			 {
			 	candidate=i; 
			 	break;
			 }  
		}
		if(candidate==-1)//���û�ҵ������ŵĵ� 
		{
			printf("��ͼ�л�·!\n");
			return 0;
		}
		else
		{
			topology[index++]=candidate;
			sorted[candidate]=1; 
			for(int i=0;i<graph.vertexNum;i++)
			{
				if(graph.matrix[candidate][i]==1)
				   incoming[i]--;
			}
		
		}
		
	}
	
	
	printf("��������Ϊ:");
	for(int i=0;i<graph.vertexNum;i++)
	  printf("%d ",topology[i]);
	printf("\n");
}


