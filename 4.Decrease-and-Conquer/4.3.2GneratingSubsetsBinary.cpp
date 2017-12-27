#include<stdio.h>
int n = 3;
void print_subset(int n,int ans)
{
    for(int i = 0; i < n; i ++)//打印{0,1,2,3..n-1}的子集ans 
    {
	
    printf("ans=%d\n",ans);    
    printf("1<<%d=%d\n",i,1<<i);
    printf("ans&(1<<i) = %d\n",ans&(1<<i));
        if(ans&(1<<i))
            printf("%d ",i);
   }
    printf("\n");
    return;
}

int main()
{
    for(int i = 0; i < (1<<n); i ++)//枚举各子集对应的编码 
        print_subset(n,i);
    return 0;
}

