/* 
 * File:   SimpleGraph.h
 * Author: Administrator
 *
 * Created on 2016年12月9日, 上午10:49
 */

#ifndef SIMPLEGRAPH_H
#define	SIMPLEGRAPH_H


template<typename L>
struct SimpleGraph
{
    typedef L Location;
    typedef typename vector<Location>::iterator iterator;
      const vector<Location> neighbors(Location id)
    {
        return edges[id];
    }
    SimpleGraph(){} //应该有这个函数，供子类调用，但是没有这个函数在netbeans里没有报错，在dev C++里肯定会报错
    SimpleGraph(unordered_map<Location, vector<Location> > pedges)
    {
        edges=pedges;
    } 
    //没有这个带参数的构造函数竟然也不报错，在dev C++里肯定会报错
    private:
    unordered_map<Location, vector<Location> > edges;

   
};

////在一般的C++里，都是使用 A b(pp);来初始化对象
////但是这里使用的是初始化列表的方式进行初始化 vector<int> va{1, 2, 3};
////而且还会自动匹配类型 这里初始化的就是 edges 这个数据成员
////字符型的location 映射到字符向量上
SimpleGraph<char> example_graph{
    {
        {'A',
            {'B'}},
        {'B',
            {'A', 'C', 'D'}},
        {'C',
            {'A'}},
        {'D',
            {'E', 'A'}},
        {'E',
            {'B'}}
    }};


 template<typename L>
struct SimpleGraphWithWeights:SimpleGraph<L>
{
    typedef L Location; //这个Location要再次定义，直接使用父类的定义，但是这个类的template<typename L>泛型一定要定义出来
    SimpleGraphWithWeights(unordered_map<Location, unordered_map<Location,int>> pedges)
    {
        edges=pedges;
    }
    //这里没有调用父类的构造函数，应该是编译器的问题,在dev C++里这么写会报错
    //（如果父类只有有参数的构造方法，则子类必须显示调用此带参构造方法）
    //现在调用的是父类的默认的无参数构造函数
    
    const vector<Location> neighbors(Location id)
    {
        unordered_map<Location,int> info=edges[id];
        vector<Location> neighbors; //有人写成const vector<Location> neighbors; 那是不行的，这样的vector无法往里面加入元素，不能push_back const vector用于参数传递
        for(typename unordered_map<Location,int>::iterator iter = info.begin(); iter != info.end(); iter++)
        // 写成for(unordered_map<Location,int>::iterator iter = info.begin(); iter != info.end(); iter++) 会报下面的错
        //SimpleGraph.h:78:13: error: need 'typename' before 'std::unordered_map<L, int>::iterator' because 'std::unordered_map<L, int>' is a dependent scope    
        //必须加typename 因为这个用了Location这个模板参数里的成员iterator 必须等Location由用户确定了以后，再解析出其中的iterator
        {    
           neighbors.push_back(iter->first);
        }
        return neighbors;
    }
    
    int getWeight(Location from,Location to)
    {
        return edges[from][to];
    }
    private:
    unordered_map<Location, unordered_map<Location,int> > edges;
    
};

SimpleGraphWithWeights<char> example_graph2(
    {//表示组成了unordered_map
        {'0',
           {{'1',4},{'2',6},{'3',6}} },
        {'1',
           {{'2',1},{ '4',7}}},
        {'2',
           {{'4',6},{'5',4}}},
        {'3',
           {{'2',2},{'5',5}}},
        {'4',
           { {'6',6}}},
         {'5',
            {{'4',1},{'6',8}}}                    
    }//表示组成了unordered_map;
   );    
#endif	/* SIMPLEGRAPH_H */

