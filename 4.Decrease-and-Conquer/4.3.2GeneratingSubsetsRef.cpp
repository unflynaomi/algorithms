#include<stdio.h>

int num[4],n;

void A(int n,int *a,int ans)
{
    for(int i = 0; i < ans; i ++)//��ӡ��ǰԪ�� 
        printf("%d ",a[i]);
    printf("\n");
    int s = ans?a[ans-1]+1:0;//ȷ����ǰԪ�ص���С����ֵ 
    for(int i = s; i < n; i ++)
    {
        a[ans] = i;
        A(n,a,ans+1);//�ݹ鹹���Ӽ� 
    } 
    return;
}

int main()
{
    n = 3;
    A(n,num,0);
    return 0;
}
