#include<iostream>
#include<set>
#include<fstream>
#include<windows.h>
using namespace std;
//�������� POJ 2676

class Grid
{
public:
    bool needFill; //�Ƿ���Ҫ�������
    int row; //�кţ���1��ʼ
    int col; //�кţ���1��ʼ
    set<int> candidate; //������������,dfsʱʹ��
    set<int> originCandidate; //���ڻָ�һ�����ӿ���������
    int val; //����ֵ

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
    cout << "����" << testCaseNum << "����������" << endl;
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
                fin.get(numChar); //���з��϶�Ҫ����  ��ʵֱ��ʹ��fin>>numChar�ͺã��Զ����Ի��з� 
                if ((int) numChar == 13 || (int) numChar == 10)
                    continue;
                else
                {
                    cout << numChar;
                    num = numChar - '0';
                    if (num == 0)//0����Ҫ����
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
            for (int i = 0; i < 9; i++)//��
                for (int j = 0; j < 9; j++)//��
                {
                    //��δ���ĸ���Ϊ�ӽǣ��������������ֵ��
                    if (sudoku[i][j].needFill)
                    {

                        for (int k = 0; k < 9; k++)
                        {
                            if (!sudoku[i][k].needFill)//��һ�еĿհ׸����ﲻ���� sudoku[i][k]
                                sudoku[i][j].candidate.erase(sudoku[i][k].val);
                            if (!sudoku[k][j].needFill) //��һ�еĿհ׸����ﲻ���� sudoku[k][j]
                                sudoku[i][j].candidate.erase(sudoku[k][j].val);
                        }
                        int gridRow = i / 3;
                        int gridCol = j / 3;
                        for (int m = gridRow * 3; m < gridRow * 3 + 3; m++) //��
                            for (int n = gridCol * 3; n < gridCol * 3 + 3; n++) //��
                                if (!sudoku[m][n].needFill)
                                    sudoku[i][j].candidate.erase(sudoku[m][n].val);
                        if (sudoku[i][j].candidate.size() == 1)//���ֻ��һ��·�����ߣ���ô��ֱ������Ͼͺ���
                        {
                            alreadyFillNum++;
                            sudoku[i][j].needFill = false;//����ĸ��ӿ��԰��������ĸ���Ҳ���ǽ��� 
                            sudoku[i][j].val = *sudoku[i][j].candidate.begin();
                            sudoku[i][j].candidate.clear();
                            cout << i << " " << j << ": " << sudoku[i][j].val << endl;
                            //						����صĸ����� ���������ϵ�����ɾ��
                            reErase = true;//�����������һ��������ô�������������ǰ�棬���˻�ֻ��һ��ѡ�� 

                        }
                    }
                }
            cout << endl;
        }

        for (int i = 0; i < 9; i++)//��
        {

            for (int j = 0; j < 9; j++)//��
            {
                if (sudoku[i][j].needFill)
                {
                    sudoku[i][j].originCandidate = sudoku[i][j].candidate;
                }
            }
        }



        cout << "Ŀǰ������ֵ:" << endl;
        for (int i = 0; i < 9; i++)//��
        {

            for (int j = 0; j < 9; j++)//��
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

        cout << "��Ҫ���" << needFillNum << "��" << endl;
        cout << "�Ѿ����" << alreadyFillNum << "��" << endl;

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
        //cout << "���� <" << i << "," << j << "> :" << test << endl;
        if (ifCanFill(i, j, test))
        {
            //cout << "���Է��� <" << i << "," << j << "> :" << test << endl;
            sudoku[i][j].val = test;
            sudoku[i][j].candidate.erase(test);
            Grid next = nextFillPos(i, j);
            if (next.val == -1)//û����һ��Ҫ������ֵ�ˣ��ҵ���һ���� 
            {
               // cout << "û����һ����" << endl;
                for (int i = 0; i < 9; i++)//��
                {

                    for (int j = 0; j < 9; j++)//��
                    {
                        cout << sudoku[i][j].val;


                    }
                    cout << endl;
                }
                cout << endl;

            } else
            {
               // cout << endl << "dfs ����<" << next.row << "," << next.col << ">" << endl;
                //Sleep(500);
                dfs(next.row, next.col);

            }

        } else
        {
            //cout<<"����ʧ��!"<<endl;
            sudoku[i][j].candidate.erase(test);
        }


    }
    //cout << "�ָ� <" << i << "," << j << "> " << endl;
    sudoku[i][j].candidate = sudoku[i][j].originCandidate;//��Ϊ��ÿ�ζ����candidate����գ�����������ӻ�����ֵ��ʼ������ʱ��Ҫ�ָ�����һ�����ӿ�������� 
}

//�ж�ĳ�������Ƿ�����ĳ������Ҫ�ж��������֮ǰ�Ѿ����˵����Լ�������Ӻ���Ĳ���Ҫ����� 
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
    for (int m = gridRow * 3; m < gridRow * 3 + 3; m++) //��
        for (int n = gridCol * 3; n < gridCol * 3 + 3; n++) //��
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

//����һ����Ҫ������ 
Grid nextFillPos(int i, int j)
{

    Grid result;
    for (int n = j + 1; n < 9; n++)//����i���ң���һ����Ҫ������ 
    {
        if (sudoku[i][n].needFill)
            return sudoku[i][n];
    }


    //�������û�У���i+1�� 
    for (int m = i + 1; m < 9; m++)//��
    {
        for (int n = 0; n < 9; n++)//��
        {
            if (sudoku[m][n].needFill)
                return sudoku[m][n];

        }
    }

    result.val = -1;
    return result;

}
