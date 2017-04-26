#include<iostream>
#include<set>
#include<fstream>
#include<windows.h>
using namespace std;
//数独问题 POJ 2676

class Grid
{
public:
    bool needFill; //是否需要填充数字
    int row; //行号，从1开始
    int col; //列号，从1开始
    set<int> candidate; //允许填充的数字,dfs时使用
    set<int> originCandidate; //用于恢复一个格子可以填充的数
    int val; //填充的值

};

Grid sudoku[9][9];
void dfs(int i, int j);
bool ifCanFill(int i, int j, int test);
Grid nextFillPos(int i, int j);

int main()
{
    ifstream fin("Sudoku2.txt");
    int testCaseNum;
    fin>>testCaseNum;
    cout << "共有" << testCaseNum << "个测试样本" << endl;
    while (testCaseNum > 0)
    {

        char numChar;
        int num;
        int needFillNum = 0;
        int alreadyFillNum = 0;
        for (int i = 0; i < 9; i++)
        {
            int j = 0;
            while (j < 9)
            {
                fin.get(numChar); //换行符肯定要忽略  其实直接使用fin>>numChar就好，自动忽略换行符 
                if ((int) numChar == 13 || (int) numChar == 10)
                    continue;
                else
                {
                    cout << numChar;
                    num = numChar - '0';
                    if (num == 0)//0是需要填充的
                    {
                        needFillNum++;
                        sudoku[i][j].row = i;
                        sudoku[i][j].col = j;
                        sudoku[i][j].needFill = true;
                        sudoku[i][j].candidate.clear();
                        for (int k = 1; k <= 9; k++)
                            sudoku[i][j].candidate.insert(k);
                        sudoku[i][j].val = 0;
                    } else
                    {
                        sudoku[i][j].row = i;
                        sudoku[i][j].col = j;
                        sudoku[i][j].needFill = false;
                        sudoku[i][j].val = num;
                        sudoku[i][j].candidate.clear();
                    }

                    j++;

                }

            }
            cout << endl;
        }

        bool reErase = true;
        while (reErase)
        {
            reErase = false;
            for (int i = 0; i < 9; i++)//行
                for (int j = 0; j < 9; j++)//列
                {
                    //以未填充的格子为视角，计算出可以填充的值来
                    if (sudoku[i][j].needFill)
                    {

                        for (int k = 0; k < 9; k++)
                        {
                            if (!sudoku[i][k].needFill)//这一行的空白格子里不许有 sudoku[i][k]
                                sudoku[i][j].candidate.erase(sudoku[i][k].val);
                            if (!sudoku[k][j].needFill) //这一列的空白格子里不许有 sudoku[k][j]
                                sudoku[i][j].candidate.erase(sudoku[k][j].val);
                        }
                        int gridRow = i / 3;
                        int gridCol = j / 3;
                        for (int m = gridRow * 3; m < gridRow * 3 + 3; m++) //行
                            for (int n = gridCol * 3; n < gridCol * 3 + 3; n++) //列
                                if (!sudoku[m][n].needFill)
                                    sudoku[i][j].candidate.erase(sudoku[m][n].val);
                        if (sudoku[i][j].candidate.size() == 1)//如果只有一条路可以走，那么就直接填充上就好了
                        {
                            alreadyFillNum++;
                            sudoku[i][j].needFill = false;//后面的格子可以把这个新填的格子也考虑进入 
                            sudoku[i][j].val = *sudoku[i][j].candidate.begin();
                            sudoku[i][j].candidate.clear();
                            cout << i << " " << j << ": " << sudoku[i][j].val << endl;
                            //						在相关的格子里 把我新填上的数给删掉
                            reErase = true;//如果新填上了一个数，那么可能在这个格子前面，有人会只有一个选项 

                        }
                    }
                }
            cout << endl;
        }

        for (int i = 0; i < 9; i++)//行
        {

            for (int j = 0; j < 9; j++)//列
            {
                if (sudoku[i][j].needFill)
                {
                    sudoku[i][j].originCandidate = sudoku[i][j].candidate;
                }
            }
        }



        cout << "目前能填充的值:" << endl;
        for (int i = 0; i < 9; i++)//行
        {

            for (int j = 0; j < 9; j++)//列
            {
                if (sudoku[i][j].needFill)
                {
                    cout << " <" << i << "," << j << "> :";
                    for (set<int>::iterator iter = sudoku[i][j].candidate.begin(); iter != sudoku[i][j].candidate.end(); iter++)
                        cout << *iter << " ";
                    cout << endl;
                }


            }

        }

        cout << "需要填充" << needFillNum << "个" << endl;
        cout << "已经填充" << alreadyFillNum << "个" << endl;

        if (needFillNum > alreadyFillNum)
        {
            Grid first = nextFillPos(0, -1);
            dfs(first.row, first.col);

        }


        testCaseNum--;


    }

}

