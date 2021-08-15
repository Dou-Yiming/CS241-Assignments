class SimpleLinearRegression
{
public:
    point p[100];
    double avg_x = 0, avg_y = 0;
    double Lxx = 0, Lxy = 0, Lyy = 0;
    double r = 0;
    double a = 0, b = 0;
    double ans = 0;
    int size = 0;
    SimpleLinearRegression() {}
    bool get_points(string str)
    {
        int len = str.length();
        int i = 0;
        int pos = 0;
        bool is_x = true;
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
                    float index = 0.1;
                    while (i < len && str[i] <= '9' && str[i] >= '0')
                    {
                        tmp += (str[i] - '0') * index;
                        ++i;
                        index /= 10;
                    }
                }
                if ((i < len && str[i] == ' ') || i == len)
                {
                    if (pos == 0) //待估值的点
                    {
                        if (is_add)
                            p[pos].x += tmp;
                        else
                            p[pos].x -= tmp;
                        is_add = true;
                        ++pos;
                    }
                    else
                    {
                        if (is_add)
                        {
                            if (is_x)
                            {
                                p[pos].x += tmp;
                                is_x = 1 - is_x;
                            }
                            else
                            {
                                p[pos].y += tmp;
                                is_x = 1 - is_x;
                                // cout << "y+=" << tmp << endl;
                                ++pos;
                                ++size;
                            }
                        }
                        else
                        {
                            is_add = true;
                            if (is_x)
                            {
                                p[pos].x -= tmp;
                                is_x = 1 - is_x;
                            }
                            else
                            {
                                p[pos].y -= tmp;
                                is_x = 1 - is_x;
                                ++pos;
                                ++size;
                            }
                        }
                    }
                    ++i;
                    if (i == len)
                        return true;
                }
                else if (i < len)
                    return 0;
            }
            else if (str[i] == '-')
            {
                is_add = false;
                ++i;
                if (i == len || (str[i] > '9' || str[i] < '0'))
                    return 0;
            }
            else
                return 0;
        }
        return true;
    }
    bool judge()
    {
        double tmp = 0;
        for (int i = 1; i <= size; ++i)
            tmp += p[i].x;
        avg_x = tmp / size;
        tmp = 0;
        for (int i = 1; i <= size; ++i)
            tmp += p[i].y;
        avg_y = tmp / size;
        for (int i = 1; i <= size; ++i)
        {
            Lxx += (p[i].x - avg_x) * (p[i].x - avg_x);
            Lyy += (p[i].y - avg_y) * (p[i].y - avg_y);
            Lxy += (p[i].x - avg_x) * (p[i].y - avg_y);
        }
        r = Lxy / sqrt(Lxx * Lyy);
        if (fabs(r) >= 0.75)
            return true;
        else
            return false;
    }
    void cal()
    {
        b = Lxy / Lxx;
        a = avg_y - b * avg_x;
        ans = b * p[0].x + a;
    }
    void print()
    {
        // for (int i = 0; i <= size; ++i)
        // {
        //     cout << p[i].x << ' ';
        // }
        // cout << endl;
        int i = 0;
        string tmp;
        // if (size == 1 || fabs(Lyy) < 1e-5)
        // {
        //     if (fabs(p[1].y) < 1e-5)
        //     {
        //         cout << "0.0000\n0.0000";
        //         return;
        //     }
        //     else
        //     {
        //         cout<<"y=";

        //     }
        // }

        cout << "y=";
        if (fabs(b) < 1e-5)
        {
            cout << "0.0000";
            goto next1;
        }
        tmp = to_string(b);
        while (tmp[i] != '.')
        {
            cout << tmp[i];
            ++i;
        }
        cout << ".";
        for (int j = 1; j <= 4; ++j)
            cout << tmp[i + j];
    next1:
        cout << "*x";
        if (a >= 0)
            cout << "+";
        if (fabs(a) < 1e-5)
        {
            cout << "0.0000\n";
            goto next2;
        }
        tmp = to_string(a);
        i = 0;
        while (tmp[i] != '.')
        {
            cout << tmp[i];
            ++i;
        }
        cout << ".";
        for (int j = 1; j <= 4; ++j)
            cout << tmp[i + j];
        cout << endl;
    next2:
        if (fabs(ans) < 1e-5)
        {
            cout << "0.0000";
            return;
        }
        tmp = to_string(ans);
        i = 0;
        while (tmp[i] != '.')
        {
            cout << tmp[i];
            ++i;
        }
        cout << ".";
        for (int j = 1; j <= 4; ++j)
            cout << tmp[i + j];
    }
};