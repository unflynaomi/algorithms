//算法竞赛入门经典 7.5.2 7-3倒水问题
#include<stdio.h>
struct State
{
	int x;
	int y;
	int z;
	int preIndex;
};

int main()
{
	State queue[1000];//队列
	int front=0;
	int rear=0;
	queue[rear].x=6;
	queue[rear].y=0;
	queue[rear].z=0;
	queue[rear].preIndex=-1;

	rear++;
	//宽度搜索隐式图
	while(front!=rear)
	{
		if(queue[front].x==4)//只有x里可以量出4升水来
		{
			State stack[100];
			int top=0;
			int tmp=front;
			while(tmp!=-1)
			{
				stack[top].x=queue[tmp].x;
				stack[top].y=queue[tmp].y;
				stack[top].z=queue[tmp].z;
				top++;
				tmp=queue[tmp].preIndex;
			}
			top--;
			while(top>=0)
			{
				printf("(%d,%d,%d)\n",stack[top].x,stack[top].y,stack[top].z);
				top--;
			}
			break;
		}
		else
		{
			int x=queue[front].x;
			int y=queue[front].y;
			int z=queue[front].z;
			printf("扩展 (%d,%d,%d)\n",x,y,z);
			//新扩展的结点不能和祖先结点一样，可以少搜很多没有用的东西
			int ancx=queue[queue[front].preIndex].x;
			int ancy=queue[queue[front].preIndex].y;
			int ancz=queue[queue[front].preIndex].z;

			int tmpx=0;
			int tmpy=0;
			int tmpz=0;

			//规则开始
			//y倒入x
			//1.x倒满了x=6，y中还有剩余y=y-(6-x),y-(6-x)>0,这不可能
			//2.x没倒满，y中已经啥也不剩
			if(x<6&&y>0)
			{
				tmpx=x+y;
				tmpy=0;
				tmpz=z;

				if(!(tmpx==ancx&&tmpy==ancy&&tmpz==ancz))//新扩展的结点不能和祖先结点一样，可以少搜很多没有用的东西
				{

					queue[rear].x=tmpx;
					queue[rear].y=tmpy;
					queue[rear].z=tmpz;
					queue[rear].preIndex=front;
					printf("(%d,%d,%d)\n",queue[rear].x,queue[rear].y,queue[rear].z);
					rear++;
				}
			}
			//z倒入x
			//1.x倒满了x=6，z中还有剩余z=z-(6-x),z-(6-x)>0,这不可能
			//2.x没倒满，z中啥也不剩
			if(x<6&&z>0)
			{
				tmpx=x+1;
				tmpy=y;
				tmpz=0;
				if(!(tmpx==ancx&&tmpy==ancy&&tmpz==ancz))
				{

					queue[rear].x=tmpx;
					queue[rear].y=tmpy;
					queue[rear].z=tmpz;
					queue[rear].preIndex=front;
					printf("(%d,%d,%d)\n",queue[rear].x,queue[rear].y,queue[rear].z);
					rear++;
				}
			}
			//x倒入y
			//1.y没倒满，x中啥也不剩，那么y+x<3 这不可能
			//2. y倒满了，x中还有剩余
			if(y<3)
			{
				tmpx=x-(3-y);
				tmpy=3;
				tmpz=z;
				if(!(tmpx==ancx&&tmpy==ancy&&tmpz==ancz))
				{

					queue[rear].x=tmpx;
					queue[rear].y=tmpy;
					queue[rear].z=tmpz;
					queue[rear].preIndex=front;
					printf("(%d,%d,%d)\n",queue[rear].x,queue[rear].y,queue[rear].z);
					rear++;
				}
			}
			//z倒入y
			//1.y倒满了，z中还有剩余 如果z能倒入y 说明 z=1 y<3 现在y=3 z=1 这不可能
			//2.y没倒满，z中已经空了
			if(y<3&&z>0)
			{
				tmpx=x;
				tmpy=y+1;
				tmpz=0;
				if(!(tmpx==ancx&&tmpy==ancy&&tmpz==ancz))
				{

					queue[rear].x=tmpx;
					queue[rear].y=tmpy;
					queue[rear].z=tmpz;
					queue[rear].preIndex=front;
					printf("(%d,%d,%d)\n",queue[rear].x,queue[rear].y,queue[rear].z);
					rear++;
				}
			}
			//x倒入z
			//1.z没倒满，x中已经空了，这不可能
			//2.z倒满，x中还有剩余
			if(z==0)
			{
				tmpx=x-1;
				tmpy=y;
				tmpz=1;
				if(!(tmpx==ancx&&tmpy==ancy&&tmpz==ancz))
				{

					queue[rear].x=tmpx;
					queue[rear].y=tmpy;
					queue[rear].z=tmpz;
					queue[rear].preIndex=front;
					printf("(%d,%d,%d)\n",queue[rear].x,queue[rear].y,queue[rear].z);
					rear++;
				}
			}
			//y倒入z
			//1.z没倒满，y中已经空了 有前提约束y>=1
			//2.z倒满了，y中还有剩余
			if(z==0&&y>0)
			{
				tmpx=x;
				tmpy=y-1;
				tmpz=1;
				if(!(tmpx==ancx&&tmpy==ancy&&tmpz==ancz))
				{

					queue[rear].x=tmpx;
					queue[rear].y=tmpy;
					queue[rear].z=tmpz;
					queue[rear].preIndex=front;
					printf("(%d,%d,%d)\n",queue[rear].x,queue[rear].y,queue[rear].z);
					rear++;
				}
			}
			front++;//出队
			printf("\n");
		}



	}

}
