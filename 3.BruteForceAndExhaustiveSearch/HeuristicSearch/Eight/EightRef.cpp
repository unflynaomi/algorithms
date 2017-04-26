#pragma warning(disable:4786) 
#include <algorithm> 
#include <cstdio> 
#include <set> 
#include <utility> 
#include <ctime> 
#include <cassert> 
#include <cstring> 
#include <iostream>
using namespace std;

/*item��¼�����ռ���һ�����         
state ��¼��������ʽ��ʾ��8������          
blank ��¼��ǰ�ո�λ�ã���Ҫ���ڳ����Ż���
��չʱ�ɲ�����Ѱ�ҿո�λ��         
g, h  ��Ӧg(n), h(n)          
pre   ��¼��ǰ������ĸ������չ���� */
struct item  
{          
	int state;          
	int blank;         
	int g;         
	int h;           
	int pre; 
};

const int MAXSTEPS = 100000; 
const int MAXCHAR = 100; 
char buf[MAXCHAR][MAXCHAR]; //open�� 
item open[MAXSTEPS]; 
//vector<item> open;
int steps = 0;

//closed���Ѳ�ѯ״ֻ̬Ҫ֪����״̬�Լ������ĸ������չ�������ɣ��������·�� 
//ÿ��ֻ��õ���Ӧfֵ��С�Ĵ���չ��㣬�ö�ʵ�����Ч��
pair<int, int> closed[MAXSTEPS];
//��¼��ÿ��״̬�ľ������ݺ���չ���Ľ����closed���е����� 


//���룬��8���������ת��Ϊ������ʾ 

bool read(pair<int,int> &state) 
{          
	if (!gets(buf[0]))// gets���Դӿ���̨���տո���Ϊ�Ѿ����������ض�����ˣ���scanf�����ո񡢻س���Tab��������Ϊ������������������ܽ��տո�          
		return false;         
	if (!gets(buf[1]))  //gets�����س�������               
		return false;         
	if (!gets(buf[2]))                 
		return false; 

	//cout << strlen(buf[0]) << ' ' << strlen(buf[1]) << ' ' << strlen(buf[2]) << endl;
	assert(strlen(buf[0]) == 5 && strlen(buf[1]) == 5 && strlen(buf[2]) == 5);
	// astar.in�е�ÿ�����ݳ��ȱ���Ϊ5
	state.first = 0;
	for (int i = 0, p = 1; i < 3; ++i)         
	{                  
		for (int j = 0; j < 6; j += 2)                  
		{                          
			if (buf[i][j] == '0')                                  
				state.second = i * 3 + j / 2;     // state.secondΪ0���ո��ڽڵ��е�λ�� ����˳������                 
			else                                  
				state.first += p * (buf[i][j] - '0');                
			p *= 10;                 
		}         
	}

	/* �����Խڵ�Ϊ:   
	1 2 3
	8 0 4
	7 6 5
	��state.firstΪ567408321��state.secondΪ4
	*/
	return true;
}

//���㵱ǰ����Ŀ��ľ��� 
int calculate(int current, int target)  // return h=the sum of distances each block have to move to the right position,�����each block�������ո�
{          
	int c[9], t[9];         
	int i, cnt = 0;          
	for (i = 0; i < 9; ++i)         
	{                  
		c[current % 10] = t[target % 10] = i;                 
		current /= 10;                
		target /= 10;         
	}  

	for (i = 1; i < 9; ++i)                  
		cnt += abs(c[i] / 3 - t[i] / 3) + abs(c[i] % 3 - t[i] % 3);         

	return cnt; 
}

//open���н���ѡ��ʱ�Ĺ��� f(n) = g(n) + h(n)
//Binary function that accepts two elements in the range as arguments, and returns a value convertible to bool. The value returned indicates whether the element passed as first argument is considered to be less than the second
//��Ϊheapʼ�ն�ȡ���ֵ����������������true,��ô˵����һ���ͱȵڶ���С���ҿ϶�ѡ�ڶ�������ô��fֵ��Сʱ����ѡ�ڶ���

class cmp 
{ 
public: inline bool operator()(item a, item b)         
		{                  
			return a.g + a.h > b.g + b.h;         
		} 
}; 

//��������ʽ��ʾת��Ϊ�����ʾ���
void pr(int state) 
{          
	memset(buf, ' ', sizeof(buf));         
	for (int i = 0; i < 3; ++i)         
	{                  
		for (int j = 0; j < 6; j += 2)                 
		{                          
			if (state % 10)
				buf[i][j] = state % 10 + '0';                         
			state /= 10;                 
		}       

		buf[i][5] = '\0';                 
		puts(buf[i]);
	}
}

