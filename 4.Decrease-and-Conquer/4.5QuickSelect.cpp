#include"stdio.h"
#include <windows.h>
int A[8]={49,38,65,97,76,13,27,49};
int k=3;
int LomutoPartition(int l,int r);
int QuickSelect(int l,int r);
//ʹ�������л���ѡ�������е�kС���� 
int main()
{	
    printf("��%dС������:%d\n",k,QuickSelect(0,7));  
}


//���û��֣������������ŵ���Ӧ���ڵ�λ����,������߶��Ǳ���С�������ұߵ�������ڵ����� 
int LomutoPartition(int l,int r)
{
	int i=l+1;
	int p=A[l];
	int s=l;
	while(i<=r)
	{
		if(A[i]>=p)
		 i++;
		else
		{
			s++;
			int tmp=A[i];
			A[i]=A[s];
			A[s]=tmp;
			i++;
			
		} 
	}
	A[l]=A[s];
	A[s]=p;
	printf("����Ϊ%d\n",p);
	for(int i=l;i<=r;i++)
	  printf("%d ",A[i]);
	printf("\n");  
	return s;
}

//�������򻮷� 
int QuickPartition(int l,int r)
{
	int p=A[l];
	int j=r;
	int i=l+1;
	while(i<j)
	{
		while(A[i]<p)//i������>=p�ģ���������p�� 
		 i++;
		while(A[j]>p)//j������<=p�ģ���������p�� 
		 j--;
		if(i<j)//ֻ�е�i<j��ʱ��Żύ��A[i]��A[j] 
		{
			int tmp=A[i];
			A[i]=A[j];
			A[j]=tmp;
		  	
		} 
		 
	}
	A[l]=A[j];
	A[j]=p;
    return j;
}

//��[l,r]�ķ�Χ�����ұգ��ҵ�kС���� 
int QuickSelect(int l,int r)
{
	
//	int s=LomutoPartition(l,r);
	int s=QuickPartition(l,r);
	printf("s=%d\n",s);
	//Sleep(1000);//��ʱһ��
	if(s==k-1)//s���ǵ�kС���� 
	  return A[s];
	else if(s>k-1)//��kС������s�����ߣ���Ϊ���ص�s����ԭ���������������k-1Ҳ����ԭ���������
	//����һ�������л��ֺ�λ��s�ϵ����Ѿ����������������Ӧ���ڵ�λ��s�ϣ�ֱ����s��k-1�Ƚ���㣬�����ǲ��ǵ�kС����������ȥ��k 
	  return QuickSelect(l,s-1);
	else //��kС������s���Ұ�� 
	  return QuickSelect(s+1,r);  
     	      
} 
