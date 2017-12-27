//Memory Time
//184K  422MS

#include<iostream>
#include<string.h>
#include<fstream>
using namespace std;

int map[10][10]; //九宫格

bool row[10][10];    //row[i][x]  标记在第i行中数字x是否出现了
bool col[10][10];    //col[j][y]  标记在第j列中数字y是否出现了
bool grid[10][10];   //grid[k][x] 标记在第k个3*3子格中数字z是否出现了

//(这里说明的字母不代表下面程序中的变量)

void DFS(int x,int y)
{
	if(x==10)
	{
		for(int i=1; i<=9; i++)
		{
			for(int j=1; j<=9; j++)
				cout<<map[i][j];
			cout<<endl;
		}
		cout<<endl;
	
	}

	if(map[x][y])  //如果不需要填充
	{
		if(y==9)
			DFS(x+1,1);
		else
			DFS(x,y+1);


	}
	else  //说明这个格子是需要我填的
	{

		int k=3*((x-1)/3)+(y-1)/3+1;

		for(int i=1; i<=9; i++) //枚举数字1~9填空
			if(!row[x][i] && !col[y][i] && !grid[k][i])
			{
				map[x][y]=i;

				row[x][i]=true;
				col[y][i]=true;
				grid[k][i]=true;

				if(y==9)//如果列数已经到了9，那么需要新开一行
					DFS(x+1,1);
				else
					DFS(x,y+1);

				//回溯，继续枚举  如果能找到解，一样要撤销，去试试下一个数字能不能形成解，如果找不到解，就要回溯,撤销填数的动作
				map[x][y]=0;

				row[x][i]=false;
				col[y][i]=false;
				grid[k][i]=false;

			}
	}

}

int main()
{
	ifstream fin("Sudoku2.txt");
	int test;
	fin>>test;
	while(test--)
	{
		/*Initial*/

		memset(row,false,sizeof(row));
		memset(col,false,sizeof(col));
		memset(grid,false,sizeof(grid));

		/*Input*/

		char MAP[10][10];
		for(int i=1; i<=9; i++)
			for(int j=1; j<=9; j++)
			{
				fin>>MAP[i][j]; //cin会忽略换行符，所以无需处理换行符
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

		DFS(1,1);

	}

	return 0;
}



