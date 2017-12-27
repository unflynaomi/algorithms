#include"stdio.h"
#include <windows.h>
int A[8]={49,38,65,97,76,13,27,49};
int k=3;
int LomutoPartition(int l,int r);
int QuickSelect(int l,int r);
//使用洛穆托划分选出数组中第k小的数 
int main()
{	
    printf("第%d小的数是:%d\n",k,QuickSelect(0,7));  
}


//利用划分，把数组的轴枢放到它应该在的位置上,它的左边都是比它小的数，右边的数则大于等于它 
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
	printf("轴心为%d\n",p);
	for(int i=l;i<=r;i++)
	  printf("%d ",A[i]);
	printf("\n");  
	return s;
}

//快速排序划分 
int QuickPartition(int l,int r)
{
	int p=A[l];
	int j=r;
	int i=l+1;
	while(i<j)
	{
		while(A[i]<p)//i负责找>=p的，包括等于p的 
		 i++;
		while(A[j]>p)//j负责找<=p的，包括等于p的 
		 j--;
		if(i<j)//只有当i<j的时候才会交换A[i]和A[j] 
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

//在[l,r]的范围里，左闭右闭，找第k小的数 
int QuickSelect(int l,int r)
{
	
//	int s=LomutoPartition(l,r);
	int s=QuickPartition(l,r);
	printf("s=%d\n",s);
	//Sleep(1000);//延时一秒
	if(s==k-1)//s就是第k小的数 
	  return A[s];
	else if(s>k-1)//第k小的数在s的左半边，因为返回的s就是原数组里的索引，而k-1也就是原数组的索引
	//经过一次洛穆托划分后，位置s上的数已经在数组排完序后它应该在的位置s上，直接拿s和k-1比较最方便，看它是不是第k小的数，无需去改k 
	  return QuickSelect(l,s-1);
	else //第k小的数在s的右半边 
	  return QuickSelect(s+1,r);  
     	      
} 
