#include<stdio.h>
//�����ֵ������� ����1-n��ȫ���� 
int n;
void permutation(int* permute,int size)
{
	if(size==n)
	{
		for(int i=0; i<size; i++)
			printf("%d ",permute[i]);
		printf("\n");
	}
	else
	{

		for(int i=1; i<=n; i++ )
		{
			bool flag=false;//�����¼��������֮ǰ��û�г��ֹ�
			for(int j=0; j<size; j++)
			{
				if(permute[j]==i)
				{
					flag=true;
					break;
				}
			}
			if(!flag)
			{
				permute[size]=i;			
				permutation(permute,size+1);
			}

		}

	}
}

int main()
{
	n=5;
	int permute[n];
	permutation(permute,0);
}
