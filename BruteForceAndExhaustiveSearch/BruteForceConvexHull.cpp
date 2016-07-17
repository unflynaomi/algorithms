/*brute force solution to convex hull problem  */
/*only limited to there is no point on the same line with any other point*/
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
	if((fp=fopen("ConvexHull.txt","r"))==NULL)
	{
		printf("Cannot open file !");
		exit(1);
	}
	int n=0;
	int a=0;
	int b=0;
	int c=0;
	int sign=0;
	int cmp;//compare with sign
	int point;
	int index;	
	
	while(!feof(fp))
	{
		fscanf(fp,"%d,%d",&points[n].x,&points[n].y);
		n++;
	}
	
   	int convexHull[n][2]; //every point in the set can be an extreme point ,this array stores the edges forming the convex hull,the first diemsion is an extreme point,the second diemsion is the corresponding point forming the edge with the first diemsion point
	//int convexHull[n][2]={-1};//not working at all only convexHull[0][0]=-1 others 0
		for(int i=0;i<n;i++)
	{
		convexHull[i][0]=-1;
		convexHull[i][1]=-1;		
	}
	
	
	for(int i=0; i<n; i++)
		printf("No %d point:(%d,%d)\n",i+1,points[i].x,points[i].y);

	for(int one=0; one<n; one++)
	{
		index=0;
		for(int two=0; two<n; two++)
		{
			if(one!=two)
			{
				a=points[two].y-points[one].y;
				b=points[one].x-points[two].x;
				c=points[one].x*points[two].y-points[one].y*points[two].x;
				sign=0;   //whether ax+by-c is postive or not
				for(point=0; point<n; point++)
					if(point!=one&&point!=two)
					{
						cmp=a*points[point].x+b*points[point].y-c; //cmp can be zero, if cmp is zero it's on the line,one and two are can be still extreme points
						if(sign==0)
							sign=cmp;//if the first cmp is zero ,it can not be used for sign,thus sign will be assgined again
						else if(sign*cmp<0)
							break;

					}
				if(point==n)//all points on the same side
				{
				//	printf("%d and %d are extreme points!\n",one,two);
					convexHull[one][index++]=two;
				}

			}
		}
	}
	
//	for(int i=0;i<n;i++)
//	{
//		printf("%d :",i);
//		printf("%d %d\n",convexHull[i][0],convexHull[i][1]);
//		
//	}
	
       int start=0;//the start point
	   int pre=-1;
	   int next=-1;
	   int count=1;
	   int tmp=-1;

	   while(convexHull[start][0]==-1)
	     start++;

	   pre=start;
	   next=convexHull[start][0];
	  

	   printf("convex hull extreme points clockwise:\n");
	   while(pre!=start||count==1)
	   {
	   	  printf("No %d:(%d,%d)\n",count++,points[pre].x,points[pre].y);
	   	  tmp=next;
	   	  if(convexHull[next][0]!=pre)
	   	    next=convexHull[next][0];
	   	  else
			next=convexHull[next][1];
		  pre=tmp;
	   }

	return 0;
}

