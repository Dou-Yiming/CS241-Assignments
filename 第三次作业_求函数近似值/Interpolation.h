struct point
{
    double x = 0;
    double y = 0;
};
class interpolation
{
public:
    point p[100];
    double F[100][100];
    int size = 0;
    interpolation()
    {
        for (int i = 0; i < 100; ++i)
            for (int j = 0; j < 100; ++j)
                F[i][j] = 0;
    }
    void _swap(int i, int j)
    {
        point tmp = p[j];
        p[j] = p[i];
        p[i] = tmp;
    }
    void qsort(int l, int r)
    {
        if (l >= r)
            return;
        double key = p[l].x;
        point tmp = p[l];
        int left = l, right = r;
        while (left < right)
        {
            while (left < right && p[right].x >= key)
            {
                --right;
            }
            if (left < right)
            {
                p[left] = p[right];
                ++left;
            }
            while (left < right && p[left].x <= key)
                ++left;
            if (left < right)
            {
                p[right] = p[left];
                --right;
            }
        }
        p[left] = tmp;
        qsort(l, left);
        qsort(left + 1, r);
    }
    bool judge()
    {
        double gap = p[2].x - p[1].x;
        // cout<<"size:"<<size<<endl;
        for (int i = 2; i < size; ++i)
            if (fabs(p[i + 1].x - p[i].x - gap) > 1e-5)
                return false;
        return true;
    }
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
                        is_add=true;
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
    double Newton()
    {
        //计算各阶差商
        for (int i = 1; i <= size - 1; ++i)
            F[i][i + 1] = (p[i].y - p[i + 1].y) / (p[i].x - p[i + 1].x);
        for (int pace = 2; pace <= size - 1; ++pace)
        {
            for (int i = 1; i <= size - pace; ++i)
            {
                F[i][i + pace] = (F[i][i + pace - 1] - F[i + 1][i + pace]) /
                                 (p[i].x - p[i + pace].x);
            }
        }
        //计算估值
        double ans = p[1].y;
        double tmp = 1;
        for (int i = 2; i <= size; ++i)
        {
            tmp *= (p[0].x - p[i - 1].x);
            ans += F[1][i] * tmp;
        }
        return ans;
    }
    void print()
    {
        for (int i = 0; i <= size; ++i)
        {
            cout << p[i].x << ' ';
        }
        cout << endl;
    }
};