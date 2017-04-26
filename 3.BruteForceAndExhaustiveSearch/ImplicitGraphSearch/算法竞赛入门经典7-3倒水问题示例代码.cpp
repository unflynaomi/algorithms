#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define MAXN 105
int cap[3], x;//cap表示每个杯子的容量 x表示想要量出来的水量 
int vis[MAXN][MAXN];//是否访问过的标记，因为水量的总数是恒定的，所以只要知道后两位，前面一位一定也能知道,所以只要是二维数组就好了,无需是三维的 

struct Node
{
	int v[3];//0 1 2分别表示每个杯子里的水量 
	int fa, dist, last_op;
	//fa记录了在队列中的前驱的索引 
	//dist记录了从起点到当前结点需要几步 
	//last_op 是用一个两位数表示的,比如ij，表示把水从i倒入j  
};

Node q[MAXN*MAXN];//队列 用于bfs 

//用这种递归的方式打印路径很巧妙，都不需要栈了 
void print_path(int idx)
{
	if(q[idx].fa != idx)
		print_path(q[idx].fa);
	printf("%d %d %d\n", q[idx].v[0], q[idx].v[1], q[idx].v[2]);
}

void bfs()
{
	int front=0, rear=1, i, j, k;
	q[0].v[0] = cap[0];
	q[0].v[1] = q[0].v[2] = q[0].dist = q[0].fa = 0;
	vis[0][0] = 1;

	while(front<rear)//当队不为空时 
	{
		Node& u = q[front];
		if(u.v[0] == x || u.v[1] == x || u.v[2] == x)
		{
			printf("%d\n", u.dist);
			print_path(front);
			return;
		}
		
		//这里写的就比我的高明多了，把水从i倒入j中，i和j一共有6种组合，不用一个个地写if和else规则 
		for(i = 0; i < 3; i++)
			for(j = 0; j < 3; j++) if(i!=j)
				{
					Node& v = q[rear];
					int amount = min(u.v[i], (cap[j]-u.v[j]));
					//倒水有两种情况，如果i中的水比较少，就全部倒入j中， i all to j
					//如果j中的空间比较少，i就只能倒一部分在j中，把j倒满，i fill j 
					for(k = 0; k < 3; k++) v.v[k] = u.v[k];//复制以前的状态 
					v.v[i] -= amount;
					v.v[j] += amount;
					//如果i是空的，也就是amount=0也没有关系，这样会让当前的状态与以前的状态一样，已经被访问过的结点是不会入队的
					//i和j会换人 
					if(!vis[v.v[1]][v.v[2]])
					{
						vis[v.v[1]][v.v[2]] = 1;
						v.fa = front;
						v.dist = q[front].dist+1;
						v.last_op = i*10+j;
						rear++;
					}
				}
		front++;
	}
}

int main()
{
	int i, j;
	scanf("%d%d%d%d", &cap[0], &cap[1], &cap[2], &x);
	memset(vis, 0, sizeof(vis));
	bfs();
	return 0;
}
