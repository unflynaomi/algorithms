#include<stdio.h>
#include <string.h>
int input[4]= {2,2,3,3};
int total=4;
int count=0;
//���ð��ֵ��� �������ؼ����������
//��������
//ĸ������322 ��Ҫ�������3������� 3232
//ĸ������232��Ҫ�������3��Ҳ����� 3232
//�������ظ��ˣ����Һ��ѱ���
 
void repeatPermutation(int* permute,int size,int total)
{
	if(size==total)
	{
		for(int i=0; i<size; i++)
			printf("%d ",permute[i]);
		printf("\n");
		count++;
	}
	else
	{
		//����Ҫ��������ֲ���ÿ����λ��  ע�ⲻ���Ը�permute���뽨���µ��ַ���newpermute
		int i=0;
		while(i<=size)//i��ʾÿ����λ��ͬʱĿǰ���еĴ�С����size
		{
			
			int current=input[size];//ĿǰҪ�������
			printf("ĿǰҪ����%d  size=%d i=%d\n",current,size,i);
			printf("ĸ����Ϊ:");
			for(int m=0; m<size; m++)
				printf("%d ",permute[m]);
			printf("\n");
			int newpermute[total];
			memset(newpermute,0,sizeof(newpermute));
			if(permute[i]==current)//���Ҫ���������ԭ������һ��
			{
				while(i<size&&permute[i]==current)//����ҵ���һ������Ҫ�����������Ҫ���������������ǰ��
				{
					i++;
					
				}
                printf("�ƶ��� i=%d\n",i);
  			}
            
            //������Ҫ�����ҵ�Ŀǰ�����λ�ã�����û���������Ƶ��µ����еĹ��̶���һ���� 
			int j=0;
			for(int k=0; k<i; k++)
			{
				newpermute[j++]=permute[k];
			}
			newpermute[j++]=current;
			for(int k=i; k<size; k++)
				newpermute[j++]=permute[k];
			printf("newpermute:");
			for(int m=0; m<size+1; m++)
				printf("%d ",newpermute[m]);
			printf("\n");

			repeatPermutation(newpermute,size+1,total);
		
				i++;//������Ҫ�����ҵ�Ŀǰ�����λ�ã�����û��������һ��Ҫ�����λ�ÿ϶�Ҫ����һ���������ҵĴ���� 
		}//newpermute�ڵݹ���ɺ�Ż�ʧЧ
		printf("\n");
	}
}

int main()
{
	int myarray[1];
	myarray[0]=input[0];
	repeatPermutation(myarray,1,total);
	printf("һ����%d������\n",count);

}
