//8�ʺ����⣬�򵥻��ݰ汾 
#include<stdio.h>
#define N 4
int result[N];//���ÿ���ʺ�ŵ��к� 
int count;//ͳ�ƽ����Ŀ 
void  dfs(int curQueen);
bool ifCanLay(int curQueen,int tryCol);
int main()
{
	dfs(0);	
	printf("����%d����",count);
	
} 

void  dfs(int curQueen)//i�ǵ�ǰ��Ҫ�ŵĻʺ� 
{
	
	if(curQueen==N)//ȫ�������Ժ������� 
	{
		count++;
		for(int i=0;i<N;i++)
		  printf("%d ",result[i]);
	    printf("\n");	  
	}
	else
	{
		for(int tryCol=0;tryCol<N;tryCol++)//���Է��õ���
		{
			
			if(ifCanLay(curQueen,tryCol))//����ܷţ��ͷţ���������һ���ʺ� 
			{
				
				result[curQueen]=tryCol;
				//dfs(++curQueen);//����һ���ʺ�  
				//��������ôд�ģ���4�ʺ�Ϊ�������ѵ�try[1][2]��ʱ�򣬷��ֿ��԰ڷŵ�,dfs(2),curQueen=2 
				//���㷢�ֵ�2�Żʺ�������ô�ڶ�����ʱ��dfs(2)�ͽ����ˣ�tryCol=3,����Ӧ����[1][3]�ģ�������Ϊ��
				//û�л��ݣ�û�а����ڷŵĻʺ��-1���ѵ���[2][3],�ʹ���
				dfs(curQueen+1);//������curQueenû�б� 
				
			}
		} 
		
	}
}

//�������������ǰ�Ļʺ�岻��ͻ����Ҫ������ǰ���еĻʺ���eightQueenSpace.cpp���棬�����跭����ǰ���лʺ�ģ�����Ҫ����Ŀռ� 
bool ifCanLay(int curQueen,int tryCol)
{
	for(int k=0;k<curQueen;k++)//������ǰ�ŵ����е�queen�岻��ͻ 
	{
		if(tryCol==result[k]||(curQueen+tryCol)==(k+result[k])||(curQueen-tryCol)==(k-result[k]))//��һ��˵����ǰ��Ļʺ���һ���ζԽ�����
		//��һ��˵����ǰ��Ļʺ���һ�����Խ����� 
		      return false;
	}
	return true;
}


