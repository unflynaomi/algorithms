#include<iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;
//实现Backjump-based backtracking for constraint satisfaction problems 论文 by Rina Dechter上的Example 4的带约束的图着色 基本回溯法 P152 
//问题，使用简单回溯
//输入  ColoringProblemBacktrack.txt 第一行 7 表示有7个变量 下面的7行分别表示从x1-x7都能涂什么颜色 下面是两两变量之间不能涂一样颜色的约束
std::vector<std::string> split(std::string str,std::string pattern);
int main()
{
	ifstream fin("ColoringProblemBacktrack.txt");

	int numOfVar=0;
	string numOfVarStr;
	getline(fin,numOfVarStr);
	numOfVar=atoi(numOfVarStr.c_str());
	cout<<"变量的个数为:"<<numOfVar<<endl;

	vector<string> varDomain[numOfVar+1];//变量编号从1开始  varDomain是变量的取值域
	string s;
	for(int i=1; i<=numOfVar; i++)
	{
		getline(fin,s);
		varDomain[i]=split(s," "); //string 是" ",不是单引号' ' ,单引号是char,vector有默认的拷贝构造函数
	}

	cout<<"变量的域为: "<<endl;
	for(int i=1; i<=numOfVar; i++)
	{
		for(int j=0; j<varDomain[i].size(); j++)
			cout<<varDomain[i][j]<<" ";
		cout<<endl;
	}

	vector<int> graph[numOfVar+1];//变量编号从1开始，graph是约束图


	int a;
	int b;
	while(fin>>a>>b)
	{
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	cout<<"约束图为: "<<endl;
	for(int i=1; i<=numOfVar; i++)
	{
		for(int j=0; j<graph[i].size(); j++)
			cout<<graph[i][j]<<" ";
		cout<<endl;
	}

	//回溯开始
	int backtrackCount=0;//记录回溯次数 ，分析回溯性能 
	int solveCount=0;//解的个数 
	vector<string> searchDomain[numOfVar+1]; 
	int i=1;
	searchDomain[i]=varDomain[i];//论文里的Di'
	string solution[numOfVar+1];//记录现在的解
	while(i>=1)
	{
		string selectedVal;

		while(!searchDomain[i].empty())//从头开始考虑i的取值域,每次都取 取值域中的第0个取值尝试是否兼容，试完了就弹出来
		{
			bool consistent=true;
			//检测ai-1与xi是否一致，只需检测与xi在约束图中的邻接结点 
			for(int index=0; index<graph[i].size(); index++)
			{
				int neighbour=graph[i][index];//在约束图里与xi有约束关系的变量
				if(neighbour<i)//只有在i前面的才需要检查
				{
					if(solution[neighbour]==searchDomain[i][0])//违反了约束
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
		//cout<<i<<" 取值为："<<solution[i]<<endl;

		if(solution[i].empty()) //selectedVal==Null这样不行
		{
			i--;//回溯
			backtrackCount++;
		}			
		else if(i==numOfVar)//找到了一个解
		{
			solveCount++;
			cout<<"解为：";
			for(int i=1; i<=numOfVar; i++)
				cout<<solution[i]<<" ";
			cout<<endl;
			i--;//回溯  i=7的时候，回退到i=6，给6找一个新的取值，再在6的新值的语义下找一个7的新值 
			backtrackCount++;
		}
		else//向前走
		{

			i++;
			searchDomain[i]=varDomain[i];
		}

	}
    
    cout<<"有 "<<solveCount<<" 个解"<<endl;
    cout<<"共回溯了 "<<backtrackCount<<" 次"<<endl;


//    split("red blue green"," ");
}

std::vector<std::string> split(std::string str,std::string pattern)
{
	std::string::size_type pos;//string::size_type 是find函数的返回类型，之所以不用int，是因为这样不论你的str有多长，我都能表示出它的位置信息
	std::vector<std::string> result;
	str+=pattern;//扩展字符串以方便操作
	int size=str.size();

	for(int i=0; i<size; i++)
	{
		pos=str.find(pattern,i);//从i开始查找pattern出现的位置，包括i
		if(pos<size)
		{
			std::string s=str.substr(i,pos-i);//截取从i开始长度为pos-i的字符串，包括i
			result.push_back(s);
			i=pos+pattern.size()-1;//别忘了最后在for循环里i还要++

		}
	}
	return result;
}


