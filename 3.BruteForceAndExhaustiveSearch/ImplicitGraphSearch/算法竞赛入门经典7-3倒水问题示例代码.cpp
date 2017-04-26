#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

#define MAXN 105
int cap[3], x;//cap��ʾÿ�����ӵ����� x��ʾ��Ҫ��������ˮ�� 
int vis[MAXN][MAXN];//�Ƿ���ʹ��ı�ǣ���Ϊˮ���������Ǻ㶨�ģ�����ֻҪ֪������λ��ǰ��һλһ��Ҳ��֪��,����ֻҪ�Ƕ�ά����ͺ���,��������ά�� 

struct Node
{
	int v[3];//0 1 2�ֱ��ʾÿ���������ˮ�� 
	int fa, dist, last_op;
	//fa��¼���ڶ����е�ǰ�������� 
	//dist��¼�˴���㵽��ǰ�����Ҫ���� 
	//last_op ����һ����λ����ʾ��,����ij����ʾ��ˮ��i����j  
};

Node q[MAXN*MAXN];//���� ����bfs 

//�����ֵݹ�ķ�ʽ��ӡ·�������������Ҫջ�� 
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

	while(front<rear)//���Ӳ�Ϊ��ʱ 
	{
		Node& u = q[front];
		if(u.v[0] == x || u.v[1] == x || u.v[2] == x)
		{
			printf("%d\n", u.dist);
			print_path(front);
			return;
		}
		
		//����д�ľͱ��ҵĸ������ˣ���ˮ��i����j�У�i��jһ����6����ϣ�����һ������дif��else���� 
		for(i = 0; i < 3; i++)
			for(j = 0; j < 3; j++) if(i!=j)
				{
					Node& v = q[rear];
					int amount = min(u.v[i], (cap[j]-u.v[j]));
					//��ˮ��������������i�е�ˮ�Ƚ��٣���ȫ������j�У� i all to j
					//���j�еĿռ�Ƚ��٣�i��ֻ�ܵ�һ������j�У���j������i fill j 
					for(k = 0; k < 3; k++) v.v[k] = u.v[k];//������ǰ��״̬ 
					v.v[i] -= amount;
					v.v[j] += amount;
					//���i�ǿյģ�Ҳ����amount=0Ҳû�й�ϵ���������õ�ǰ��״̬����ǰ��״̬һ�����Ѿ������ʹ��Ľ���ǲ�����ӵ�
					//i��j�ỻ�� 
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
