//���1-n������
#include<stdio.h>
void print_permutation(int n,int* A,int cur);
int main()
{
	int A[5];
    print_permutation(5,A,0);
}

void print_permutation(int n,int* A,int cur)
{
	if(cur==n)
	{
		for(int i=0; i<cur; i++) //output A
			printf("%d ",A[i]);
		printf("\n");
	}
	else
	{
		int flag=0;
		for(int i=1; i<=n; i++)//��A[cur]����������� 
		{
			flag=0;
			for(int j=0; j<cur; j++)
				if(i==A[j])
					flag=1;//˵��������Ѿ����ֹ���
			if(!flag)
			{
				A[cur]=i;
				print_permutation(n,A,cur+1);
			}

		}

	}
}
