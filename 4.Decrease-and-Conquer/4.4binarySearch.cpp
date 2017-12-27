#include<stdio.h>
int binarySearch(int left,int right,int* array,int key);
int binarySearchR(int left,int right,int* array,int key);
int main()
{
	int array[9]={7,9,12,12,13,13,16,17,18};
	printf("查找%d在位置%d\n",9,binarySearch(0,8,array,18));
	printf("查找%d在位置%d\n",9,binarySearchR(0,8,array,18));
	printf("查找%d在位置%d\n",7,binarySearchR(0,8,array,7));
	printf("查找%d在位置%d\n",14,binarySearchR(0,8,array,14));
}

//折半查找，能找到返回元素索引，找不到就返回-1，非递归版,搜索区间是[left,right]包含left和right 
int binarySearch(int left,int right,int* array,int key)
{
	int mid;
	while(left<=right)//注意一定是小于等于，不是小于，当等于的时候还要循环一次，例如查找第一个元素的时候，就会有left=right的情况 
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

//折半查找，能找到返回元素索引，找不到就返回-1，递归版,搜索区间是[left,right]包含left和right
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
