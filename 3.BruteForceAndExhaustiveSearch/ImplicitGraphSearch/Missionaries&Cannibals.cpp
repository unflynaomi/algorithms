#include<stdio.h>
//����ʿ��Ұ�˹������⣬���˴��󰶶��˵��Ұ�
int visited[4][4][2];//�󰶵Ĵ���ʿ��0,1,2,3 Ұ��Ҳ��0,1,2,3 ״̬S=0 �����󰶣�S=1�����Ұ� �����ͳ�ʼ������,ȫ��0
struct State
{
	int M;//�󰶴���ʿ����
	int C;//��Ұ������
	int S;//S=0 �����󰶣�S=1�����Ұ�
	//int preIndex;//�������stack�е����� ��ôд���������첻���ˣ�bfs������Ҫ��¼������һ���⣬����
	//dfs������Ҫ����dfs��ջ��ʱ�̱����ŵľ��ǽ� 

};


State firstUnvisitedValidState(State current);
State stack[1000];

void printPath(int top)
{
	
	if(top==0)
	   printf("(%d %d %d)\n",stack[top].M,stack[top].C,stack[top].S);
	else
	{
		printPath(top-1);//�Ȱ���֮ǰ�Ľ�㶼����� 
     	printf("(%d %d %d)\n",stack[top].M,stack[top].C,stack[top].S);//�ٴ�ӡ���Լ� 
	}

}

int main()
{


	
	int top=-1;
	top++;//topָ��ջ��Ԫ��
	stack[top].M=3;
	stack[top].C=3;
	stack[top].S=0;
	visited[3][3][0]=1;

	//��ʼdfs
	while(top>-1)
	{
		
		if(stack[top].M==0&&stack[top].C==0)
		{
			printPath(top);			
			printf("found!\n");
		   	break;
		}
		else
		{
			
			State newState=firstUnvisitedValidState(stack[top]);
			if(newState.S==-1)
			{
				
				top--;//��ջ
				
			}

			else
			{
				stack[++top]=newState;
				visited[stack[top].M][stack[top].C][stack[top].S]=1;
				//printf("��״̬Ϊ:(%d %d %d)\n",stack[top].M,stack[top].C,stack[top].S);

			}


		}
	}


}

State firstUnvisitedValidState(State current)
{
	int tryM=0;//�ȳ����Ž���״̬ת�ƣ����жϺϷ��� ��������Ծ�ת�ƣ����оͷ��� 
	int tryC=0;
	State result;
	for(int i=0; i<=2; i++)//i����ʿ�������� 
		for(int j=0; j<=2; j++)//jҰ�˵������� 
		{
			if(i+j>0&&i+j<=2)
			{

				if(current.S==0)//�����Ұ�����
				{
					//printf("������%d������ʿ��%d��Ұ�˹�ȥ\n",i,j);
					tryM=current.M-i;
					tryC=current.C-j;
					if(tryM==0&&tryC>=0&&!visited[tryM][tryC][1])//�����û�д���ʿ������ô�����������ж� ����ʿ�Ƿ��Ұ�˶� 
					{
						result.M=tryM;
						result.C=tryC;
						result.S=1;
						return result;
					}
					if(3-tryM==0&&tryC>=0&&!visited[tryM][tryC][1])//û���Ұ��˴���ʿ������Ұ�û�д���ʿ����ô�����������ж� ����ʿ�Ƿ��Ұ�˶� 
					{
						result.M=tryM;
						result.C=tryC;
						result.S=1;
						return result;
					}
					if(tryM>0&&tryC>=0&&tryM>=tryC&&3-tryM>=3-tryC&&!visited[tryM][tryC][1])
					{
						result.M=tryM;
						result.C=tryC;
						result.S=1;
						return result;

					}
				}
				else//�Ұ���������
				{
					//printf("������%d������ʿ��%d��Ұ�˹���\n",i,j);
					tryM=current.M+i;//tryMһ��>=0
					tryC=current.C+j;//tryCһ��>=0
					if(3-current.M>=i&&3-current.C>=j)//��ϣ�� �Է���֧����i������ʿ��j��Ұ�˵�����  ��Ȼ�����ⰶ��2������ʿ��2��Ұ�ˣ��㾹ȻҪ�˹���2������ʿ��0��Ұ�ˣ��ⲻ���� 
					{

						if(tryM==0&&!visited[tryM][tryC][0])//�󰶱���û�д���ʿ��Ҳû���˹�������ʿ
						{
							result.M=tryM;
							result.C=tryC;
							result.S=0;
							return result;
						}
						if(3-tryM==0&&!visited[tryM][tryC][0])//����ʿ�����˹������Ҳ��õ������������� 
						{
							result.M=tryM;
							result.C=tryC;
							result.S=0;
							return result;

						}
						if(tryM>=tryC&&3-tryM>=3-tryC&&!visited[tryM][tryC][0])
						{
							result.M=tryM;
							result.C=tryC;
							result.S=0;
							return result;

						}
					}
				}

			}
		}
	result.M=-1;
	result.C=-1;
	result.S=-1;
	return result;

}
