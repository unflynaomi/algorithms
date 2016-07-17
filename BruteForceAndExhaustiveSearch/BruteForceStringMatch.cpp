/*brute force string match */
#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#define MAX 100
int main()
{
	FILE *fp;
	if((fp=fopen("StringMatch.txt","r"))==NULL)
	{
		printf("Cannot open file !");
		exit(1);
	}
	char text[MAX];
	int textLen=0;
	char pattern[MAX];
	int patternLen=0;
	
	fscanf(fp,"%s",text);
	textLen=strlen(text);
	fscanf(fp,"%s",pattern);
	patternLen=strlen(pattern);

	printf("text is£º%s  length£º%d\n",text,textLen);
	printf("pattern is£º%s length£º%d\n",pattern,patternLen);
	
	int count=0;
	for(int i=0;i<=textLen-patternLen;i++)
	 {	 	
	    count=0;
		 while(count<patternLen&&text[i+count]==pattern[count])
		   count++;
		if(count==patternLen)   
		   printf("match at %d\n",i+1);
	  } 

}
