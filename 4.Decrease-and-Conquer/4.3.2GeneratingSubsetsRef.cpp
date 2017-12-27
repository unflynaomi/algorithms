#include<stdio.h>

int num[4],n;

void A(int n,int *a,int ans)
{
    for(int i = 0; i < ans; i ++)//打印当前元素 
        printf("%d ",a[i]);
    printf("\n");
    int s = ans?a[ans-1]+1:0;//确定当前元素的最小可能值 
    for(int i = s; i < n; i ++)
    {
        a[ans] = i;
        A(n,a,ans+1);//递归构造子集 
    } 
    return;
}

int main()
{
    n = 3;
    A(n,num,0);
    return 0;
}