void dfs(int i, int j)
{

    while (!sudoku[i][j].candidate.empty())
    {
        int test = *sudoku[i][j].candidate.begin();
        //cout << "尝试 <" << i << "," << j << "> :" << test << endl;
        if (ifCanFill(i, j, test))
        {
            //cout << "可以放置 <" << i << "," << j << "> :" << test << endl;
            sudoku[i][j].val = test;
            sudoku[i][j].candidate.erase(test);
            Grid next = nextFillPos(i, j);
            if (next.val == -1)//没有下一个要搜索的值了，找到了一个解 
            {
               // cout << "没有下一个！" << endl;
                for (int i = 0; i < 9; i++)//行
                {

                    for (int j = 0; j < 9; j++)//列
                    {
                        cout << sudoku[i][j].val;


                    }
                    cout << endl;
                }
                cout << endl;

            } else
            {
               // cout << endl << "dfs 搜索<" << next.row << "," << next.col << ">" << endl;
                //Sleep(500);
                dfs(next.row, next.col);

            }

        } else
        {
            //cout<<"放置失败!"<<endl;
            sudoku[i][j].candidate.erase(test);
        }


    }
    //cout << "恢复 <" << i << "," << j << "> " << endl;
    sudoku[i][j].candidate = sudoku[i][j].originCandidate;//因为我每次都会把candidate都清空，当给这个格子换个新值开始搜索的时候，要恢复它下一个格子可以填的数 
}

//判断某个格子是否能填某个数，要判断这个格子之前已经填了的数以及这个格子后面的不需要填的数 
bool ifCanFill(int i, int j, int test)
{
    for (int k = 0; k < 9; k++)
    {
        if (sudoku[i][k].needFill)
        {
            if (k < j && sudoku[i][k].val == test)
            {
                //cout << " <" << i << "," << k << "> " << endl;
                return false;
            }
        } else
            if (sudoku[i][k].val == test)
        {
           // cout << " <" << i << "," << k << "> " << endl;
            return false;
        }

        if (sudoku[k][j].needFill)
        {
            if (k < i && sudoku[k][j].val == test)
            {
               // cout << " <" << k << "," << j << "> " << endl;
                return false;
            }
        } else
            if (sudoku[k][j].val == test)
        {
            //cout << " <" << k << "," << j << "> " << endl;
            return false;
        }

    }
    int gridRow = i / 3;
    int gridCol = j / 3;
    for (int m = gridRow * 3; m < gridRow * 3 + 3; m++) //行
        for (int n = gridCol * 3; n < gridCol * 3 + 3; n++) //列
        {
            if (sudoku[m][n].needFill)
            {
                if ((m < i || (m==i&&n<j)) && sudoku[m][n].val == test)
                {
                   // cout << " <" << m << "," << n << "> " << endl;
                    return false;
                }

            } else
                if (sudoku[m][n].val == test)
            {
                //cout << " <" << m << "," << n << "> " << endl;
                return false;
            }

        }
    return true;

}

//找下一个需要填充的数 
Grid nextFillPos(int i, int j)
{

    Grid result;
    for (int n = j + 1; n < 9; n++)//先在i行找，下一个需要填充的数 
    {
        if (sudoku[i][n].needFill)
            return sudoku[i][n];
    }


    //如果本行没有，找i+1行 
    for (int m = i + 1; m < 9; m++)//行
    {
        for (int n = 0; n < 9; n++)//列
        {
            if (sudoku[m][n].needFill)
                return sudoku[m][n];

        }
    }

    result.val = -1;
    return result;

}
