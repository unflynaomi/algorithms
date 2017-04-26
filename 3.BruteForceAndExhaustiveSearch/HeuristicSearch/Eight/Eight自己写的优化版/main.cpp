//启发式搜索八数码难题
#include<iostream>
#include<utility>
#include<queue>
#include<vector>
#include<set>
#include<math.h>
using namespace std;



//char target[3][3] = {{'1','2','3'},{'8','0','4'},{'7','6','5'}};//需要5步
//char target[3][3] = {
//    {'8', '1', '5'},
//    {'7', '3', '6'},
//    {'4', '0', '2'}
//};//31步
char target[3][3] = {{'1','2','3'},{'8','0','4'},{'7','6','5'}};//需要18步
//char target[3][3] = {
//    {'0', '1', '2'},
//    {'3', '4', '5'},
//    {'6', '7', '8'}
//}; //无解
int targetReverseNum = 0; //目标的逆序数个数和

void printRoute(int index);

class Eight
{
public:
    int parent; //记录父结点在closed集中的索引
    char state[3][3];
    //	char parent[3][3] ;//扩展它的结点的数码情况 没有必要存父结点，有了moveType可以推算
    int moveType; //左 1 右 10 上2 下 20 ，且子结点的行动方式，不许和我相反 空格的移动方式
    int g; //深度，可以算出从初始到目标需要几步
    int h; //启发函数值，当前状态不在目标位置上的数码总数
    int spaceRow; //空格所在的行号,省的去搜
    int spaceCol; //空格所在的列号

    void setHAndSpace()//当前状态不在目标位置上的数码总数，顺便设置空格所在的行号和列号
    {
        h = 0;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
            {
                if (state[i][j] != '0')
                {
                    if (state[i][j] != target[i][j])
                        h++;
                } else//第一个结点还是要靠查找发现空格的位子
                {
                    spaceRow = i;
                    spaceCol = j;
                }
            }
    }

    void setState(char(*p)[3])
    {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                state[i][j] = p[i][j];
    }

    void printNode()
    {
        if (moveType == 1)
            cout << "左:\n";
        else if (moveType == 2)
            cout << "上:\n";
        else if (moveType == 10)
            cout << "右:\n";
        else if (moveType == 20)
            cout << "下:\n";
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
                cout << state[i][j] << " ";
            cout << endl;
        }
        cout << "g:" << g << " h:" << h << " hash:" << toInt() << endl;
        cout << endl;
    }

    bool isTarget()//是否已经到达目标状态
    {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
            {
                if (state[i][j] != target[i][j])
                    return false;
            }
        return true;
    }

    //无需写ifCanUp ifCanDown ifCanLeft ifCanRight 用参数的方式省时省力

    bool ifCanMove(int rowMove, int colMove, int moveTypeP)
    //判断在我的state状态下，空格能否按照参数给的动作移动
    //我子结点的移动动作，不允许和我的动作相反
    {
        if (spaceRow + rowMove < 0 || spaceRow + rowMove > 2 || spaceCol + colMove < 0 || spaceCol + colMove > 2 || (moveType + moveTypeP) % 11 == 0) //左 1 右 10 上2 下 20
            return false;
        else
            return true;
    }

    //这个和ifCanMove不能合并，因为操作的对象不同

    void moveSpace(int rowMove, int colMove, int moveTypeP)
    {
        char temp = state[spaceRow + rowMove][spaceCol + colMove];
        state[spaceRow][spaceCol] = temp;
        state[spaceRow + rowMove][spaceCol + colMove] = '0';
        moveType = moveTypeP;
    }



    //用一种很直接地方式转成整数，直接就是这么直着写写下来 

    int toInt()
    {

        int hash = 0;
        for (int i = 0; i < 3; i++)
            hash += (state[0][i] - '0')*100000000 / pow(10, i);
        for (int i = 0; i < 3; i++)
            hash += (state[1][i] - '0')*100000 / pow(10, i);
        for (int i = 0; i < 3; i++)
            hash += (state[2][i] - '0')*100 / pow(10, i);
        return hash;


    }

    //判断从当前的状态，有没有希望到达目标，判断和目标的逆序数个数和的奇偶性一不一样，用于剪枝

    bool canReachTarget()
    {
        int arrayInt[9];
        int index = 0;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                arrayInt[index++] = state[i][j] - '0';
        int reverseNum = 0;
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (arrayInt[j] > arrayInt[i] && arrayInt[i] != 0)//除了0之外的每个数字的逆序数之和
                    reverseNum++;
            }
        }
        return ((targetReverseNum % 2 == 0 && reverseNum % 2 == 0) || (targetReverseNum % 2 == 1 && reverseNum % 2 == 1));

    }



};

