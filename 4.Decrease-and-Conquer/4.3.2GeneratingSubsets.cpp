#include<iostream>
#include<string>
#include <sstream>
#include<vector>
using namespace std;
//产生a1,...,an的子集

string getString ( const int n )

{

	stringstream newstr;
	newstr<<n;
	return newstr.str();

}

vector<string> getSubset(int n)
{
	if(n==0)
	{
		vector<string> former;
		former.push_back("");
		return former;
	}
	else
	{
		vector<string> former=getSubset(n-1);
		int k=former.size();
		for(int i=0; i<k; i++)
		{
			string str=former[i];
			former.push_back(str+getString(n));
		}
		return former;
	}

}

int main()
{

	vector<string> subset;
	subset=getSubset(5);
	cout<<"size为: "<<subset.size()<<endl;
	for(int i=0;i<subset.size();i++)
	  cout<<subset[i]<<endl;
	cout<<endl;  
  

}
