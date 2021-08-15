#include <iostream>
#include <cstdio>
using namespace std;
class LinearEquations
{
public:
    double eq[100][101] = {0.00};
    double map_eq[100][101] = {0.00};
    int to[1000] = {0};
    int back[1000] = {0};
    int num = 0;
    LinearEquations() {}
    bool get_equation(string str, int pos)
    {
        int len = str.length();
        int _pos = 0; //"="的位置
        for (int i = 0; i < len; ++i)
            if (str[i] == '=')
            {
                _pos = i;
                break;
            }
        if (_pos == 0)
            return 0;
        int i = 0;
        bool is_add = true;
        while (i < _pos)
        {
            if (str[i] <= '9' && str[i] >= '0')
            {
                double tmp = 0;
                while (i < _pos && str[i] <= '9' && str[i] >= '0')
                {
                    tmp *= 10;
                    tmp += (str[i] - '0');
                    ++i;
                }
                if (i < _pos && str[i] == '.')
                {
                    ++i;
                    double index = 0.1;
                    while (i < _pos && str[i] <= '9' && str[i] >= '0')
                    {
                        tmp += (str[i] - '0') * index;
                        ++i;
                        index /= 10;
                    }
                }
                if (i < _pos && str[i] == 'x')
                {
                    ++i;
                    if (i < _pos && str[i] == '_')
                    {
                        ++i;
                        if (i < _pos && str[i] <= '9' && str[i] >= '0')
                        {

                            int _tmp = str[i] - '0';
                            ++i;
                            while (i < _pos && str[i] <= '9' && str[i] >= '0')
                            {
                                _tmp *= 10;
                                _tmp += str[i] - '0';
                                ++i;
                            }
                            if (is_add)
                                eq[pos][_tmp] += tmp;
                            else
                                eq[pos][_tmp] += -1 * tmp;
                        }
                        else
                            return 0;
                    }
                }
                else if (i < _pos && str[i] != '+' && str[i] != '-')
                    return 0;
                else
                {
                    if (is_add)
                        eq[pos][0] += tmp;
                    else
                        eq[pos][0] -= tmp;
                    ++i;
                }
            }
            else if (str[i] == '+')
            {
                is_add = true;
                ++i;
                if (i == _pos || ((str[i] > '9' || str[i] < '0') && str[i] != 'x'))
                    return 0;
            }
            else if (str[i] == '-')
            {
                is_add = false;
                ++i;
                if (i == _pos || ((str[i] > '9' || str[i] < '0') && str[i] != 'x'))
                    return 0;
            }
            else if (str[i] == 'x')
            {
                ++i;
                if (i < _pos && str[i] == '_')
                {
                    ++i;
                    if (i < _pos && str[i] <= '9' && str[i] >= '0')
                    {
                        int _tmp = str[i] - '0';
                        ++i;
                        while (i < _pos && str[i] <= '9' && str[i] >= '0')
                        {
                            _tmp *= 10;
                            _tmp += str[i] - '0';
                            ++i;
                        }
                        if (is_add)
                            eq[pos][_tmp] += 1;
                        else
                            eq[pos][_tmp] += -1 * 1;
                    }
                    else
                        return 0;
                }
                else
                {
                    if (is_add)
                        eq[pos][1] += 1;
                    else
                        eq[pos][1] += -1 * 1;
                }
            }
            else
                return 0;
        }
        i = _pos + 1;
        is_add = true;
        //等号右边
        while (i < len)
        {
            if (str[i] <= '9' && str[i] >= '0')
            {
                double tmp = 0;
                while (i < len && str[i] <= '9' && str[i] >= '0')
                {
                    tmp *= 10;
                    tmp += (str[i] - '0');
                    ++i;
                }
                if (i < len && str[i] == '.')
                {
                    ++i;
                    double index = 0.1;
                    while (i < len && str[i] <= '9' && str[i] >= '0')
                    {
                        tmp += (str[i] - '0') * index;
                        ++i;
                        index /= 10;
                    }
                }
                if (i < len && str[i] == 'x')
                {
                    ++i;
                    if (i < len && str[i] == '_')
                    {
                        ++i;
                        if (i < len && str[i] <= '9' && str[i] >= '0')
                        {

                            int _tmp = str[i] - '0';
                            ++i;
                            while (i < len && str[i] <= '9' && str[i] >= '0')
                            {
                                _tmp *= 10;
                                _tmp += str[i] - '0';
                                ++i;
                            }
                            if (is_add)
                                eq[pos][_tmp] -= tmp;
                            else
                                eq[pos][_tmp] -= -1 * tmp;
                        }
                        else
                            return 0;
                    }
                    else
                    {
                        /*if (is_add)
                            pol[1] += tmp;
                        else
                            pol[1] += -1 * tmp;*/
                    }
                }
                else if (i < len && str[i] != '+' && str[i] != '-')
                    return 0;
                else
                {
                    if (is_add)
                        eq[pos][0] -= tmp;
                    else
                        eq[pos][0] += tmp;
                    ++i;
                }
            }
            else if (str[i] == '+')
            {
                is_add = true;
                ++i;
                if (i == len || ((str[i] > '9' || str[i] < '0') && str[i] != 'x'))
                    return 0;
            }
            else if (str[i] == '-')
            {
                is_add = false;
                ++i;
                if (i == len || ((str[i] > '9' || str[i] < '0') && str[i] != 'x'))
                    return 0;
            }
            else if (str[i] == 'x')
            {
                ++i;
                if (i < len && str[i] == '_')
                {
                    ++i;
                    if (i < len && str[i] <= '9' && str[i] >= '0')
                    {
                        int _tmp = str[i] - '0';
                        ++i;
                        while (i < len && str[i] <= '9' && str[i] >= '0')
                        {
                            _tmp *= 10;
                            _tmp += str[i] - '0';
                            ++i;
                        }
                        if (is_add)
                            eq[pos][_tmp] -= 1;
                        else
                            eq[pos][_tmp] -= -1 * 1;
                    }
                    else
                        return 0;
                }
                else
                {
                    if (is_add)
                        eq[pos][1] -= 1;
                    else
                        eq[pos][1] -= -1 * 1;
                }
            }
            else
                return 0;
        }
        eq[pos][100] -= eq[pos][0];

        return true;
    }
    bool solve(int pos, int cur)
    {
        int row = 1, col = 1;
        for (; row <= pos && col <= cur; ++row, ++col)
        {
            int max_row = row; //找绝对值最大的行
            for (int i = row; i <= pos; ++i)
                if (fabs(map_eq[i][col]) > fabs(map_eq[max_row][col]))
                    max_row = i;
            if (max_row != row)
                _swap(row, max_row);
            if (fabs(map_eq[row][col]) < 1e-5) //剩下的全是0
            {
                --row;
                continue;
            }
            for (int i = row + 1; i <= pos; ++i) //一行一行减
            {
                double tmp = map_eq[i][col] / map_eq[row][col];
                for (int j = col; j <= cur + 1; ++j)

                    map_eq[i][j] -= tmp * map_eq[row][j];
            }
        }
        //检查(0,0,...,0,a)
        for (int i = row + 1; i <= pos; ++i)
            if (fabs(map_eq[i][cur + 1]) > 1e-5)
                return false;

        //检查(0,0,...,0)
        if (row <= cur)
            return false;
        //求解
        double ans[100] = {0};
        for (int i = cur; i >= 1; --i)
        {
            double tmp = map_eq[i][cur + 1];
            for (int j = i + 1; j <= cur; ++j)
                tmp -= map_eq[i][j] * ans[j];
            ans[i] = tmp / map_eq[i][i];
        }
        //输出
        for (int i = 1; i < 100; ++i)
        {
            if (to[i] != 0)
            {
                if (fabs(ans[to[i]]) < 1e-5)
                {
                    printf("0.0000");
                    continue;
                }
                string a = to_string(ans[to[i]]);
                int i = 0;
                while (a[i] != '.')
                {
                    cout << a[i];
                    ++i;
                }
                cout << ".";
                for (int j = 1; j <= 4; ++j)
                    cout << a[i + j];
                cout << " ";
            }
        }
        return true;
    }
    void print(int cur)
    {
        for (int i = 0; i < 10; ++i)
        {
            for (int j = 0; j < 10; ++j)
                cout << eq[i][j] << ' ';
            cout << eq[i][100];
            cout << endl;
        }
        cout << "====\n";
        for (int i = 0; i < 10; ++i)
        {
            for (int j = 0; j < 10; ++j)
                cout << map_eq[i][j] << ' ';
            cout << eq[i][cur + 1];
            cout << endl;
        }
    }
    int map()
    {
        int cur = 0;
        for (int i = 1; i < 100; ++i)
        {
            for (int j = 1; j < 100; ++j)
            {
                if (fabs(eq[i][j]) > 1e-5)
                {
                    if (to[j] == 0) //j没有映射过
                    {
                        to[j] = ++cur;
                        back[cur] = j; //映射到cur
                        map_eq[i][cur] = eq[i][j];
                    }
                    else //j映射过

                        map_eq[i][to[j]] = eq[i][j];
                }
            }
        }
        for (int i = 1; i < 100; ++i)

            map_eq[i][cur + 1] = eq[i][100];

        return cur; //返回未知数数量
    }
    void _swap(int i, int j) //交换i,j两行
    {
        double tmp[100] = {0};
        for (int k = 0; k < 100; ++k)
            tmp[k] = map_eq[j][k];
        for (int k = 0; k < 100; ++k)
            map_eq[j][k] = map_eq[i][k];
        for (int k = 0; k < 100; ++k)
            map_eq[i][k] = tmp[k];
    }
};