#include "std_lib_facilities.h"
#include "Interpolation.h"
#include "SimpleLinearRegression.h"

//定义main函数
int main()
{
	/********** Begin **********/
	bool exercisel = false;
	if (exercisel)
	{
		//第一关执行代码 完成 Interpolation.cpp与 Interpolation.h文件
		string str; //测试输入数据存放变量
		string tmp;
		while (getline(cin, tmp))
		{
			str += tmp;
			str += " ";
		}
		// cout << str << endl;
		interpolation inter;
		bool flag = inter.get_points(str);
		cout << "aaa" << flag << endl;
		inter.qsort(1, inter.size);
		for (int i = 1; i <= inter.size; ++i)
			cout << inter.p[i].x << ' ' << inter.p[i].y << endl;
		if (!inter.judge() || !flag) //不满足等距条件
		{
			cout << "error";
			return 0;
		}
		double ans = inter.Newton();
		if (fabs(ans) < 1e-5)
		{
			printf("0.0000");
			return 0;
		}
		string a = to_string(ans);
		int i = 0;
		while (a[i] != '.')
		{
			cout << a[i];
			++i;
		}
		cout << ".";
		for (int j = 1; j <= 4; ++j)
			cout << a[i + j];
	}
	else
	{
		//第二执行代码 完成 SimpleLinearRegression.cpp与 SimpleLinearRegression.h文件
		string str; //测试输入数据存放变量
		string tmp;
		while (getline(cin, tmp))
		{
			str += tmp;
			str += " ";
		}
		SimpleLinearRegression regression;
		if (!regression.get_points(str))
		{
			cout << "error\nerror\nerror";
			return 0;
		}
		bool flag = regression.judge();
		if(fabs(regression.Lyy)<1e-5||regression.size==1)
		{
			cout << "error\nerror\nerror";
			return 0;			
		}
		string a = to_string(regression.r);
		int i = 0;
		while (a[i] != '.')
		{
			cout << a[i];
			++i;
		}
		cout << ".";
		for (int j = 1; j <= 4; ++j)
			cout << a[i + j];
		cout<<endl;
		if(!flag)
		{
			cout<<"error\nerror";
			return 0;
		}
		regression.cal();
		regression.print();
	}

	/********** End **********/
	return 0;
}
