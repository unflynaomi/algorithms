//减治法拓扑排序 
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
	int incoming[graph.vertexNum];//统计入度的数组 
	memset(incoming,0,sizeof(incoming));
	int sorted[graph.vertexNum]; //是否已经排过序 
	memset(sorted,0,sizeof(sorted));
	int topology[graph.vertexNum];//拓扑排序
    int index=0; //拓扑排序的索引
	
	for(int i=0;i<graph.vertexNum;i++)
	   for(int j=0;j<graph.vertexNum;j++)
	   { 
	      fscanf(fp,"%d",&graph.matrix[i][j]);
	      if(graph.matrix[i][j]!=0)
	         incoming[j]++;
	    } 
	      
	printf("有%d个结点\n",graph.vertexNum);
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
		if(candidate==-1)//这次没找到可以排的点 
		{
			printf("此图有环路!\n");
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
	
	
	printf("拓扑排序为:");
	for(int i=0;i<graph.vertexNum;i++)
	  printf("%d ",topology[i]);
	printf("\n");
}


