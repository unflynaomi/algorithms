//暴力法解旅行商问题 
#include<stdio.h>
#include <stdlib.h>
void print_permutation(int n,int* A,int cur);
int graph[100][100];
int distance=100;
int solution[100];
int main()
{
	FILE *fp;
	if((fp=fopen("3.4BruteForceTSP.txt","r"))==NULL)
	{
		printf("Cannot open file !");
		exit(1);
	}
	int cityNum=0;
	fscanf(fp,"%d",&cityNum);
	printf("有%d个城市:\n",cityNum);
	
	char city[cityNum][100];
	for(int i=0;i<cityNum;i++)
	 {
	 	fscanf(fp,"%s",&city[i]);
	 	printf("%s\n",city[i]);
	 } 
	  
	 
	 for(int i=0;i<cityNum;i++) 
	 {
	 	 for(int j=0;j<cityNum;j++)
	     {
	     	fscanf(fp,"%d",&graph[i][j]);
	     	printf("%d ",graph[i][j]);
	     }  
	     printf("\n");
	 }
	 int A[cityNum-1];
	 print_permutation(cityNum-1,A,0);
	 printf("TSP最短路径为：%s ->",city[0]);
	 for(int i=0;i<cityNum-1;i++)
	    printf("%s ->",city[solution[i]]);
	 printf("%s   距离为：%d\n",city[0],distance);   
	   
}
 

void print_permutation(int n,int* A,int cur)
{
	if(cur==n)
	{
		int sum=graph[0][A[0]]+graph[A[cur-1]][0];//算上从A出发和到A的路程		
		for(int i=0; i<cur-1; i++) //output A
		{
			sum+=graph[A[i]][A[i+1]]; 
		}
		if(sum<distance)
		{		    		
			distance=sum;
			for(int i=0;i<cur;i++)
			  solution[i]=A[i];
		}
	}
	else
	{
		int flag=0;
		for(int i=1; i<=n; i++)//在A[cur]中填各种整数 
		{
			flag=0;
			for(int j=0; j<cur; j++)
				if(i==A[j])
					flag=1;//说明这个数已经出现过了
			if(!flag)
			{
				A[cur]=i;
				print_permutation(n,A,cur+1);
			}

		}

	}
} 
