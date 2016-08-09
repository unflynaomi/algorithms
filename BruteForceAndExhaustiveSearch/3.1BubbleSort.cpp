/*bubble sort*/
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
	bool ifChanged=true;

	while(!feof(fp)) //if it is not end of file
	{
		fscanf(fp,"%d",&data[size]);
		size++;
	}
	printf("input data are£º");
	for(int i=0; i<size; i++)
		printf("%d ",data[i]);
	printf("\n");

	//bubbleSort slightly improved
	for(int j=size; j>1&&ifChanged; j--) //stop sorting if there is no exchange
	{
		ifChanged=false; //default is no exchange
		for(int i=0; i<j-1; i++)
			if(data[i]>data[i+1])
			{
				ifChanged=true;
				tmp=data[i];
				data[i]=data[i+1];
				data[i+1]=tmp;

			}
	}

	printf("after bubble sort£º");
	for(int i=0; i<size; i++)
		printf("%d ",data[i]);
	fclose(fp);
}
