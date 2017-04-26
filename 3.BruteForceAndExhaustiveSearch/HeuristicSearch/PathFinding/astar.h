/* 
 * File:   astar.h
 * Author: Administrator
 *
 * Created on 2016年12月12日, 上午10:28
 */

#ifndef ASTAR_H
#define	ASTAR_H

#include"Util.h"
#include"SimpleGraph.h"
#include"SquareGrid.h"
#include"math.h"

inline double heuristic(SquareGrid::Location a, SquareGrid::Location b)
{
    int x1, y1, x2, y2;
    tie(x1, y1) = a;
    tie(x2, y2) = b;
    return abs(x1 - x2) + abs(y1 - y2);//曼哈顿距离
    //sqrt((xPoint-xDest)*(xPoint-xDest)+(yPoint-yDest)*(yPoint-yDest));也可以用直线距离
}

template<typename Graph>
void a_star_search
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
    cost_so_far[start] = 0;//各个点距离起点的距离

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
            if (!cost_so_far.count(next) || new_cost < cost_so_far[next])//如果经由新的current，找到了到达next的新路径，比原来的到达next的好
            {
                cost_so_far[next] = new_cost;
                double priority = new_cost + heuristic(next, goal);
                frontier.put(next, priority);
                came_from[next] = current;
            }
        }
    }
}

//直接在main函数里调用的例子，在格子图里使用A*来搜索从起点到终点的最短路径
void grid_a_star_exp()
{
    GridWithWeights grid = make_diagram4();
    SquareGrid::Location start{1, 4};
    SquareGrid::Location goal{8, 5};
    unordered_map<SquareGrid::Location, SquareGrid::Location> came_from;
    unordered_map<SquareGrid::Location, double> cost_so_far;
    a_star_search(grid, start, goal, came_from, cost_so_far);
    draw_grid(grid, 2, nullptr, &came_from);
    std::cout << std::endl;
    draw_grid(grid, 3, &cost_so_far, nullptr);
    std::cout << std::endl;
    vector<SquareGrid::Location> path = reconstruct_path(start, goal, came_from);
    draw_grid(grid, 3, nullptr, nullptr, &path);
}

#endif	/* ASTAR_H */

