#include "std_lib_facilities.h"
#include "Polynomial.h"
#include "LinearEquations.h"

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
        float left, right; //左右区间
        cin >> left;
        // cout << "===\n";
        cin >> right;
        // cout << "===\n";
        polynomial pol;
        bool flag = pol.get_pol(str);
        if (!flag || left > right) //输入不合法
        {
            printf("error");
            return 0;
        }
        float l = pol.cal(left), r = pol.cal(right);
        if (l * r >= 0) //两点乘积不小于0
        {
            printf("error");
            return 0;
        }
        pol.der();
        if (!pol.judge(left, right)) //判断是否满足条件
        {
            printf("error");
            return 0;
        }
        float ans = pol.solve(left, right);
        printf("%.4lf", ans);
    }
    else
    {
        //第二关执行代码
        LinearEquations eq;
        string str;
        int pos = 0;
        while (getline(cin, str))
        {
            // cout << pos << endl;
            if (!eq.get_equation(str, ++pos))
            {
                cout << "error";
                return 0;
            }
        }
        //  cout << pos << endl;
        int cur = eq.map();
        // cout<<"===\n";
        // eq.print(cur);
        // cout<<"========"<<4.677*0.5<<endl;
        double ans[100]={0};
        bool flag = eq.solve(pos, cur);
        // cout<<endl;

        // eq.print(cur);
        if (!flag)
        {
            cout << "error";
            return 0;
        }
    }
    /********** End **********/
    return 0;
}
