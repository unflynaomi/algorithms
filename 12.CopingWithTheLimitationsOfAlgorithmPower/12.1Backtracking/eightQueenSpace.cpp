//8�ʺ����⣬�򵥻��ݰ汾
#include<stdio.h>
#define N 8
int result[N];//���ÿ���ʺ�ŵ��к�
int col[N];//������б�ռ�˾���Ϊ1
int mainDiagonal[2*N-1];//���Խ������м���+N-1
int minorDiagonal[2*N-1];//�ζԽ������м���
int count;//ͳ�ƽ����Ŀ
void  dfs(int curQueen);//i�ǵ�ǰ��Ҫ�ŵĻʺ�
bool ifCanLay(int curQueen,int tryCol);
int main()
{
	dfs(0);
	printf("����%d����",count);

}

void  dfs(int curQueen)//i�ǵ�ǰ��Ҫ�ŵĻʺ�
{
	printf("curQueen= %d\n",curQueen);
	if(curQueen==N)//ȫ�������Ժ�������
	{
		count++;
		for(int i=0; i<N; i++)
			printf("%d ",result[i]);
		printf("\n");

	}
	else
	{

		for(int tryCol=0; tryCol<N; tryCol++) //���Է��õ���
		{
			printf("try:%d %d\n",curQueen,tryCol);
			if(ifCanLay(curQueen,tryCol))//����ܷţ��ͷţ���������һ���ʺ�
			{
				printf("can lay! %d %d\n",curQueen,tryCol);
				result[curQueen]=tryCol;
				col[tryCol]=1;
				mainDiagonal[curQueen-tryCol+N-1]=1;
				minorDiagonal[curQueen+tryCol]=1;
				//dfs(++curQueen);//����һ���ʺ�
				//��������ôд�ģ���4�ʺ�Ϊ�������ѵ�try[1][2]��ʱ�򣬷��ֿ��԰ڷŵ�,dfs(2),curQueen=2
				//���㷢�ֵ�2�Żʺ�������ô�ڶ�����ʱ��dfs(2)�ͽ����ˣ�tryCol=3,����Ӧ����[1][3]�ģ�������Ϊ��
				//û�л��ݣ�û�а����ڷŵĻʺ��-1���ѵ���[2][3],�ʹ���
				dfs(curQueen+1);//������curQueenû�б� 
                 
                //��һ�����ԵĻ��� 
				//��4�ʺ�Ϊ�������ѵ�try[1][2]��ʱ�򣬷����ǿ��԰ڷŵģ��ڷţ�dfs(2),���ֶ����У���ʱ��Ҫ���԰ڷ�try[1][3]
				//������ʱ�ڶ����Ѿ����㣨1,2����ռ���ˣ���������Ҫ��(1,2) �����ˣ���Ҫ��������Ӱ�죬�ͷŵڶ���
				//���dfs�ݹ�Ĺ��̣����ɹ�����ô����ȻҪ�����ⲽ���߷������dfs�Ĺ������ҵ��⣬����Ҳ���������ˣ������ⲽ���߷�
				//������һ��λ�ã������ǲ���һ���� 
				col[tryCol]=0;
				mainDiagonal[curQueen-tryCol+N-1]=0;
				minorDiagonal[curQueen+tryCol]=0;


			}
		}



	}
}

//��eightQueenSpace.cpp���棬�����跭����ǰ���лʺ�ģ�����Ҫ����Ŀռ䣬�ж�����ǰ�Ļʺ��ͻ����������ζԽ��ߵı�־λ 
bool ifCanLay(int curQueen,int tryCol)
{

	if(col[tryCol]||mainDiagonal[curQueen-tryCol+N-1]||minorDiagonal[curQueen+tryCol])//��һ��˵����ǰ��Ļʺ���һ���ζԽ�����
		//��һ��˵����ǰ��Ļʺ���һ�����Խ�����
		return false;

	return true;
}


