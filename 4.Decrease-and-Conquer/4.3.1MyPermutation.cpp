#include<stdio.h>
#include <string.h>
//不用按字典序 产生1-n的全排列 
void permutation(int* permute,int size,int total)
{
	if(size==total)
	{
		for(int i=0; i<size; i++)
			printf("%d ",permute[i]);
		printf("\n");
	}
	else
	//把我要加入的数字插入每个空位中  注意不可以改permute必须建立新的字符串newpermute，不可以改模板 
		for(int i=0; i<=size; i++)//i表示每个空位，这次要插入的数是szie+1，同时目前排列的大小就是size 
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
		}//newpermute在递归完成后才会失效 
}

int main()
{
	int myarray[1]= {1};
	permutation(myarray,1,5);

}
