#include<iostream>
#include<map>
using namespace std;
//���տ��ؼ��ֵ������� ����1-n��ȫ���У���Ҫʹ�ö���ռ� 
int n;
int count;
void permutation(int* permute,int size,map<int, int>& inputMap)
{
	if(size==n)
	{
		for(int i=0; i<size; i++)
			printf("%d ",permute[i]);
		printf("\n");
		count++;
	}
	else
	{
        //�ݹ������ɺ���inputMap����ԭ�����Ǹ����Ͼ�������newInputMap���޸ĵ� 
		for(map<int, int>::iterator iter = inputMap.begin(); iter != inputMap.end(); iter++)
		{




			if(iter->second>0)
			{
//				cout<<"�����mapΪ:\n";
//				for(map<int, int>::iterator iter3 = inputMap.begin(); iter3 != inputMap.end(); iter3++)
//				{
//					cout<<iter3->first<<"\t"<<iter3->second<<endl;
//				}
                map<int, int> newInputMap=inputMap;
				permute[size]=iter->first;				
				newInputMap[iter->first]--;
				//��Щ��ֱ����inputMap����iter->second-- ������һ������㣬������ֱ�Ӹı�ĸ������ֿ������ 
				//������Ҫ�ŵĿ��ؼ��� 2233 ��ôinputMap ���� 2 2 3 2 �����ŵ�һ��λ�ÿ����� 2��inputMap����
				//2 1 3 2���ƶ�iter,������ŵ�һ��λ����3����ôinputMap���� 2 2 3 1���������2��ʱ��ֱ����inputMap���޸ģ���ô
				//����3��ʱ��inputMap �ͳ��� 2 1 3 1 ����ʵ����һ��2Ҳû�á� 

//				cout<<"�ݹ����!��ǰ����Ϊ:";
//				for(int i=0; i<size+1; i++)
//					printf("%d ",permute[i]);
//				printf("\n");
//				printf("�޸ĺ��mapΪ:\n");
//				for(map<int, int>::iterator iter2 = inputMap.begin(); iter2 != inputMap.end(); iter2++)
//				{
//					cout<<iter2->first<<"\t"<<iter2->second<<endl;
//				}
//				cout<<endl;
				permutation(permute,size+1,newInputMap);
//				cout<<"�ݹ����!"<<endl;
//				cout<<"��ʱiterָ��:"<<iter->first<<"\t"<<iter->second<<endl; 
				

			}

		}
//		cout<<endl;		
	}
}

int main()
{
	n=6;
	int input[n]= {2,4,5,5,7,7};
	map<int,int> inputMap;//ͳ���˲��ظ���ÿ�����֣��Լ����ĸ��� ,int��ֵĬ�ϳ�ʼ��Ϊ0 
	for(int i=0; i<n; i++)
		inputMap[input[i]]++;
	for(map<int, int>::iterator iter = inputMap.begin(); iter != inputMap.end(); iter++)
	{
		cout<<iter->first<<"\t"<<iter->second<<endl;
	}
	int permute[n];
	permutation(permute,0,inputMap);
	cout<<"����"<<count<<endl;


}
