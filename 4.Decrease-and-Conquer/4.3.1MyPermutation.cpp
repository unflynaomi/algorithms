#include<stdio.h>
#include <string.h>
//���ð��ֵ��� ����1-n��ȫ���� 
void permutation(int* permute,int size,int total)
{
	if(size==total)
	{
		for(int i=0; i<size; i++)
			printf("%d ",permute[i]);
		printf("\n");
	}
	else
	//����Ҫ��������ֲ���ÿ����λ��  ע�ⲻ���Ը�permute���뽨���µ��ַ���newpermute�������Ը�ģ�� 
		for(int i=0; i<=size; i++)//i��ʾÿ����λ�����Ҫ���������szie+1��ͬʱĿǰ���еĴ�С����size 
		{
			int newpermute[total];
			memset(newpermute,0,sizeof(newpermute));
			int j=0;
			for(int k=0; k<i; k++)
			{
				newpermute[j++]=permute[k];
			}
			newpermute[j++]=size+1;
			for(int k=i; k<size; k++)
				newpermute[j++]=permute[k];
//			for(int m=0; m<size+1; m++)
//				printf("%d ",newpermute[m]);
//			printf("\n");
			permutation(newpermute,size+1,total);
		}//newpermute�ڵݹ���ɺ�Ż�ʧЧ 
}

int main()
{
	int myarray[1]= {1};
	permutation(myarray,1,5);

}
