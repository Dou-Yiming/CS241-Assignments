#include "std_lib_facilities.h"
#include "NodeRecognition.h"
#include "TreeConstruct.h"

int main()
{
    bool exercise_1 = false;
    if (exercise_1)
    {
        //第一关执行代码
        //Please fix NodeRecognition.h and NodeRecognition.cpp
        graph g;
        string str;
        getline(cin, str);
        bool flag = g.get_relation(str);
        if (!flag)
        {
            cout << "We have recognized 0 graph.";
            return 0;
        }
        // cout<<"xxx"<<endl;
        g.cal();
        g._sort();
        g.print();
    }
    else
    {
        //第二关执行代码
        //Please fix TreeConstruct.h and TreeConstruct.cpp
        string str1, str2;
        getline(cin, str1);
        getline(cin, str2);
        Tree t1, t2;
        t1.get_relation(str1);
        t2.get_relation(str2);
        t1.cal();
        // cout<<"===\n";
        t2.cal();
        pair<int, string> ans1 = t1.ans(), ans2 = t2.ans();
        cout << ans1.first << ' ' << ans2.first << endl;
        cout << ans1.second << ' ' << ans2.second << endl;
        if (ans1.second == ans2.second)
            cout << "Yes";
        else
            cout << "No";
    }
    /********** End **********/
    return 0;
}