#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int arr[4][4] = {0};
bool gameover = false;

void output()
{
    for (int i = 0; i < 4; ++i)
    {
        cout << "+----+----+----+----+\n";

        for (int j = 0; j < 4; ++j)
        {
            cout << "|";

            if (arr[i][j] < 10)
                cout << "   ";
            else if (arr[i][j] < 100)
                cout << "  ";
            else if (arr[i][j] < 1000)
                cout << " ";

            arr[i][j] == 0 ? cout << ' ' : cout << arr[i][j];
        }
        cout << "|\n";
    }
    cout << "+----+----+----+----+\n";
}
// 回傳是否有改變
bool move(int way)
{
    bool changed = false;
    for (int i = 0; i < 4; ++i)
    {
        int temp[4] = {0};
        int t = 0;
        for (int j = 0; j < 4; ++j)
        {
            int r = i, c = j;
            if (way == 0)
                r = j, c = i; // 上
            else if (way == 1)
                r = i, c = j; // 左
            else if (way == 2)
                r = 3 - j, c = i; // 下
            else
                r = i, c = 3 - j; // 右
            if (arr[r][c] != 0)
                temp[t++] = arr[r][c];
        }
        int k = 0;
        for (int j = 0; j < t; ++j)
        {
            if (j + 1 < t && temp[j] == temp[j + 1])
            {
                temp[k++] = temp[j] * 2;
                ++j;
                changed = true;
            }
            else
            {
                temp[k++] = temp[j];
            }
        }
        while (k < 4)
            temp[k++] = 0;

        for (int j = 0; j < 4; ++j)
        {
            int r = i, c = j;
            if (way == 0)
                r = j, c = i;
            else if (way == 1)
                r = i, c = j;
            else if (way == 2)
                r = 3 - j, c = i;
            else
                r = i, c = 3 - j;
            if (arr[r][c] != temp[j])
            {
                arr[r][c] = temp[j];
                changed = true;
            }
        }
    }
    return changed;
}

void randNum()
{
    int r, c;
    do
    {
        r = rand() % 4;
        c = rand() % 4;
    } while (arr[r][c] != 0);
    arr[r][c] = (rand() % 100 < 90) ? 2 : 4;
}

bool canMove()
{
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (arr[i][j] == 0)
                return true;

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 3; ++j)
            if (arr[i][j] == arr[i][j + 1] || arr[j][i] == arr[j + 1][i])
                return true;
    return false;
}

int main()
{
    srand(time(NULL));
    randNum();
    randNum();

    while (!gameover)
    {
        output();
        cout << "請輸入 W/A/S/D：";
        char way;
        cin >> way;
        way = toupper(way);
        bool moved = false;
        switch (way)
        {
        case 'W':
            moved = move(0);
            break;
        case 'A':
            moved = move(1);
            break;
        case 'S':
            moved = move(2);
            break;
        case 'D':
            moved = move(3);
            break;
        default:
            cout << "請輸入 W/A/S/D\n";
            continue;
        }
        if (moved)
            randNum();

        if (!canMove())
        {
            output();
            cout << "GameOver\n";
            gameover = true;
        }
    }
    return 0;
}
