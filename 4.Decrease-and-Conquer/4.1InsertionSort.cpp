#include<stdio.h>
int main()
{
	int array[7]={89,45,68,90,29,34,17};
	int arraySize=7;
	int tmp;
	//插入排序 
	for(int sorting=1;sorting<arraySize;sorting++)//sorting就是我现在正要排的那个数 
	{
		tmp=array[sorting];
		int i=0;
		//找到要插入的位置 并把数往后挪 
		for(i=sorting-1;i>=0&&array[i]>tmp;i--)
		    array[i+1]=array[i];		
		//插入    
		array[i+1]=tmp;   
	    		    
	}
	for(int i=0;i<arraySize;i++)
	   printf("%d ",array[i]);
	   
}
