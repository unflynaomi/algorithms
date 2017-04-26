#include<stdio.h>
//传教士与野人过河问题，把人从左岸都运到右岸
int visited[4][4][2];//左岸的传教士有0,1,2,3 野人也是0,1,2,3 状态S=0 船在左岸，S=1船在右岸 天生就初始化好了,全是0
struct State
{
	int M;//左岸传教士人数
	int C;//左岸野人人数
	int S;//S=0 船在左岸，S=1船在右岸
	//int preIndex;//父结点在stack中的索引 这么写就是你概念含混不清了，bfs或许需要记录下来这一串解，但是
	//dfs并不需要，在dfs的栈中时刻保持着的就是解 

};


State firstUnvisitedValidState(State current);
State stack[1000];

void printPath(int top)
{
	
	if(top==0)
	   printf("(%d %d %d)\n",stack[top].M,stack[top].C,stack[top].S);
	else
	{
		printPath(top-1);//先把它之前的结点都打出来 
     	printf("(%d %d %d)\n",stack[top].M,stack[top].C,stack[top].S);//再打印我自己 
	}

}

int main()
{


	
	int top=-1;
	top++;//top指向栈顶元素
	stack[top].M=3;
	stack[top].C=3;
	stack[top].S=0;
	visited[3][3][0]=1;

	//开始dfs
	while(top>-1)
	{
		
		if(stack[top].M==0&&stack[top].C==0)
		{
			printPath(top);			
			printf("found!\n");
		   	break;
		}
		else
		{
			
			State newState=firstUnvisitedValidState(stack[top]);
			if(newState.S==-1)
			{
				
				top--;//弹栈
				
			}

			else
			{
				stack[++top]=newState;
				visited[stack[top].M][stack[top].C][stack[top].S]=1;
				//printf("新状态为:(%d %d %d)\n",stack[top].M,stack[top].C,stack[top].S);

			}


		}
	}


}

State firstUnvisitedValidState(State current)
{
	int tryM=0;//先尝试着进行状态转移，再判断合法性 ，如果可以就转移，不行就放弃 
	int tryC=0;
	State result;
	for(int i=0; i<=2; i++)//i传教士的运输数 
		for(int j=0; j<=2; j++)//j野人的运输数 
		{
			if(i+j>0&&i+j<=2)
			{

				if(current.S==0)//左岸往右岸运人
				{
					//printf("尝试运%d个传教士和%d个野人过去\n",i,j);
					tryM=current.M-i;
					tryC=current.C-j;
					if(tryM==0&&tryC>=0&&!visited[tryM][tryC][1])//如果左岸没有传教士，允那么两岸都无需判断 传教士是否比野人多 
					{
						result.M=tryM;
						result.C=tryC;
						result.S=1;
						return result;
					}
					if(3-tryM==0&&tryC>=0&&!visited[tryM][tryC][1])//没往右岸运传教士，如果右岸没有传教士，那么两岸都无需判断 传教士是否比野人多 
					{
						result.M=tryM;
						result.C=tryC;
						result.S=1;
						return result;
					}
					if(tryM>0&&tryC>=0&&tryM>=tryC&&3-tryM>=3-tryC&&!visited[tryM][tryC][1])
					{
						result.M=tryM;
						result.C=tryC;
						result.S=1;
						return result;

					}
				}
				else//右岸往左岸运人
				{
					//printf("尝试运%d个传教士和%d个野人过来\n",i,j);
					tryM=current.M+i;//tryM一定>=0
					tryC=current.C+j;//tryC一定>=0
					if(3-current.M>=i&&3-current.C>=j)//我希望 对方能支付起i个传教士与j个野人的运输  不然假设这岸有2个传教士，2个野人，你竟然要运过来2个传教士，0个野人，这不可能 
					{

						if(tryM==0&&!visited[tryM][tryC][0])//左岸本来没有传教士，也没有运过来传教士
						{
							result.M=tryM;
							result.C=tryC;
							result.S=0;
							return result;
						}
						if(3-tryM==0&&!visited[tryM][tryC][0])//传教士都运了过来，我不用担心人数的问题 
						{
							result.M=tryM;
							result.C=tryC;
							result.S=0;
							return result;

						}
						if(tryM>=tryC&&3-tryM>=3-tryC&&!visited[tryM][tryC][0])
						{
							result.M=tryM;
							result.C=tryC;
							result.S=0;
							return result;

						}
					}
				}

			}
		}
	result.M=-1;
	result.C=-1;
	result.S=-1;
	return result;

}
