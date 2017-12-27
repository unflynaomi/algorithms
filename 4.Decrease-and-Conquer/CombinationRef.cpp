#include"iostream"
using namespace std;
/*                   组合数                           */

#define N 100
int a[N];
int count=0;

//求组合数C(m,k)个数并分别从大到小遍历,
/*思路就是减治法，当组合的第一个数字选定时，其后的数字是从余下的m-1个数中取k-1数的组合。这
就将求m个数中取k个数的组合问题转化成求m-1个数中取k-1个数的组合问题。
按照降序产生组合数，第一个数是最大的数，比如从5中选出3个来,那么组合中最大的数可以是5 4 3，不可能是2 因为你至少要选3个
那么第一个最大的数有了，比如第一个数是5就从剩下的4个数中选出2个来，如果第一个数是4，就从剩下的3个数中选出2个来，5开头的组合数怎么也不可能
和4开头的重，从剩下的4个数中选2个，也是一样的，先确定最大的数可能是 4 3 2，比如是4，从剩下的3个数理再选1个*/
int  comb(int m,int k)//(C(m,k))
{    
    int i,j;
    for (i=m;i>=k;i--)
    {
        a[k]=i;
        if (k>1)
        {
            comb(i-1,k-1);
        }
        else
        { 
            count++;
            for (j=a[0];j>0;j--)
            {
                cout<<a[j];
            }
            cout<<" ";
            
        }
    }
    
    return count;           
}
int main()
{
    int m,k;
    cout<<"输入n与k:"; 
    cin>>m>>k;
    a[0]=k;
    int num=comb(m,k);
    cout<<endl;
    cout<<"有"<<num<<"个解"<<endl;
    return 0;
}