//�����жϵ�ǰ�ո��Ƿ�������Ӧ�����ƶ�
inline bool suit(int a, int b)  //�ո��ƶ��������Ϊ(a,b)
{          
	return (a >= 0 && a < 3 && b >= 0 && b < 3); 
} 


//�ݹ��������·��
void path(int index) 
{          
	if (index == 0)         
	{                  
		pr(closed[index].first);                 
		puts("");                 
		return;         
	}          
	path(closed[index].second);         
	pr(closed[index].first); //��������ʽ��ʾת��Ϊ�����ʾ���         
	puts("");         
	++steps; 
}

int getNixuNum( int state ) //��ڵ���������
{
	int sum = 0;
	int result[9];
	memset( result, 0, sizeof(result) );
	//cout << result[8] << result[7] << endl;

	char buf[10];
	itoa( state, buf, 10 );//��stateת��Ϊ�ַ�����10��ʾת��10������ 
	//cout << buf << endl;
	int k = 0;
	while( buf[k] != '\0' )
	{
		result[9-k-1] = buf[k] - '0';
		k++;
	}
	
	for( int i = 0; i < 9; i++ )
	{
		for( int j = i + 1; j < 9; j++ )
		{
			if( result[i] && result[j] && result[i] > result[j] )
			{
				sum++;
			}
		}
	}
	return sum; //����3*3����������������
}

