//�㷨�������ž��� 7.5.2 7-3��ˮ����
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
	State queue[1000];//����
	int front=0;
	int rear=0;
	queue[rear].x=6;
	queue[rear].y=0;
	queue[rear].z=0;
	queue[rear].preIndex=-1;

	rear++;
	//���������ʽͼ
	while(front!=rear)
	{
		if(queue[front].x==4)//ֻ��x���������4��ˮ��
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
			printf("��չ (%d,%d,%d)\n",x,y,z);
			//����չ�Ľ�㲻�ܺ����Ƚ��һ�����������Ѻܶ�û���õĶ���
			int ancx=queue[queue[front].preIndex].x;
			int ancy=queue[queue[front].preIndex].y;
			int ancz=queue[queue[front].preIndex].z;

			int tmpx=0;
			int tmpy=0;
			int tmpz=0;

			//����ʼ
			//y����x
			//1.x������x=6��y�л���ʣ��y=y-(6-x),y-(6-x)>0,�ⲻ����
			//2.xû������y���Ѿ�ɶҲ��ʣ
			if(x<6&&y>0)
			{
				tmpx=x+y;
				tmpy=0;
				tmpz=z;

				if(!(tmpx==ancx&&tmpy==ancy&&tmpz==ancz))//����չ�Ľ�㲻�ܺ����Ƚ��һ�����������Ѻܶ�û���õĶ���
				{

					queue[rear].x=tmpx;
					queue[rear].y=tmpy;
					queue[rear].z=tmpz;
					queue[rear].preIndex=front;
					printf("(%d,%d,%d)\n",queue[rear].x,queue[rear].y,queue[rear].z);
					rear++;
				}
			}
			//z����x
			//1.x������x=6��z�л���ʣ��z=z-(6-x),z-(6-x)>0,�ⲻ����
			//2.xû������z��ɶҲ��ʣ
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
			//x����y
			//1.yû������x��ɶҲ��ʣ����ôy+x<3 �ⲻ����
			//2. y�����ˣ�x�л���ʣ��
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
			//z����y
			//1.y�����ˣ�z�л���ʣ�� ���z�ܵ���y ˵�� z=1 y<3 ����y=3 z=1 �ⲻ����
			//2.yû������z���Ѿ�����
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
			//x����z
			//1.zû������x���Ѿ����ˣ��ⲻ����
			//2.z������x�л���ʣ��
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
			//y����z
			//1.zû������y���Ѿ����� ��ǰ��Լ��y>=1
			//2.z�����ˣ�y�л���ʣ��
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
			front++;//����
			printf("\n");
		}



	}

}
