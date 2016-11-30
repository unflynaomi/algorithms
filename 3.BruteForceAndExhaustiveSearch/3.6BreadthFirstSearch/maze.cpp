//���Թ� �㷨�������ž��� P108
//maze.txt �����һ��  6 5 ���У�6���к� 5���к� 
//Ѱ�Ҵ����Ͻǵ����Ͻǵ����·�� 
//ʹ�ÿ�ȱ��������ɽ���Զ���ѵ��յ� 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 50
#define print //printf
int main()
{
	int graph[MAX][MAX];//��¼���Թ�����ͨ���߶�������� 
	memset(graph,0,sizeof(graph));

    int n;//n���к�
	int m;//m���к�
	
	 	FILE *fp;
	if((fp=fopen("maze.txt","r"))==NULL)
	{
		printf("Cannot open file !");
		exit(1);
	}
	fscanf(fp,"%d %d",&n,&m);
	
    int visited[MAX];//��0,1,2��3,4,5,6��ʼ�ĸ�����û�б����ʹ� 
	memset(visited,0,sizeof(visited)); 
	
	for(int i=0;i<n;i++)
	   for(int j=0;j<m;j++)
	     fscanf(fp,"%d",&graph[i+1][j+1]); 
     
	printf("������Թ�Ϊ��\n");
	for(int i=0;i<n+2;i++)
	{
		 for(int j=0;j<m+2;j++)
	        printf("%d ",graph[i][j]); 
	     printf("\n"); 
	}	
	
	int queue[MAX];//���Թ����ӱ�ţ���0��ʼ 0��1,2,3,4,5,6��... 
	int father[MAX];//��¼��BFS�ĸ�����ڶ������������ 
	for(int i=0;i<MAX;i++)
	     father[i]=-2;
	     
	int front=0;
	int rear=0;
	queue[front]=0;//�����Ͻǵĸ������
	visited[0]=1;
	father[front]=-1;
	rear++;
	
	while(true)//�����û����Ŀ�ĵ� 
	{
		int current=queue[front];		
		print("current:%d\n",current);
		
		//current��ͼ�϶�Ӧ�ĸ��Ӿ��� graph[current/m+1][current%m+1]
		if((current-m)>=0&&visited[current-m]==0&&graph[current/m][current%m+1]==1)//���������� ֮����Ҫ  (current-m)>=0 ��Ϊcurrent̫Сʱ��current-m�п����Ǹ��� ��ôvisited��û�и����������� 
		{
			print("�ϣ�%d���\n",current-m);
			queue[rear]=current-m; 
			visited[current-m]=1;
			father[rear++]=front;//father[rear++]=current ��Ҫ�Ǹ����ı�ţ���Ҫ�Ǹ�����λ�ã������޷�����һ������㣬�����ı���ڶ�������� 
			if((current-m)==(m-1))//�����Ŀ��㣬�˳� 
			    break;
		} 
		
		if(visited[current+1]==0&&graph[current/m+1][current%m+2]==1)//���������� 
		{
			print("�ң�%d���\n",current+1);
			queue[rear]=current+1; 
			visited[current+1]=1;
			father[rear++]=front;
			if((current+1)==(m-1))//�����Ŀ��㣬�˳� 
			    break;
		} 
		
		if(visited[current+m]==0&&graph[current/m+2][current%m+1]==1)//���������� 
		{
			print("�£�%d���\n",current+m);
			queue[rear]=current+m; 
			visited[current+m]=1;
			father[rear++]=front;
		} 
		
		if((current-m)>=0&&visited[current-1]==0&&graph[current/m+1][current%m]==1)//���������� 
		{
			print("��%d���\n",current-1);
			queue[rear]=current-1; 
			visited[current-1]=1;
			father[rear++]=front;
		} 
		
		front++; 
	}
	
	 print("queue:\n"); 
	 for(int i=0;i<rear;i++)
	    print("%d ",queue[i]);
	 print("\n");   
	 print("father:\n"); 
	 for(int i=0;i<rear;i++)
	    print("%d ",father[i]);    
	 print("\n");     
	    
	 int stack[MAX];//������������ջ  �����߲���˳�� 
	 int top=-1;//topָ��ʵ���ϵ�ջ��Ԫ�� 
	  
	 int p=queue[rear-1];
	 
	 print("stack:\n");
	 stack[++top]=p;
	 print("%d\n",p);
	 int tmp=rear-1;
	 while(father[tmp]!=-1)
	 {
	 	 stack[++top]=queue[father[tmp]];
	 	 print("%d\n",queue[father[tmp]]);
	 	 tmp=father[tmp];		   
	 } 
	 
	 while(stack[top]!=m-1)
	 {
	 	if(stack[top-1]==stack[top]-m)
	 	    printf("��->");
	 	else if(stack[top-1]==stack[top]+1)
		    printf("��->"); 
	    else if(stack[top-1]==stack[top]+m)
		    printf("��->"); 
	    else
		    printf("��->");	
	    top--;				   
	 }
	  
}
 
