#include<stdio.h>
#include <string.h>
int input[4]= {2,2,3,3};
int total=4;
int count=0;
//不用按字典序 产生可重集数组的排列
//不中用了
//母序列是322 ，要插入的是3，会产生 3232
//母序列是232，要插入的是3，也会产生 3232
//这样就重复了，而且很难避免
 
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
		//把我要加入的数字插入每个空位中  注意不可以改permute必须建立新的字符串newpermute
		int i=0;
		while(i<=size)//i表示每个空位，同时目前排列的大小就是size
		{
			
			int current=input[size];//目前要插入的数
			printf("目前要插入%d  size=%d i=%d\n",current,size,i);
			printf("母序列为:");
			for(int m=0; m<size; m++)
				printf("%d ",permute[m]);
			printf("\n");
			int newpermute[total];
			memset(newpermute,0,sizeof(newpermute));
			if(permute[i]==current)//如果要插入的数和原来排列一样
			{
				while(i<size&&permute[i]==current)//向后找到第一个不是要插入的数，把要插入的数放在它的前面
				{
					i++;
					
				}
                printf("移动后 i=%d\n",i);
  			}
            
            //不论是要跳着找到目前插入的位置，还是没有跳，复制到新的排列的过程都是一样的 
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
		
				i++;//不论是要跳着找到目前插入的位置，还是没有跳，下一个要插入的位置肯定要向后加一个，这是我的错误点 
		}//newpermute在递归完成后才会失效
		printf("\n");
	}
}

int main()
{
	int myarray[1];
	myarray[0]=input[0];
	repeatPermutation(myarray,1,total);
	printf("一共有%d个排列\n",count);

}
