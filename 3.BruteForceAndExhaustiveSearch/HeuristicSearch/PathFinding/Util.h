/* 
 * File:   PriorityQueue.h
 * Author: Administrator
 *
 * Created on 2016年12月9日, 上午11:55
 */

#ifndef UTIL
#define	UTIL
#include <iostream>
#include <iomanip>
#include <unordered_map>
#include <unordered_set>
#include <array>
#include <vector>
#include <utility>
#include <queue>
#include <tuple>
#include <algorithm>
using namespace std;

template<typename T, typename priority_t>//T是Location  priority_t是启发式函数估值
struct PriorityQueue
{
    typedef pair<priority_t, T> PQElement;
    priority_queue<PQElement, vector<PQElement>,std::greater<PQElement>> elements;//greater给pair排序的时候，会先看第一个数字的大小，如果一样，再看第二个

    inline bool empty() const
    {
        return elements.empty();
    }

    inline void put(T item, priority_t priority)
    {
        elements.emplace(priority, item);
    }

    inline T get()
    {
        T best_item = elements.top().second;    
       // cout<<elements.top().second<<" "<<elements.top().first<<endl;
        elements.pop();
        return best_item;
    }
};

template<typename Location>
vector<Location> reconstruct_path(
        Location start,
        Location goal,
        unordered_map<Location, Location>& came_from
        )
{
    vector<Location> path;
    Location current = goal;
    path.push_back(current);
    while (current != start)
    {
        current = came_from[current];
        path.push_back(current);
    }
    path.push_back(start); // optional
    std::reverse(path.begin(), path.end());
    return path;
}


// Helpers for SquareGrid::Location
//必须有这个hash的定义
//比如unordered_map<char,int> unordered_map<char,int> 键的类型是基本类型，这样的C++知道怎么把键搞成hash，存储起来，
//但是如果键的类型是tuple<int,int> C++就懵了，不知道怎么搞成hash,所以必须自己定义一个hash类
//不定义，就报错
// Since I'm using std::unordered_map<tuple<int,int>> I'm defining the
// hash function here. It would be nice if C++ automatically provided
// the hash function for tuple and pair, like Python does. It would
// also be nice if C++ provided something like boost::hash_combine. In
// any case, here's a simple hash function that combines x and y:
//来自C++网对hash函数的介绍
//Hash
//A unary function object type that takes an object of type key type as argument and returns a unique value of type size_t(size_t就是无符号整数) based on it. This can either be a class implementing a function call operator or a pointer to a function (see constructor for an example). This defaults to hash<Key>, which returns a hash value with a probability of collision approaching 1.0/std::numeric_limits<size_t>::max().
//The unordered_map object uses the hash values returned by this function to organize its elements internally, speeding up the process of locating individual elements.
//Aliased as member type unordered_map::hasher.
//hash函数只接受map里的键的类型作为参数，所以是单参数的，作用就是创建独特的哈希值,这个函数是不可省略的
namespace std {

    template <>
    struct hash<tuple<int, int> >
    {

        inline size_t operator()(const tuple<int, int>& location) const
        {
            int x, y;
            tie(x, y) = location; //把location里的x和y注入x和y之中，其实是让x y成为location里x 和 y的引用
            return x * 1812433253 + y;
        }
    };
}

// For debugging it's useful to have an ostream::operator << so that we can write cout << foo

std::basic_iostream<char>::basic_ostream& operator<<(std::basic_iostream<char>::basic_ostream& out, tuple<int, int> loc)
{
    int x, y;
    tie(x, y) = loc;
    out << '(' << x << ',' << y << ')';
    return out;
}

#endif	/* UTIL */

