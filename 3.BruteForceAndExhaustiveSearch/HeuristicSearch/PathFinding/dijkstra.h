/* 
 * File:   dijkstra.h
 * Author: Administrator
 *
 * Created on 2016年12月12日, 上午10:29
 */

#ifndef DIJKSTRA_H
#define	DIJKSTRA_H

#include"Util.h"
#include"SimpleGraph.h"
#include"SquareGrid.h"
#include <stack>  


/*
 * 
 */
template<typename Graph>
void dijkstra_search
(const Graph& graph,
        typename Graph::Location start,
        typename Graph::Location goal,
        unordered_map<typename Graph::Location, typename Graph::Location>& came_from,
        unordered_map<typename Graph::Location, double>& cost_so_far)
{
    typedef typename Graph::Location Location;
    PriorityQueue<Location, double> frontier;
    frontier.put(start, 0);

    came_from[start] = start;
    cost_so_far[start] = 0;

    while (!frontier.empty())
    {
        auto current = frontier.get();

        if (current == goal)
        {
            break;
        }

        for (auto next : graph.neighbors(current))
        {
            double new_cost = cost_so_far[current] + graph.cost(current, next);
            if (!cost_so_far.count(next) || new_cost < cost_so_far[next])
            {
                cost_so_far[next] = new_cost;
                came_from[next] = current;
                frontier.put(next, new_cost);
               
            }
        }
    }
}

//直接在main函数里调用的例子，在格子图里使用Dijkstra来搜索从起点到终点的最短路径
void grid_dijkstra_dest_exp()
{
    GridWithWeights grid = make_diagram4();
    SquareGrid::Location start{1, 4};
    SquareGrid::Location goal{8, 5};
    unordered_map<SquareGrid::Location, SquareGrid::Location> came_from;
    unordered_map<SquareGrid::Location, double> cost_so_far;
    dijkstra_search(grid, start, goal, came_from, cost_so_far);
    draw_grid(grid, 2, nullptr, &came_from);
    std::cout << std::endl;
    draw_grid(grid, 3, &cost_so_far, nullptr);
    std::cout << std::endl;
    vector<SquareGrid::Location> path = reconstruct_path(start, goal, came_from);
    draw_grid(grid, 3, nullptr, nullptr, &path);
}


//普通带权图的Dijkstra,能算出从起点0到达所有各个结点的最短路径
void SimpleGraphWithWeightsDijkstra()
{
      
      //typedef typename SimpleGraphWithWeights::Location Location;
      //这样写不行 dijkstra.h:60:24: error: 'template<class L> struct SimpleGraphWithWeights' used without template parameters
       typedef typename SimpleGraphWithWeights<char>::Location Location;
      
       PriorityQueue<Location, int> open;
       unordered_map<Location,int> distance;//记录了距离起点的距离
       unordered_map<Location,Location> path;//记录了每个结点的前驱
       
       open.put('0',0);
       distance['0']=0;
       path['0']='#';
       
       while(!open.empty())
       {
           Location current=open.get();//获取优先队列最前面的元素，同时会把最前面的元素弹出来
           for(auto neighbor:example_graph2.neighbors(current))
           {
               int newDistance=distance[current]+example_graph2.getWeight(current,neighbor);
               if(!distance.count(neighbor)||newDistance<distance[neighbor])
                 //有两种情况要更新，1.之前没有路径到neighbor,现在有了通过current 2.找到了更短的路径，合并在一起写
               {
                   open.put(neighbor,newDistance);
                   distance[neighbor]=newDistance;
                   path[neighbor]=current;
               }                   
                   
           }            
               
       }
     
       for(unordered_map<Location,int>::iterator iter =distance.begin();iter!=distance.end();iter++)
       {
           cout<<iter->first<<" 距离起点的距离为: "<<iter->second<<endl;           
       }
       cout<<endl;
       for(unordered_map<Location,Location>::iterator iter =path.begin();iter!=path.end();iter++)
       {
           cout<<iter->first<<" 的前驱为: "<<iter->second<<endl;           
       }
       cout<<endl;
       
       cout<<"从0到6的路径为:"<<endl;
       Location tmp='6';
       stack<Location> resultPath;
       resultPath.push(tmp);
       while(path[tmp]!='#')
       {
           resultPath.push(path[tmp]);
           tmp=path[tmp];
       }
       while(!resultPath.empty())
       {
           cout<<resultPath.top()<<" ";
           resultPath.pop();
       }
       cout<<endl;
       
}

void priorityQueen_exp()
{
    PriorityQueue<char, int> open;
    open.put('A',1);
    open.put('B',3);
    open.put('A',2);
    while(!open.empty())
    {
        open.get();
    }
}

#endif	/* DIJKSTRA_H */

