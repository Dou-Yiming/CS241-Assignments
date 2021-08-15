#include "std_lib_facilities.h"
#include "Polynomial.h"

int main()
{
    //请打开文件目录修改Polynomial.h，Polynomial.cpp，和exercise_2.cpp
    /********** Begin **********/

    bool exercise1 = false;
    if (exercise1)
    {
        //第一关执行代码
        string str;
        getline(cin, str);
        double x;
        scanf("%lf", &x);
        polynomial pol;
        bool flag = pol.get_pol(str);
        if (flag)
        {
            double ans = pol.cal(x);
            string a = to_string(ans);
            pol.der();
            pol.print();
            cout << '\n';
            int i = 0;
            while (a[i] != '.')
            {
                cout << a[i];
                ++i;
            }
            cout << '.';
            for (int j = 1; j <= 4; ++j)
                cout << a[i + j];
        }
        else
            printf("error\nerror\nerror");
    }
    else
    {
        //第二关执行代码
        string str1, str2;
        getline(cin, str1);
        getline(cin, str2);
        polynomial pol1, pol2;
        bool flag1 = pol1.get_pol(str1);
        bool flag2 = pol2.get_pol(str2);
        if (flag1 && flag2)
        {
            bool flag = pol1.devide(pol2);
            if (!flag)
            {
                printf("error\nerror");
                cout << 123 << endl;
            }
            else
                pol1.print();
        }
        else
            printf("error\nerror");
    }
    /********** End **********/
    return 0;
}
