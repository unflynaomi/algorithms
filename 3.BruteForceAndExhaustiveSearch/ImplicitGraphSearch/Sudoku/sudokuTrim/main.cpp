#include "stdio.h"  
#include "string.h"  
//实现POJ 3074 数独问题
struct node  
{  
    int x,y;  
    int candidate[10]; // 对于每个空格，数字i是否可用  
    int candidateNum; // 对于每个空格，一共可以填入的数字种数  
}order[101];  //需要填的空格 
  
int cnt; // 总空格数  
char str[101];  
int row[20][20],col[20][20],block[20][20]; //记录第i（行，列，小矩阵)的数字j是否已被占用  
int table[101][101]; // 大矩阵  
void init()  
{  
    int i,x,y;  
    memset(row,0,sizeof(row));  
    memset(col,0,sizeof(col));  
    memset(block,0,sizeof(block));  
  
    cnt=0;  
    for (i=0;i<81;i++)  
    {  
        x=i/9;  
        y=i%9;  
        if (str[i]=='.')  
        {  
            table[x][y]=0;  
            order[cnt].x=x;  
            order[cnt].y=y;  
            cnt++;  
        }  
        else  
        {  
            table[x][y]=str[i]-'0';  
            row[x][str[i]-'0']=1;  
            col[y][str[i]-'0']=1;  
            block[x/3*3+y/3][str[i]-'0']=1;  
        }  
    }  
}  
  
void updata()  
{  
    int x,y,i,j,k;  
    int oprow[10][10],opcol[10][10],opblock[10][10];  // 记录每行，列，小矩阵中数字k一共有几个可以放置的地方  
   //oprow里会存着可以放1的位置是0个，因为1已经被填充过了，是不需要填充的，在数独提示中出现了的
    memset(oprow,0,sizeof(oprow));  
    memset(opcol,0,sizeof(opcol));  
    memset(opblock,0,sizeof(opblock));  
  
    for (i=0;i<cnt;i++)  
    {  
        x=order[i].x;  
        y=order[i].y;  
        if (table[x][y]==0) //不是没有必要的，有的空格已经填过了 
        {  
            order[i].candidateNum=0;  
            memset(order[i].candidate,0,sizeof(order[i].candidate));  
            for (k=1;k<=9;k++)  
                if (row[x][k]==0 && col[y][k]==0 && block[x/3*3+y/3][k]==0) //如果这个数字是可以填的 
                {  
                    order[i].candidateNum++;  
                    order[i].candidate[k]=1;  
                    oprow[x][k]++;  //如果这个地方数字k是可以填的，那也就是说可以放数字k的地方多了一个 
                    opcol[y][k]++;  
                    opblock[x/3*3+y/3][k]++;  
                }  
        }  
    }  
  

	   
    for(i=0;i<9;i++)  
        for (k=1;k<=9;k++)  
        {  
            if (oprow[i][k]==1) // 如果第i行能放置数字k的位置只有一个  
            {  
                //你得找到是哪个位置能放我
                for (j=0;j<cnt;j++)  
                    if (order[j].x==i && table[order[j].x][order[j].y]==0 && order[j].candidate[k]==1)  
                    {  
                        order[j].candidateNum=1;  //我只有填k这一种选择 
                        memset(order[j].candidate,0,sizeof(order[j].candidate));  
                        order[j].candidate[k]=1;  
                        break;  
                    }  
            }  
  
            if (opcol[i][k]==1)  
            {  
                for (j=0;j<cnt;j++)  
                    if (order[j].y==i && table[order[j].x][order[j].y]==0 && order[j].candidate[k]==1)  
                    {  
                        order[j].candidateNum=1;  
                        memset(order[j].candidate,0,sizeof(order[j].candidate));  
                        order[j].candidate[k]=1;  
                        break;  
                    }  
            }  
  
            if (opblock[i][k]==1)  
            {  
                for (j=0;j<cnt;j++)  
                    if (order[j].x/3*3+order[j].y/3==i && table[order[j].x][order[j].y]==0 && order[j].candidate[k]==1)  
                    {  
                        order[j].candidateNum=1;  
                        memset(order[j].candidate,0,sizeof(order[j].candidate));  
                        order[j].candidate[k]=1;  
                        break;  
                    }  
            }  
  
        }  
}  
 
//翻一遍所有需要填的空格，选一个可能最少的空格去填，返回空格的序号,比起只有一种可能的空格是优先选择的，
//更优先的是一种可能都没有的空格，这样可以使递归提前结束
int getnow()  
{  
    int temp,mark,i,x,y;  
    temp=10;  
    mark=-1;  
    for (i=0;i<cnt;i++)  
    {  
        x=order[i].x;  
        y=order[i].y;  
        if (table[x][y]==0 && order[i].candidateNum<temp)  
        {  
            temp=order[i].candidateNum;  
            mark=i;  
        }  
    }  
   // printf("现在搜<%d,%d>有%d个候选解\n",order[mark].x,order[mark].y,order[mark].candidateNum);
    return mark;  
}  

int  dfs(int w)  
{  
    int now,x,y,k;  
    if (w==cnt) return 1;  
    now=getnow();  
    if (now==-1)
    {
        printf("now==-1\n");
        return 0;}  
  
    x=order[now].x;  
    y=order[now].y;  
    for (k=1;k<=9;k++)  
        if (order[now].candidate[k])  //如果k这个数字是可以填 
        {  
            row[x][k]=1;  
            col[y][k]=1;  
            block[x/3*3+y/3][k]=1;  
            table[x][y]=k;  
  
            updata();  
            if (dfs(w+1)==1) return 1;  
  
            row[x][k]=0;  
            col[y][k]=0;  
            block[x/3*3+y/3][k]=0;  
            table[x][y]=0;  
  
            updata();  
        }  
  
    return 0;  //一个好使的解都没有找到，直接返回0 
}  
int main()  
{  
    int i,j;  
    while (scanf("%s",str)!=EOF)  
    {  
        if (strcmp(str,"end")==0) break;  
  
        init();  
        updata();  
        dfs(0);  
  
        for (i=0;i<9;i++)  
            for (j=0;j<9;j++)  
            printf("%d",table[i][j]);  
        printf("\n");  
    }  
    return 0;  
}  
