//Memory Time
//184K  422MS

#include<iostream>
#include<string.h>
using namespace std;

int map[10][10]; //九宫格 从1开始 每行都是1-9 

bool row[10][10];    //row[i][x]  标记在第i行中数字x是否出现了
bool col[10][10];    //col[j][y]  标记在第j列中数字y是否出现了
bool grid[10][10];   //grid[k][x] 标记在第k个3*3子格中数字z是否出现了

//(这里说明的字母不代表下面程序中的变量)

bool DFS(int x,int y)
{
	if(x==10)
		return true;

	bool flag=false;

	if(map[x][y])  //如果不需要填充
	{
		if(y==9)
			flag=DFS(x+1,1);
		else
			flag=DFS(x,y+1);

		if(flag) //如果(1,1) 是不需要填充的，那么flag=DFS(1,2) 如果能成功，那么就直接返回给主函数一个true
			return true;
		else
			return false;
	}
	else  //说明这个格子是需要我填的
	{

		int k=3*((x-1)/3)+(y-1)/3+1;//计算出我这个i,j在哪个九宫格中 

		for(int i=1; i<=9; i++) //枚举数字1~9填空
			if(!row[x][i] && !col[y][i] && !grid[k][i])
			{
				map[x][y]=i;

				row[x][i]=true;
				col[y][i]=true;
				grid[k][i]=true;

				if(y==9)//如果列数已经到了9，那么需要新开一行
					flag=DFS(x+1,1);
				else
					flag=DFS(x,y+1);

				if(!flag)   //回溯，继续枚举  如果能找到解，就终止，如果找不到解，就要回溯,撤销填数的动作 
				{
					map[x][y]=0;

					row[x][i]=false;
					col[y][i]=false;
					grid[k][i]=false;
				}
				else
					return true;//会导致调用的栈，全部返回true,一直回到main函数 
			}
	}
	return false;
}

int main(int i,int j)
{
	int test;
	cin>>test;
	while(test--)
	{
		/*Initial*/

		memset(row,false,sizeof(row));
		memset(col,false,sizeof(col));
		memset(grid,false,sizeof(grid));

		/*Input*/

		char MAP[10][10];
		for(i=1; i<=9; i++)
			for(j=1; j<=9; j++)
			{
				cin>>MAP[i][j]; //cin会忽略换行符，所以无需处理换行符
				map[i][j]=MAP[i][j]-'0';

				if(map[i][j]) //如果是已经填充好的数字
				{
					int k=3*((i-1)/3)+(j-1)/3+1;
					row[i][ map[i][j] ]=true;
					col[j][ map[i][j] ]=true;
					grid[k][ map[i][j] ]=true;
				}
			}

		/*Fill the Sudoku*/

		if(DFS(1,1))//如果有解就输出 
		{
			for(i=1; i<=9; i++)
			{
				for(j=1; j<=9; j++)
					cout<<map[i][j];
				cout<<endl;
			}
		}


	}
	return 0;
}



