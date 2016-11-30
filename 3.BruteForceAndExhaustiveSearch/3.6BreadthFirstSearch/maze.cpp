//走迷宫 算法竞赛入门经典 P108
//maze.txt 输入第一行  6 5 其中，6是行号 5是列号 
//寻找从左上角到右上角的最短路径 
//使用宽度遍历，能由近及远地搜到终点 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 50
#define print //printf
int main()
{
	int graph[MAX][MAX];//记录了迷宫的连通或者堵塞的情况 
	memset(graph,0,sizeof(graph));

    int n;//n是行号
	int m;//m是列号
	
	 	FILE *fp;
	if((fp=fopen("maze.txt","r"))==NULL)
	{
		printf("Cannot open file !");
		exit(1);
	}
	fscanf(fp,"%d %d",&n,&m);
	
    int visited[MAX];//从0,1,2，3,4,5,6开始的格子有没有被访问过 
	memset(visited,0,sizeof(visited)); 
	
	for(int i=0;i<n;i++)
	   for(int j=0;j<m;j++)
	     fscanf(fp,"%d",&graph[i+1][j+1]); 
     
	printf("输入的迷宫为：\n");
	for(int i=0;i<n+2;i++)
	{
		 for(int j=0;j<m+2;j++)
	        printf("%d ",graph[i][j]); 
	     printf("\n"); 
	}	
	
	int queue[MAX];//放迷宫格子标号，从0开始 0，1,2,3,4,5,6，... 
	int father[MAX];//记录下BFS的父结点在队列里的索引号 
	for(int i=0;i<MAX;i++)
	     father[i]=-2;
	     
	int front=0;
	int rear=0;
	queue[front]=0;//把左上角的格子入队
	visited[0]=1;
	father[front]=-1;
	rear++;
	
	while(true)//如果还没遇到目的地 
	{
		int current=queue[front];		
		print("current:%d\n",current);
		
		//current在图上对应的格子就是 graph[current/m+1][current%m+1]
		if((current-m)>=0&&visited[current-m]==0&&graph[current/m][current%m+1]==1)//可以向上走 之所以要  (current-m)>=0 因为current太小时，current-m有可能是负数 那么visited就没有负数的索引了 
		{
			print("上：%d入队\n",current-m);
			queue[rear]=current-m; 
			visited[current-m]=1;
			father[rear++]=front;//father[rear++]=current 不要记父结点的编号，而要记父结点的位置，否则无法找下一个父结点，父结点的编号在队里存着呢 
			if((current-m)==(m-1))//如果是目标点，退出 
			    break;
		} 
		
		if(visited[current+1]==0&&graph[current/m+1][current%m+2]==1)//可以向右走 
		{
			print("右：%d入队\n",current+1);
			queue[rear]=current+1; 
			visited[current+1]=1;
			father[rear++]=front;
			if((current+1)==(m-1))//如果是目标点，退出 
			    break;
		} 
		
		if(visited[current+m]==0&&graph[current/m+2][current%m+1]==1)//可以向下走 
		{
			print("下：%d入队\n",current+m);
			queue[rear]=current+m; 
			visited[current+m]=1;
			father[rear++]=front;
		} 
		
		if((current-m)>=0&&visited[current-1]==0&&graph[current/m+1][current%m]==1)//可以向左走 
		{
			print("左：%d入队\n",current-1);
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
	    
	 int stack[MAX];//用于输出结果的栈  就是走步的顺序 
	 int top=-1;//top指向实际上的栈顶元素 
	  
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
	 	    printf("上->");
	 	else if(stack[top-1]==stack[top]+1)
		    printf("右->"); 
	    else if(stack[top-1]==stack[top]+m)
		    printf("下->"); 
	    else
		    printf("左->");	
	    top--;				   
	 }
	  
}
 
