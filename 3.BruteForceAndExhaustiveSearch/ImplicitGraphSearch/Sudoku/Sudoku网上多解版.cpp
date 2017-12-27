//Memory Time
//184K  422MS

#include<iostream>
#include<string.h>
#include<fstream>
using namespace std;

int map[10][10]; //�Ź���

bool row[10][10];    //row[i][x]  ����ڵ�i��������x�Ƿ������
bool col[10][10];    //col[j][y]  ����ڵ�j��������y�Ƿ������
bool grid[10][10];   //grid[k][x] ����ڵ�k��3*3�Ӹ�������z�Ƿ������

//(����˵������ĸ��������������еı���)

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

	if(map[x][y])  //�������Ҫ���
	{
		if(y==9)
			DFS(x+1,1);
		else
			DFS(x,y+1);


	}
	else  //˵�������������Ҫ�����
	{

		int k=3*((x-1)/3)+(y-1)/3+1;

		for(int i=1; i<=9; i++) //ö������1~9���
			if(!row[x][i] && !col[y][i] && !grid[k][i])
			{
				map[x][y]=i;

				row[x][i]=true;
				col[y][i]=true;
				grid[k][i]=true;

				if(y==9)//��������Ѿ�����9����ô��Ҫ�¿�һ��
					DFS(x+1,1);
				else
					DFS(x,y+1);

				//���ݣ�����ö��  ������ҵ��⣬һ��Ҫ������ȥ������һ�������ܲ����γɽ⣬����Ҳ����⣬��Ҫ����,���������Ķ���
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
				fin>>MAP[i][j]; //cin����Ի��з����������账���з�
				map[i][j]=MAP[i][j]-'0';

				if(map[i][j]) //������Ѿ����õ�����
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



