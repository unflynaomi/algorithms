#include<stdio.h>
int main()
{
	int array[7]={89,45,68,90,29,34,17};
	int arraySize=7;
	int tmp;
	//�������� 
	for(int sorting=1;sorting<arraySize;sorting++)//sorting������������Ҫ�ŵ��Ǹ��� 
	{
		tmp=array[sorting];
		int i=0;
		//�ҵ�Ҫ�����λ�� ����������Ų 
		for(i=sorting-1;i>=0&&array[i]>tmp;i--)
		    array[i+1]=array[i];		
		//����    
		array[i+1]=tmp;   
	    		    
	}
	for(int i=0;i<arraySize;i++)
	   printf("%d ",array[i]);
	   
}
