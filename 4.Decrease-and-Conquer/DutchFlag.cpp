#include<stdio.h>
//������������
//int A[9]= {3,1,2,1,1,3,2,2,3};
int A[9]= {1,1,2,3,1,3,2,2,3};
//int A[10]= {1,2,3,2,2,3,1,3,2,1};
//int n=10;
int n=9;
void swap(int* a,int* b);
void LomutoDutchFlag();
void QuickPartitionDutchFlag();
int main()
{

	QuickPartitionDutchFlag();
	for(int i=0; i<n; i++)
		printf("%d ",A[i]);
}

void LomutoDutchFlag()
{
	int i=-1;//ָ�������һ�� 1
	int j=-1;//ָ��׵����һ�� 2
	int k=-1;//ָ���������һ�� 3
	//���뱣��iС�ڵ���jС�ڵ���k,�����ڵ�ʱ��˵��ĳ��Ϊ��
	while(k+1<=n-1)
	{
		if(A[k+1]==3)//���Ŀǰ�жϵ�������ɫ�� 3
			k++;
		else if(A[k+1]==2) //���Ŀǰ�жϵ����ǰ�ɫ�� 2
		{
			//�������ɫ��Ļ���j+1���ǵ�һ��3 �ѵ�һ��3���·��ֵ�2����
			if(j!=k)
			{
				swap(&A[j+1],&A[k+1]);
				j++;
				k++;

			}
			//���û����ɫ�򣬵��Ƿ�����2��j��kֱ����1
			else
			{
				j++;
				k++;
			}

		}
		else //���Ŀǰ�жϵ����Ǻ�ɫ 1
		{
			if(i<j&&j<k)//������˹�ģ��ÿ�ζ���Ϊ��
			{
				swap(&A[i+1],&A[k+1]);//�ѵ�һ��2�����·��ֵ�1����
				swap(&A[j+1],&A[k+1]); //�ѵ�һ��3�͸ջ���ȥ��2����
				k++;
				i++;
				j++;
			}
			else if(i==j&&j==k) //���û��2Ҳû��3
			{
				k++;
				i++;
				j++;
			}
			else if(i==j&&j<k) //û��2������3
			{
				swap(&A[j+1],&A[k+1]);//��һ��3�� �·��ֵ�1����
				k++;
				i++;
				j++;
			}
			else if(i<j&&j==k)//û��3��������2
			{
				swap(&A[i+1],&A[k+1]);//��һ��2�� �·��ֵ�1����
				k++;
				i++;
				j++;
			}

		}

	}
}

void QuickPartitionDutchFlag()
{
	
	int begin=-1;//beginָ�����һ���� 0
	int end=n;//end ָ���һ���� 1
	int current=0;//ָ��ĿǰҪ�жϵ���
	while(current<end)
	{
       
		if(A[current]==2)//���Ŀǰ��Ҫ�жϵ���2
			current++;
		else if(A[current]==1)
		{
			swap(&A[current],&A[begin+1]);
			//�ѷ��ֵ�1��ǰ�ף� A[begin+1]������1����2�����ǲ�������3����Ϊbegin�϶�С��current,
			//begin+1С�ڵ���current,currentɨ���ĵط���3�϶��Ѿ��׵����ұ�
			current++;
			begin++;
		}
		else if(A[current]==3)
		{
			swap(&A[current],&A[end-1]);//�ѷ��ֵ�3������
			end--;//�����п��ܻ���������1���ǻ���Ҫ��һ����ǰ��
		}
		

	}

}

void swap(int* a,int* b)
{
	int tmp=*a;
	*a=*b;
	*b=tmp;
}
