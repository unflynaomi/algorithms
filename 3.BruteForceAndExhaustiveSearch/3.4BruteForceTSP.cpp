//������������������ 
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
	printf("��%d������:\n",cityNum);
	
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
	 printf("TSP���·��Ϊ��%s ->",city[0]);
	 for(int i=0;i<cityNum-1;i++)
	    printf("%s ->",city[solution[i]]);
	 printf("%s   ����Ϊ��%d\n",city[0],distance);   
	   
}
 

void print_permutation(int n,int* A,int cur)
{
	if(cur==n)
	{
		int sum=graph[0][A[0]]+graph[A[cur-1]][0];//���ϴ�A�����͵�A��·��		
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
		for(int i=1; i<=n; i++)//��A[cur]����������� 
		{
			flag=0;
			for(int j=0; j<cur; j++)
				if(i==A[j])
					flag=1;//˵��������Ѿ����ֹ���
			if(!flag)
			{
				A[cur]=i;
				print_permutation(n,A,cur+1);
			}

		}

	}
} 
