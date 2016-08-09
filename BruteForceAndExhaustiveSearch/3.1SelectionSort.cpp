/*selection sort*/
#include <stdio.h>
#include <stdlib.h>
#define MAX 100
int main()
{
	FILE *fp;
	if((fp=fopen("sortdata.txt","r"))==NULL)
	{
		printf("Cannot open file !");
		exit(1);
	}
	int data[MAX];
	int size=0;
	int tmp;
	int minIndex;
	while(!feof(fp)) //if it is not end of file
	{
		fscanf(fp,"%d",&data[size]);
		size++;
	}
	printf("input data are£º");
	for(int i=0; i<size; i++)
		printf("%d ",data[i]);
	printf("\n");

	//selection sort begin
	for(int i=0; i<size-1; i++) //who deserves the i's place in the array
	{
		minIndex=i;
		for(int j=i+1; j<size; j++)
			if(data[j]<data[minIndex])
				minIndex=j;
		tmp=data[i];
		data[i]=data[minIndex];
		data[minIndex]=tmp;
	}
	printf("after selection sort£º");
	for(int i=0; i<size; i++)
		printf("%d ",data[i]);
	fclose(fp);
}