int main() 
{    
	//cout << getNixuNum(87654321);
	//open.resize(MAXSTEPS);
	unsigned int t1 = clock();    
	//cout << open.size() << endl;
	if( freopen("astar.in", "r", stdin) == NULL ) 
	//�����ض���������������ú��������ڲ��ı����ԭò������¸ı������������,����ʵ��oj����Դ���������л� 
	{
		cout << "file not find\n";
		exit(0);
	};    

	freopen("astar2.out", "w", stdout);         
	set<int>states;         
	char tmp[100];          
	int i, x, y, a, b, nx, ny, end, next, index, kase = 0;         
	pair<int,int> start, target;         
	item head;          //4�������ƶ�ʱ��ƫ����          
	const int xtran[4] = {-1, 0, 1, 0};         
	const int ytran[4] = {0, 1, 0, -1};          
	const int p[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

	while (read(start))  // ��ȡ����״̬�ڵ�       
	{                  
		unsigned int t2 = clock();                  
		printf("Case %d:\n\n", ++kase);                 
		gets(tmp);     //����һ������            
		read(target);  // ��ȡĿ��״̬�ڵ�          
		gets(tmp); //�ٶ���һ�����У�׼��������һ�����ʵ�� 
		

		int targetNixuNum = getNixuNum(target.first);
		//�����ߵ������������ͬΪ������ͬΪż�������޽�
		if( !(getNixuNum(start.first)&1 && targetNixuNum&1 || !(getNixuNum(start.first)&1) && !(targetNixuNum&1)) )
		//&�����������˼�������ż�������һλ�����ƾ���0,0&1=0���������������1&1=1 
		{
			cout << "�޷��ӳ�ʼ�ڵ㵽��̬�ڵ�\n";
			exit(0);
		}
		//��ʼ��open������ʼ״̬����
		open[0].state = start.first;                  
		open[0].h = calculate(start.first, target.first); // ���㵱ǰ�ڵ㵽Ŀ��ڵ�Ĺ��ƾ���                
		open[0].blank = start.second;                 
		open[0].pre = -1;    // ��ʼ�ڵ��޸��ڵ�             
		open[0].g = 0;  // ��ʼ�ڵ��gΪ0               
		index = 0;                  
		states.insert(start.first); // ��չ���ڵ㱣����states�У������ֹ���״̬������states�У�statesΪset<int>���ͣ����е�states�е�Ԫ��Ψһ

		//��ȡopen����fֵ��СԪ�ط���closed�����Ըý�������չ
		for (end = 1; end > 0; ++index)   // endΪopen���е�Ԫ�ظ�����һֱѭ����open��Ϊ��   endָ��������һ��Ԫ�صĺ�һ��Ԫ��           
		{                          
			assert(index < MAXSTEPS);       
			//��ʱ�洢                         
			head = open[0]; // ����ʹ��pop_heap������push_heap����������open[0]Ϊg+h��С��Ԫ��

			//����closed���¼��ǰ��ֺ����ĸ������չ�������ý��϶�����closed���У�
			closed[index].first = open[0].state; //����close���У���ʾ�Ѿ���չ��Ľڵ㣬�����forѭ������չ��ڵ�                         
			closed[index].second = open[0].pre; // index��ʾ��ǰclose���е�ǰ��չ�ڵ���±꣬�������������ĸ��������� 
			//��open����ɾ���ý��                          
			pop_heap(open, open + end, cmp());//endָ�������һ��λ�õĺ���һ��λ�ã�Ϊalgorithm�ļ��еĺ�������һ������ָ����ʼλ�ã��ڶ���ָ��������������ָ���ȽϺ���                         
			--end; //pop_heapֻ�ǰ� head���ŵ������һ��λ���ϣ�����Ҫ��ǰ�ƶ�һ��end,������İ�headɾȥ    

			//�õ�������ݹ����·��
			if (head.state == target.first)                         
			{                                  
				path(index);                                 
				break;                         
			}

			x = head.blank / 3;                         
			y = head.blank % 3; //�ո���3*3�����е�x,y����
			/*
			    |2 0 3|
			A = |1 8 4|
			    |7 6 5| // ����3*3������
			��head.blank=1
			x=0,y=1,���ո����3*3���������±�Ϊ(0,1)
			*/
			for (i = 0; i < 4; ++i)                         
			{                                  
				nx = x + xtran[i];                                 
				ny = y + ytran[i];   
				/*
				i=0ʱ��(nx,ny��Ϊ��ǰ�ո������ƶ�һ��������
				i=1ʱ��(nx,ny��Ϊ��ǰ�ո������ƶ�һ��������
				i=2ʱ��(nx,ny��Ϊ��ǰ�ո������ƶ�һ��������
				i=3ʱ��(nx,ny��Ϊ��ǰ�ո������ƶ�һ��������
				*/
				if (suit(nx, ny)) // �ж��Ƿ��ܹ��ƶ�
				{                                          
					a = head.blank; // �ո�ǰλ��,���������AΪ����a=1                                       
					b = nx * 3 + ny; // �ո��ƶ������λ��,��ʼ���ܹ����ұ��ƶ�����b=0*3+2=2                                        
					//����ʮ���Ʊ�ʾ������Ӧ��������λ                                          
					next = head.state + ((head.state % p[a + 1]) / p[a] - (head.state % p[b + 1]) / p[b]) * p[b]  + ((head.state % p[b + 1]) / p[b] - (head.state % p[a + 1]) / p[a]) * p[a];   
					// ��head.state=567481302,�ո������ƶ�һ�κ�next=567481032,��Ϊ�ƶ���Ľڵ�
					
					// �ж��ܷ��ɵ�ǰ�ڵ㵽��Ŀ��ڵ�,��һ�еļ�֦�ǳ����ģ����������չ�ģ�����������Ŀ���㣬��ô������չ�� 
					if( ( getNixuNum(next)&1 && targetNixuNum&1 ) || ( !(getNixuNum(next)&1) && !(targetNixuNum&1) ) )
					{
						//�ж��Ƿ��Ѿ����ɹ������Ѿ����ֹ�
						if (states.find(next) == states.end()) //û���־ͱ���һ�£�Ҳ����open��   
						//��֤���������Ѿ����ɹ��Ľ��                                     
						{                                                  
							states.insert(next);                                                     
							open[end].pre = index; //��չ����ӽڵ㣬�丸�ڵ�Ϊ��ǰ��չ�ڵ�                                                
							open[end].blank = b;                                                 
							open[end].state = next;                                                  
							open[end].h = calculate(next,target.first); 
							open[end].g  = head.g + 1;  
							++end;  //open����Ԫ�ؼ�1                                                
							push_heap(open, open + end, cmp());    //ѹ�����                                     
						}           
					}
					                      
				}                         
			}                 
		} 

		if (end <= 0)                          
			puts("No solution");
		else                 
		{                          
			printf("Num of steps: %d\n", steps);                          
			printf("Num of expanded: %d\n", index);                         
			printf("Num of generated: %d\n", index + end);                         
			printf("Time consumed: %d\n\n", clock() - t2);                 
		} 

		states.clear();                 
		steps = 0;         
	}          
	printf("Total time consumed: %d\n", clock() - t1);         
	return 0;
}