//判断优先队列中Eight的优先级

class mycomparison
{
public:

    bool operator()(const Eight& first, const Eight& second) const//降序排列，返回first>second
    {
        if ((first.g + first.h) != (second.g + second.h))//先按估值函数排序
            return first.g + first.h > second.g + second.h;
        else if (first.g != second.g)//再按层次排序，浅层优先扩展
            return first.g > second.g;
        else
            return first.moveType > second.moveType;//如果估值函数一样，层次也一样，那么按照先扩展左移动的结点的顺序排列

    }
};
//如果这个函数返回true,那么认为第一个元素比第二个元素小，因为优先队列始终都取最大值，所以函数返回true时，取第二个元素

vector<Eight> closed;

int main()
{
    int spaceMoveRow[4] = {0, -1, 0, 1}; //空格移动指南 左 行不动 上 行减一 右 行不动 下 行加一
    int spaceMoveCol[4] = {-1, 0, 1, 0}; //空格移动指南 左 列减一 上 列不动 右 列加一 下 列不动
    int spaceMoveType[4] = {1, 2, 10, 20}; //左1上2 右10下20 要形成递增的序列，能一下判断 按照左上右下的顺序扩展结点 又要能快速识别 成对的 操作
    //左 1 右 10 上2 下 20



//    	char startp[3][3]= {{'2','8','3'},{'1','6','4'},{'7','0','5'}};//需要5步
//        char startp[3][3] = {
//            {'2', '6', '4'},
//            {'1', '3', '7'},
//            {'0', '5', '8'}
//        };//需要31步
     char startp[3][3]= {{'2','1','6'},{'4','0','8'},{'7','5','3'}};//需要18步
//    char startp[3][3] = {
//        {'3', '7', '2'},
//        {'8', '1', '5'},
//        {'4', '6', '0'}
//    }; //无解

    int targetInt[9];
    int index = 0;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            targetInt[index++] = target[i][j] - '0';
    targetReverseNum = 0;//全局变量
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (targetInt[j] > targetInt[i] && targetInt[i] != 0)//除了0之外的每个数字的逆序数之和
                targetReverseNum++;
        }
    }
    cout << "目标的逆序数个数和为:" << targetReverseNum << endl;

    Eight start;
    start.setState(startp);
    if (start.canReachTarget())
    {
        start.moveType = 0;
        start.g = 0;
        start.setHAndSpace();
        start.parent = -1;

        priority_queue<Eight, vector<Eight>,mycomparison> pQueue;
        pQueue.push(start);
        set<int> hash; //用来判断当前的结点，需不需要扩展，若已经扩展过，则无需扩展

        int index = -1; //已经扩展的结点数目，就是closed数组里的位置索引，用来设置每个结点的parent标记
        while (!pQueue.empty())
        {
            Eight top = pQueue.top();
            pQueue.pop();
            //cout<<"此次扩展的结点为:"<<endl;
            //top.printNode();     
            //cout<<endl;

            closed.push_back(top);
            index++;
            if (top.isTarget())
            {
                cout << "用了" << top.g << "步到达了目标结点" << endl;
                printRoute(index);
                break;
            } else
            {
                for (int i = 0; i < 4; i++) //按照左上右下的空格移动顺序扩展结点
                {
                    if (top.ifCanMove(spaceMoveRow[i], spaceMoveCol[i], spaceMoveType[i]))//如果这个动作是可以执行的
                    {
                        Eight newStep = top; //用父结点初始化自己                        
                        newStep.moveSpace(spaceMoveRow[i], spaceMoveCol[i], spaceMoveType[i]);
                        if (newStep.canReachTarget() && hash.count(newStep.toInt()) == 0)
                            //如果未曾产生过而且可能达到目标结点，才放入Open集中   
                        {
                            newStep.parent = index;
                            newStep.g++;
                            newStep.setHAndSpace();
                            //newStep.printNode();   
                            hash.insert(newStep.toInt());
                            pQueue.push(newStep);
                        } else
                            continue;

                    }
                }
                //cout<<endl;


            }
        }
    } else
        cout << "此起点无法到达终点!" << endl;


}

void printRoute(int index)
{
    if (index != 0)
    {
        printRoute(closed[index].parent);
        closed[index].printNode();
    } else
        closed[0].printNode();
}