#include<iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <set>
#include <algorithm>
using namespace std;
//ʵ��Backjump-based backtracking for constraint satisfaction problems ���� by Rina Dechter�ϵ�Example 4�Ĵ�Լ����ͼ��ɫ �������ݷ� P152
//���⣬ʹ�ü򵥻���
//����  ColoringProblemBacktrack.txt ��һ�� 7 ��ʾ��7������ �����7�зֱ��ʾ��x1-x7����Ϳʲô��ɫ ��������������֮�䲻��Ϳһ����ɫ��Լ��
std::vector<std::string> split(std::string str,std::string pattern);
int main()
{
	ifstream fin("ColoringProblemBacktrack.txt");

	int numOfVar=0;
	string numOfVarStr;
	getline(fin,numOfVarStr);
	numOfVar=atoi(numOfVarStr.c_str());
	cout<<"�����ĸ���Ϊ:"<<numOfVar<<endl;

	vector<string> varDomain[numOfVar+1];//������Ŵ�1��ʼ  varDomain�Ǳ�����ȡֵ��
	string s;
	for(int i=1; i<=numOfVar; i++)
	{
		getline(fin,s);
		varDomain[i]=split(s," "); //string ��" ",���ǵ�����' ' ,��������char,vector��Ĭ�ϵĿ������캯��
	}

	cout<<"��������Ϊ: "<<endl;
	for(int i=1; i<=numOfVar; i++)
	{
		for(int j=0; j<varDomain[i].size(); j++)
			cout<<varDomain[i][j]<<" ";
		cout<<endl;
	}

	vector<int> graph[numOfVar+1];//������Ŵ�1��ʼ��graph��Լ��ͼ��ÿ�������������ñ�����Լ����ϵ�ı���


	int a;
	int b;
	while(fin>>a>>b)
	{
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	cout<<"Լ��ͼΪ: "<<endl;
	for(int i=1; i<=numOfVar; i++)
	{
		for(int j=0; j<graph[i].size(); j++)
			cout<<graph[i][j]<<" ";
		cout<<endl;
	}

	set<int> ancestor[numOfVar+1];//����x1,x2,...,x7������˳��������ȼ�
	for(int i=1; i<=numOfVar; i++)
	{
		for(int j=0; j<graph[i].size(); j++)
			if(graph[i][j]<i)//һ��Ҫ��i��ǰ��
				ancestor[i].insert(graph[i][j]);
	}

	cout<<"���ȼ�Ϊ: "<<endl;
	set<int>::iterator it;
	for(int i=1; i<=numOfVar; i++)
	{
		if(ancestor[i].empty())
			cout<<"�ռ�";
		else
			for(it=ancestor[i].begin(); it!=ancestor[i].end(); it++)
				cout<<*it<<" ";
		cout<<endl;

	}
	//���ݿ�ʼ
	int iprev;
	set<int> tmp;
	int backtrackCount=0;//��¼���ݴ��� ��������������
	int solveCount=0;//��ĸ���
	vector<string> searchDomain[numOfVar+1];
	set<int> I[numOfVar+1];//ÿ�������� induced ancestor set
	int i=1;
	searchDomain[i]=varDomain[i];//�������Di'
	I[i]=ancestor[i];
	string solution[numOfVar+1];//��¼���ڵĽ�
	while(i>=1)
	{
		string selectedVal;

		while(!searchDomain[i].empty())//��ͷ��ʼ����i��ȡֵ��,ÿ�ζ�ȡ ȡֵ���еĵ�0��ȡֵ�����Ƿ���ݣ������˾͵�����
		{
			bool consistent=true;
			//���ai-1��xi�Ƿ�һ�£�ֻ������xi��Լ��ͼ�е��ڽӽ��
			for(int index=0; index<graph[i].size(); index++)
			{
				int neighbour=graph[i][index];//��Լ��ͼ����xi��Լ����ϵ�ı���
				if(neighbour<i)//ֻ����iǰ��Ĳ���Ҫ���
				{
					if(solution[neighbour]==searchDomain[i][0])//Υ����Լ��
					{
						consistent=false;
						break;
					}

				}
			}

			if(consistent)
			{
				selectedVal=searchDomain[i][0];
				searchDomain[i].erase(searchDomain[i].begin());
				break;
			}
			else
			{
				searchDomain[i].erase(searchDomain[i].begin());

			}


		}

		solution[i]=selectedVal;
		//cout<<i<<" ȡֵΪ��"<<solution[i]<<endl;

		if(solution[i].empty()) //selectedVal==Null��������
		{
			if(i==1)//֮����Ҫ��i=1�������г���������Ϊ���D1'����Ҳû��ֵ����ѡ�ˣ���ô˵���������̽����ˣ�����I1=�ռ�
				//�����ʱ���� *(--I[i].end()); һ��������⣬�ռ� ��ָ��
			{
				i=0;
			}
			else
			{
				iprev=i;//����
				i=*(--I[i].end());//I[i]�е����һ������
				tmp.clear();
				set_union (I[i].begin(), I[i].end(), I[iprev].begin(), I[iprev].end(), inserter(tmp,tmp.begin()));
				tmp.erase(i);
				I[i]=tmp;

			}

			backtrackCount++;
		}
		else if(i==numOfVar)//�ҵ���һ����
		{
			solveCount++;
			cout<<"��Ϊ��";
			for(int i=1; i<=numOfVar; i++)
				cout<<solution[i]<<" ";
			cout<<endl;
			i--;
			//����  i=7��ʱ�򣬻��˵�i=6����6��һ���µ�ȡֵ������6����ֵ����������һ��7����ֵ
			//ע�����ҵ�һ�����ʱ����ݣ�����ͨ�����ʹ��I���ϻ����ǲ�ͬ�ģ����ҵ�һ���������£����е�I���϶�
			//��ʼ���������ǵ����ȼ�����i=7�����ǲ��ܻص�����induced parent x5 ��x5����һ��ֵblue,��©��x5=green�µ���һ���⣬������©��ģ���Ӧ�ûص�x6
			//���x6����ֵ�ģ���ô������ѡ�Ǹ�ֵ������I7����7�����ȼ������x6����ֵ�ģ���ôֱ�ӻ�����x2 
			backtrackCount++;
		}
		else//��ǰ��
		{

			i++;
			searchDomain[i]=varDomain[i];
			I[i]=ancestor[i];
		}

	}

	cout<<"�� "<<solveCount<<" ����"<<endl;
	cout<<"�������� "<<backtrackCount<<" ��"<<endl;


//    split("red blue green"," ");
}

std::vector<std::string> split(std::string str,std::string pattern)
{
	std::string::size_type pos;//string::size_type ��find�����ķ������ͣ�֮���Բ���int������Ϊ�����������str�ж೤���Ҷ��ܱ�ʾ������λ����Ϣ
	std::vector<std::string> result;
	str+=pattern;//��չ�ַ����Է������
	int size=str.size();

	for(int i=0; i<size; i++)
	{
		pos=str.find(pattern,i);//��i��ʼ����pattern���ֵ�λ�ã�����i
		if(pos<size)
		{
			std::string s=str.substr(i,pos-i);//��ȡ��i��ʼ����Ϊpos-i���ַ���������i
			result.push_back(s);
			i=pos+pattern.size()-1;//�����������forѭ����i��Ҫ++

		}
	}
	return result;
}


