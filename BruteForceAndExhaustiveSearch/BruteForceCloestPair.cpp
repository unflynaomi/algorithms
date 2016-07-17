/*brute force solution to colest pair problem*/
#include<stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX 100
#define MAXDISTANCE 100000
struct Point
{
	int x;
	int y;
 } points[MAX];
 
 int main()
 {
 	FILE *fp;
	if((fp=fopen("CloestPair.txt","r"))==NULL)
	{
		printf("Cannot open file !");		
		exit(1);
	}
	int n=0;
	double minDistance=MAXDISTANCE;
	double distance;
	int cloestPairOne;
	int cloestPairTwo;	
 	while(!feof(fp))
 	{
 		 fscanf(fp,"%d,%d",&points[n].x,&points[n].y);
 		 n++;
	 }
	 for(int i=0;i<n;i++)
	   printf("No %d point:(%d,%d)\n",i+1,points[i].x,points[i].y);
 
	   
	 for(int i=0;i<n-1;i++)
	  for(int j=i+1;j<n;j++)
	  {
	  	 distance=(points[i].x-points[j].x)*(points[i].x-points[j].x)+(points[i].y-points[j].y)*(points[i].y-points[j].y);
	  	 if(distance<minDistance)
	  	 {
	  	 	minDistance=distance;
	  	 	cloestPairOne=i;
	  	 	cloestPairTwo=j;
	  	 	
		   }
	  	
	  }
	  minDistance=sqrt(minDistance);//there is no necessary to sqrt every time, as sqrt is strictly increasing  
	  printf("closest pair are (%d,%d) and (%d,%d),distance is %f\n",points[cloestPairOne].x,points[cloestPairOne].y,points[cloestPairTwo].x,points[cloestPairTwo].y,minDistance);  
	      
 	return 0;
 }
 
