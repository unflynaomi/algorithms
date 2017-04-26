/* 
 * File:   bfs.h
 * Author: Administrator
 *
 * Created on 2016年12月12日, 上午10:28
 */

#ifndef BFS_H
#define	BFS_H

#include"Util.h"
#include"SimpleGraph.h"
#include"SquareGrid.h"




//普通图的指定起点的到其它所有结点的bfs
template<typename Graph>
void breadth_first_search_all(Graph graph, typename Graph::Location start)
{
    typedef typename Graph::Location Location;
    queue<Location> frontier;
    frontier.push(start);

    unordered_set<Location> visited;
    visited.insert(start);

    while (!frontier.empty())
    {
        auto current = frontier.front();
        frontier.pop();

        std::cout << "Visiting " << current << std::endl;
        for (auto next : graph.neighbors(current))
        {
            if (!visited.count(next))
            {
                frontier.push(next);
                visited.insert(next);
            }
        }
    }
}

//grid 指定起点和终点的bfs
template<typename Graph>
unordered_map<typename Graph::Location, typename Graph::Location>
grid_breadth_first_search_dest(const Graph& graph,
        typename Graph::Location start,
        typename Graph::Location goal)
{
    typedef typename Graph::Location Location;
    queue<Location> frontier;
    frontier.push(start);

    unordered_map<Location, Location> came_from;
    came_from[start] = start;

    while (!frontier.empty())
    {
        auto current = frontier.front();
        frontier.pop();

        if (current == goal)
        {
            break;
        }

        for (auto next : graph.neighbors(current))
        {
            if (!came_from.count(next))
            {
                frontier.push(next);
                came_from[next] = current;
            }
        }
    }
    return came_from;
}

//grid的指定起点的到其它所有结点的bfs
template<typename Graph>
unordered_map<typename Graph::Location, typename Graph::Location>
grid_breadth_first_search_all(Graph graph, typename Graph::Location start)
{
	typedef typename Graph::Location Location;
	queue<Location> frontier;
	frontier.push(start);

	unordered_map<Location, Location> came_from;
	came_from[start] = start;//came_from里键是某个点 值是它的访问前驱

	while (!frontier.empty())
	{
		auto current = frontier.front();
		frontier.pop();

		for (auto next : graph.neighbors(current))//这还是c++吗，不可思议
		{
			if (!came_from.count(next))//如果没有访问过
			{
				frontier.push(next);
				came_from[next] = current;
			}
		}
	}
	return came_from;
}

//使用示例,在main函数里直接调用
//普通图bfs使用示例
void breadth_first_search_all_exp()
{
    breadth_first_search_all(example_graph, 'A');
}

//格子图bfs使用示例
void grid_breadth_first_search_dest_exp()
{
    SquareGrid grid = make_diagram1();
    auto parents = grid_breadth_first_search_dest(grid, SquareGrid::Location{8, 7}, SquareGrid::Location{17, 2});
    draw_grid(grid, 2, nullptr, &parents);
}
//格子图bfs使用示例
void grid_breadth_first_search_all_exp()
{
    SquareGrid grid = make_diagram1();
    draw_grid(grid, 2);
    auto parents = grid_breadth_first_search_all(grid, std::make_tuple(7, 8));
    //以上这种语义是C++11自动类型推算，自动算出parents是什么类型 是unordered_map类型 (7,8)是起点
    draw_grid(grid, 2, nullptr, &parents); //parents就是came_from  unordered_map类型
    
}
#endif	/* BFS_H */

