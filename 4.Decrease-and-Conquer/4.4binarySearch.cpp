#include<stdio.h>
int binarySearch(int left,int right,int* array,int key);
int binarySearchR(int left,int right,int* array,int key);
int main()
{
	int array[9]={7,9,12,12,13,13,16,17,18};
	printf("����%d��λ��%d\n",9,binarySearch(0,8,array,18));
	printf("����%d��λ��%d\n",9,binarySearchR(0,8,array,18));
	printf("����%d��λ��%d\n",7,binarySearchR(0,8,array,7));
	printf("����%d��λ��%d\n",14,binarySearchR(0,8,array,14));
}

//�۰���ң����ҵ�����Ԫ���������Ҳ����ͷ���-1���ǵݹ��,����������[left,right]����left��right 
int binarySearch(int left,int right,int* array,int key)
{
	int mid;
	while(left<=right)//ע��һ����С�ڵ��ڣ�����С�ڣ������ڵ�ʱ��Ҫѭ��һ�Σ�������ҵ�һ��Ԫ�ص�ʱ�򣬾ͻ���left=right����� 
	{
		mid=(left+right)/2;
		if(key==array[mid])
		   return mid;
		else
		 if(key>array[mid])
		 {
		 	left=mid+1;
		 }   
		 else
		   right=mid-1;
	}
	return -1;
}

//�۰���ң����ҵ�����Ԫ���������Ҳ����ͷ���-1���ݹ��,����������[left,right]����left��right
 int binarySearchR(int left,int right,int* array,int key)
{
 	if(right<left)
 	  return -1;
 	int mid=(left+right)/2;  
 	if(array[mid]==key)
	 return mid;
	else if(key>array[mid])
	  return binarySearch(mid+1,right,array,key);
	else
	  return binarySearch(left,mid-1,array,key);     
}
