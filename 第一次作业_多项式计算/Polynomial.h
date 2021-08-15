#include <iostream>
#include <cstdio>
using namespace std;

class polynomial
{
public:
    double pol[1000];
    double d[1000];
    double ans[1000];
    polynomial()
    {
        for (int i = 0; i < 1000; ++i)
        {
            pol[i] = 0;
            d[i] = 0;
            ans[i] = 0;
        }
    }
    bool get_pol(string str)
    {
        int len = str.length();
        int i = 0;
        bool is_add = true;
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
                    if (i < len && str[i] == '^')
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
                                pol[_tmp] += tmp;
                            else
                                pol[_tmp] += -1 * tmp;
                        }
                        else
                            return 0;
                    }
                    else
                    {
                        if (is_add)
                            pol[1] += tmp;
                        else
                            pol[1] += -1 * tmp;
                    }
                }
                else if (i < len && str[i] != '+' && str[i] != '-')
                    return 0;
                else
                {
                    if (is_add)
                        pol[0] += tmp;
                    else
                        pol[0] -= tmp;
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
                if (i < len && str[i] == '^')
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
                            pol[_tmp] += 1;
                        else
                            pol[_tmp] += -1 * 1;
                    }
                    else
                        return 0;
                }
                else
                {
                    if (is_add)
                        pol[1] += 1;
                    else
                        pol[1] += -1 * 1;
                }
            }
            else
                return 0;
        }
        return true;
    }
    void der()
    {
        for (int i = 999; i >= 0; --i)
        {
            if (i != 0)
                d[i - 1] = i * pol[i];
        }
    }
    void print()
    {
        bool tmp_flag = 1;
        for (int i = 0; i < 100; ++i)
            if (pol[i] != 0 || ans[i] != 0)
                tmp_flag = 0;
        if (tmp_flag)
        {
            printf("0.0000\n0.0000");
            return;
        }
        bool flag = 0;
        for (int i = 99; i >= 0; --i)
        {
            if (fabs(ans[i] - 0) > 1e-4)
            {
                int tmp = ans[i] * 10000;
                ans[i] = (double)tmp / 10000;
                if (flag && ans[i] >= 0)
                    printf("+%.4lf", ans[i]);
                else
                {
                    printf("%.4lf", ans[i]);
                    flag = 1;
                }
                if (i != 0)
                {
                    if (i == 1)
                        printf("x");
                    else
                    {
                        printf("x^");
                        printf("%d", i);
                    }
                }
            }
        }
        bool __flag = 0;
        for (int i = 0; i < 100; ++i)
            if (fabs(ans[i] - 0) > 1e-4)
                __flag = 1;
        if (flag)
            printf("\n");
        else
            printf("0.0000\n");
        flag = 0;
        for (int i = 99; i >= 0; --i)
        {
            if (fabs(pol[i] - 0) >= 1e-4)
            {
                int tmp = pol[i] * 10000;
                pol[i] = (double)tmp / 10000;
                if (flag && pol[i] >= 0)
                    printf("+%.4lf", pol[i]);
                else
                {
                    printf("%.4lf", pol[i]);
                    flag = 1;
                }
                if (i != 0)
                {
                    if (i == 1)
                        printf("x");
                    else
                    {
                        printf("x^");
                        printf("%d", i);
                    }
                }
            }
        }
        bool _flag = 0;
        for (int i = 0; i < 100; ++i)
            if (ans[i] != 0)
                _flag = 1;
        if (!_flag&&__flag)
            printf("0.0000\n");
        _flag = 0;
        for (int i = 0; i < 100; ++i)
            if (pol[i] != 0)
                _flag = 1;
        if (!_flag)
            printf("0.0000");
    }
    double cal(double x)
    {
        double ans = 0;
        double tmp = 1;
        for (int i = 0; i < 100; ++i)
        {
            tmp = 1;
            for (int j = 0; j < i; ++j)
                tmp *= x;
            ans += pol[i] * tmp;
        }
        return ans;
    }
    bool devide(polynomial &other)
    {
        int max1 = -1, max2 = -1;
        //判断是否可除
        for (int i = 99; i >= 0; --i)
            if (pol[i] != 0)
            {
                max1 = i;
                break;
            }
        for (int i = 99; i >= 0; --i)
            if (other.pol[i] != 0)
            {
                max2 = i;
                break;
            }
        if (max2 == -1) //除数为0
        {
            return 0;
        }
        if (max1 == -1) //被除数为0
        {
            for (int i = 0; i < 100; ++i)
            {
                pol[i] = 0;
                d[i] = 0;
                ans[i] = 0;
            }
            return 1;
        }
        if (max2 > max1)
        {
            for (int i = 0; i < 100; ++i)
                ans[i] = 0;
            return 1;
        }
        //计算
        while (max1 >= max2)
        {
            ans[max1 - max2] = pol[max1] / other.pol[max2];
            int tmp = max1 - max2;
            for (int i = 0; i <= max2; ++i)
                pol[i + tmp] -= other.pol[i] * ans[tmp];
            for (int i = 100; i >= 0; --i)
                if (fabs(pol[i]) >= 1e-1)
                {
                    max1 = i;
                    break;
                }
                else
                    max1 = 0;
            if (max1 == 0 && fabs(pol[0]) <= 1e-5)
                break;
        }
        return 1;
    }
};