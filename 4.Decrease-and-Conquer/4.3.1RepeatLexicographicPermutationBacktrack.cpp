#include<iostream>
#include<map>
using namespace std;
//按照字典序排序 产生1-n的全排列，使用放回，无需使用额外的空间 
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
        
		for(map<int, int>::iterator iter = inputMap.begin(); iter != inputMap.end(); iter++)
		{




			if(iter->second>0)
			{
//				cout<<"传入的map为:\n";
//				for(map<int, int>::iterator iter3 = inputMap.begin(); iter3 != inputMap.end(); iter3++)
//				{
//					cout<<iter3->first<<"\t"<<iter3->second<<endl;
//				}
                
				permute[size]=iter->first;				
				iter->second--;
				//有些人直接在inputMap上用iter->second-- ，这是一个错误点，不可以直接改变母版的数字可用情况 
				//假设我要排的可重集是 2233 那么inputMap 就是 2 2 3 2 ，我排第一个位置可能是 2，inputMap就是
				//2 1 3 2，移动iter,如果我排第一个位置是3，那么inputMap就是 2 2 3 1，如果我试2的时候直接在inputMap上修改，那么
				//再试3的时候，inputMap 就成了 2 1 3 1 但事实上我一个2也没用。 所以他们就想出来重新创建一个map
				//在newInputMap上修改，就会把原来的inputMap保持不变了
				//但是这样毕竟浪费空间，不如在递归完成以后，把你用完的那个数给它放回去， 排第一个位置可能是 2
				//inputMap就是 2 1 3 2，我排完2开头的可重集以后，我把这个2再放回去，就是 2 2 3 2，再试3的时候， 
                //inputMap就是 2 2 3 1 还是正确的
				 
//				cout<<"递归调用!当前排列为:";
//				for(int i=0; i<size+1; i++)
//					printf("%d ",permute[i]);
//				printf("\n");
//				printf("修改后的map为:\n");
//				for(map<int, int>::iterator iter2 = inputMap.begin(); iter2 != inputMap.end(); iter2++)
//				{
//					cout<<iter2->first<<"\t"<<iter2->second<<endl;
//				}
//				cout<<endl;
				permutation(permute,size+1,inputMap);
				iter->second++;
//				cout<<"递归结束!"<<endl;
//				cout<<"此时iter指向:"<<iter->first<<"\t"<<iter->second<<endl; 
				

			}

		}
//		cout<<endl;		
	}
}

int main()
{
	n=6;
	int input[n]= {2,4,5,5,7,7};
	map<int,int> inputMap;//统计了不重复的每个数字，以及它的个数 ,int的值默认初始化为0 
	for(int i=0; i<n; i++)
		inputMap[input[i]]++;
	for(map<int, int>::iterator iter = inputMap.begin(); iter != inputMap.end(); iter++)
	{
		cout<<iter->first<<"\t"<<iter->second<<endl;
	}
	int permute[n];
	permutation(permute,0,inputMap);
	cout<<"共有"<<count<<endl;


}
