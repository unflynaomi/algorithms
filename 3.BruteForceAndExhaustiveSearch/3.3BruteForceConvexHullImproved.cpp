/*brute force solution to convex hull problem  */
/*only limited to there is no point on the same line with any other point*/
/*use the new extreme point to find the next*/
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
	
	int count=0;
	int start=-1;
	int pre=-1;

	while(!feof(fp))
	{
		fscanf(fp,"%d,%d",&points[n].x,&points[n].y);
		n++;
	}

	int convexHull[n]= {-1};


	for(int i=0; i<n; i++)
		printf("No %d point:(%d,%d)\n",i+1,points[i].x,points[i].y);

	int one=0;
	int two=0;


	while(one<n&&one!=start)
	{	
		for(two=0; two<n; two++)//only calculate two=one;two<n is wrong, one's two can be smaller than one 
		{
			if(one!=two&&two!=pre)
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
						if(start==-1)
							start=one;
						printf("(%d,%d) is extreme point!\n",points[one].x,points[one].y);
						pre=one;
						one=two;//not all one will ++,some one depend on two but if there is no extreme point two then one will ++ 
						/*use the new extreme point to find the next*/
						break;
					}				
			}
		}//for(two=0; two<n; two++)
		if(two==n)
			one++;
	}


	return 0;
}

