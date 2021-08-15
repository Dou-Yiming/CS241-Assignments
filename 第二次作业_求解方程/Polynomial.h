#include <iostream>
#include <cstdio>
using namespace std;

class polynomial
{
public:
    float pol[1000] = {0};
    float d[1000] = {0};
    float dd[1000] = {0};
    float ans[1000] = {0};
    polynomial() {}
    bool get_pol(string str)
    {
        int len = str.length();
        int i = 0;
        bool is_add = true;
        while (i < len)
        {
            if (str[i] <= '9' && str[i] >= '0')
            {
                float tmp = 0;
                while (i < len && str[i] <= '9' && str[i] >= '0')
                {
                    tmp *= 10;
                    tmp += (str[i] - '0');
                    ++i;
                }
                if (i < len && str[i] == '.')
                {
                    ++i;
                    float index = 0.1;
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
        for (int i = 999; i >= 0; --i)
        {
            if (i != 0)
                dd[i - 1] = i * d[i];
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
                ans[i] = (float)tmp / 10000;
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
                pol[i] = (float)tmp / 10000;
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
        if (!_flag && __flag)
            printf("0.0000\n");
        _flag = 0;
        for (int i = 0; i < 100; ++i)
            if (pol[i] != 0)
                _flag = 1;
        if (!_flag)
            printf("0.0000");
    }
    float cal(float p[], float x)
    {
        float ans = 0;
        float tmp = 1;
        for (int i = 0; i < 100; ++i)
        {
            tmp = 1;
            if (p[i] != 0)
            {
                for (int j = 0; j < i; ++j)
                    tmp *= x;
                ans += p[i] * tmp;
            }
        }
        return ans;
    }
    float cal(float x)
    {
        float ans = 0;
        float tmp = 1;
        for (int i = 0; i < 100; ++i)
        {
            tmp = 1;
            for (int j = 0; j < i; ++j)
                tmp *= x;
            ans += pol[i] * tmp;
        }
        return ans;
    }
    bool judge(float left, float right)
    {
        float pace = (right - left) / 10000;
        for (int i = 0; i <= 10000; ++i)
            if (fabs(cal(d, left + (float)i * pace)) < 1e-4)
                return false;
        float l = cal(dd, left);
        for (int i = 0; i <= 10000; ++i)
        {
            if (cal(dd, left + (float)i * pace) * l <= 0)
                return false;
        }
        if ((left - cal(pol, left) / cal(d, left)) > right || (right - cal(pol, right) / cal(d, right)) < left)
            return false;
        return true;
    }
    float solve(float left, float right)
    {
        float ans = right, tmp = right;
        do
        {
            ans = tmp;
            tmp = ans - (cal(pol, ans) / cal(d, ans));
        } while (fabs(ans - tmp) > 1e-6);
        return ans;
    }
};