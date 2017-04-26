/* 
 * File:   SquareGrid.h
 * Author: Administrator
 *
 * Created on 2016年12月9日, 上午11:36
 */

#ifndef SQUAREGRID_H
#define	SQUAREGRID_H



struct SquareGrid
{
    typedef tuple<int, int> Location;
    static array<Location, 4> DIRS;

    int width, height;
    unordered_set<Location> walls;
    //来自标准库 Unordered sets are containers that store unique elements in no particular order, and which allow for fast retrieval of individual elements based on their value.

    SquareGrid(int width_, int height_)
    : width(width_), height(height_)
    {
        
    }

    inline bool in_bounds(Location id) const
    {
        int x, y;
        tie(x, y) = id;
        return 0 <= x && x < width && 0 <= y && y < height;
    }

    inline bool passable(Location id) const
    {
        return !walls.count(id); //如果在黑名单里没有你
    }

    vector<Location> neighbors(Location id) const
    {
        int x, y, dx, dy;
        tie(x, y) = id;//tie可以用来解压缩元组，使得x y获得了id这个tuple里的x值和y值
        vector<Location> results;

        for (auto dir : DIRS)
        {
            tie(dx, dy) = dir;
            Location next(x + dx, y + dy);
            if (in_bounds(next) && passable(next))
            {
                results.push_back(next);
            }
        }

        return results;
    }
};

 array<SquareGrid::Location, 4> SquareGrid::DIRS
{
     Location {1, 0}, 
     Location {0, -1}, 
     Location {-1, 0}, 
     Location {0, 1}
};
//template < class T, size_t N > class array; 因为DIRS是静态成员必须这样初始化，少了Location也不行

void add_rect(SquareGrid& grid, int x1, int y1, int x2, int y2)
{
    for (int x = x1; x < x2; ++x)
    {
        for (int y = y1; y < y2; ++y)
        {
            grid.walls.insert(SquareGrid::Location{x, y}); //向unordered_set里加入一个墙的坐标，注意一个墙的点使用了 field_width个#填充，所以#的个数与坐标点个数不一致
        }
    }
}

SquareGrid make_diagram1()
{
    SquareGrid grid(30, 15); //建立了一个宽为30，高为15的格子图
    add_rect(grid, 3, 3, 5, 12); //添加一片墙，墙的x范围是[3,5) y的范围是[3,12) 
    add_rect(grid, 13, 4, 15, 15);
    add_rect(grid, 21, 0, 23, 7);
    add_rect(grid, 23, 5, 26, 7);
    return grid;
}

struct GridWithWeights : SquareGrid
{
    unordered_set<Location> forests;

    GridWithWeights(int w, int h) : SquareGrid(w, h)
    {
    }

    double cost(Location from_node, Location to_node) const
    {
        return forests.count(to_node) ? 5 : 1;//如果是在森林里，移动花费5，否则只花费1
    }
};

GridWithWeights make_diagram4()
{
    GridWithWeights grid(10, 10);//建立了一个宽为10，高为10的格子图
    add_rect(grid, 1, 7, 4, 9);//添加一片墙，x的坐标为[1,4) y的坐标为[7,9) 
    typedef SquareGrid::Location L;
    grid.forests = unordered_set<SquareGrid::Location>{
        L
        {3, 4}, L
        {3, 5}, L
        {4, 1}, L
        {4, 2},
        L
        {4, 3}, L
        {4, 4}, L
        {4, 5}, L
        {4, 6},
        L
        {4, 7}, L
        {4, 8}, L
        {5, 1}, L
        {5, 2},
        L
        {5, 3}, L
        {5, 4}, L
        {5, 5}, L
        {5, 6},
        L
        {5, 7}, L
        {5, 8}, L
        {6, 2}, L
        {6, 3},
        L
        {6, 4}, L
        {6, 5}, L
        {6, 6}, L
        {6, 7},
        L
        {7, 3}, L
        {7, 4}, L
        {7, 5}
    };
    return grid;
}

// This outputs a grid. Pass in a distances map if you want to print
// the distances, or pass in a point_to map if you want to print
// arrows that point to the parent location, or pass in a path vector
// if you want to draw the path. 这个设计真的挺好的，不然我会写上n个函数，其实它们都是画格子

template<class Graph>
void draw_grid(const Graph& graph, int field_width,
        unordered_map<typename Graph::Location, double>* distances = nullptr,
        unordered_map<typename Graph::Location, typename Graph::Location>* point_to = nullptr,
        vector<typename Graph::Location>* path = nullptr)
{
    for (int y = 0; y != graph.height; ++y)
    {
        for (int x = 0; x != graph.width; ++x)
        {
            typename Graph::Location id(x, y); //写成typename Graph::Location id {x, y};也行
            std::cout << std::left << std::setw(field_width); //输出左对齐，输出宽度为field_width
            if (graph.walls.count(id))//如果(x,y)在墙的范围里,那就输出field_width个#
            {
                std::cout << string(field_width, '#');
            } 
            else if (point_to != nullptr && point_to->count(id))//指向每个点的前驱
            {
                int x2, y2;
                tie(x2, y2) = (*point_to)[id]; //获得了x y的前驱 x2 y2
                // TODO: how do I get setw to work with utf8?
                if (x2 == x + 1)//
                {
                    std::cout << "→";
                } else if (x2 == x - 1)
                {
                    std::cout << "←";
                } else if (y2 == y + 1)
                {
                    std::cout << "↓";
                } else if (y2 == y - 1)
                {
                    std::cout << "↑";
                } else//表示起点
                {
                    std::cout << "* ";
                }
            } 
            else if (distances != nullptr && distances->count(id))
            {
                std::cout << (*distances)[id];
            } 
            else if (path != nullptr && find(path->begin(), path->end(), id) != path->end())//如果当前的坐标在path的向量里就输出@
            {
                std::cout << '@';
            }
            else//如果我既不输出距离，也不输出前驱，也不输出路径，就只输出点
            {
                std::cout << '.'; //纯正的格子用点表示
            }
        }
        std::cout << std::endl;
    }
}

//画格子图实验

void draw_grid_exp()
{
    SquareGrid grid = make_diagram1();
    draw_grid(grid, 2);
}
#endif	/* SQUAREGRID_H */

