//Memory Time
//184K  422MS

#include<iostream>
#include<string.h>
using namespace std;

int map[10][10]; //�Ź��� ��1��ʼ ÿ�ж���1-9 

bool row[10][10];    //row[i][x]  ����ڵ�i��������x�Ƿ������
bool col[10][10];    //col[j][y]  ����ڵ�j��������y�Ƿ������
bool grid[10][10];   //grid[k][x] ����ڵ�k��3*3�Ӹ�������z�Ƿ������

//(����˵������ĸ��������������еı���)

bool DFS(int x,int y)
{
	if(x==10)
		return true;

	bool flag=false;

	if(map[x][y])  //�������Ҫ���
	{
		if(y==9)
			flag=DFS(x+1,1);
		else
			flag=DFS(x,y+1);

		if(flag) //���(1,1) �ǲ���Ҫ���ģ���ôflag=DFS(1,2) ����ܳɹ�����ô��ֱ�ӷ��ظ�������һ��true
			return true;
		else
			return false;
	}
	else  //˵�������������Ҫ�����
	{

		int k=3*((x-1)/3)+(y-1)/3+1;//����������i,j���ĸ��Ź����� 

		for(int i=1; i<=9; i++) //ö������1~9���
			if(!row[x][i] && !col[y][i] && !grid[k][i])
			{
				map[x][y]=i;

				row[x][i]=true;
				col[y][i]=true;
				grid[k][i]=true;

				if(y==9)//��������Ѿ�����9����ô��Ҫ�¿�һ��
					flag=DFS(x+1,1);
				else
					flag=DFS(x,y+1);

				if(!flag)   //���ݣ�����ö��  ������ҵ��⣬����ֹ������Ҳ����⣬��Ҫ����,���������Ķ��� 
				{
					map[x][y]=0;

					row[x][i]=false;
					col[y][i]=false;
					grid[k][i]=false;
				}
				else
					return true;//�ᵼ�µ��õ�ջ��ȫ������true,һֱ�ص�main���� 
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
				cin>>MAP[i][j]; //cin����Ի��з����������账���з�
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

		if(DFS(1,1))//����н����� 
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



