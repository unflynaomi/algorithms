/*using Newton's method to find a num's square root*/
#include<stdio.h> 

int main()
{
	double num=0.7;
	double precision=0.000001;
	double result=(double)num/2;   
	int tryTime=0;
	while(!(result*result<num+precision&&result*result>num-precision))//5-precision 5+precision 
	{
		result=(result+num/result)/2;
		tryTime++;		 
		printf("No %d try:%f\n",tryTime,result);
	}
}


