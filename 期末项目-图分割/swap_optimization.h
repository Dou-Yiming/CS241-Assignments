#include "Graph_reader.h"
#include <queue>
#include <cmath>
struct swap_node
{
    int swap1, swap2;
    double delta;
    swap_node(int s1, int s2, double d) : swap1(s1), swap2(s2), delta(d) {}
    bool operator<(const swap_node &other) const
    {
        return delta < other.delta;
    }
};
class swap_optimization
{
private:
    int tag[3005] = {0}; //每个结点对应的子图编号
    vector<vector<double>> swap_value_updated;
    map<int, vector<edge>> adj_list; //邻接表

    priority_queue<swap_node> swap_q; //可以被交换的结点

    void calc_tag(const string &sub) //计算每个结点对应的子图编号
    {
        ifstream sub_graph_file(sub.c_str());
        string tmp;
        int cur_line = 1;
        while (getline(sub_graph_file, tmp))
        {
            vector<string> line = split(tmp);
            for (auto &no : line)
                tag[atoi(no.c_str())] = cur_line;
            ++cur_line;
        }
    }
    double calc_swap_delta(int ver1, int ver2)
    {
        register double delta = 0;
        for (auto &e : adj_list[ver1])
            if (tag[e.to] == tag[ver2] && e.to != ver2)
                delta += e.weight;
            else if (tag[e.to] == tag[ver1])
                delta -= e.weight;
        for (auto &e : adj_list[ver2])
            if (tag[e.to] == tag[ver1] && e.to != ver1)
                delta += e.weight;
            else if (tag[e.to] == tag[ver2])
                delta -= e.weight;
        return delta;
    }
    void init_swap_q()
    {
        register int ver1, ver2;
        register double delta = 0;
        for (auto &it1 : adj_list)
            for (auto &it2 : adj_list)
            {
                ver1 = it1.first;
                ver2 = it2.first;
                if (ver2 <= ver1) //不然会计算两次
                    continue;
                if (tag[ver1] != tag[ver2]) //不属于同一个子图
                {
                    delta = calc_swap_delta(ver1, ver2);
                    swap_value_updated[ver1][ver2] = delta;
                    if (delta > 0)
                    {
                        swap_q.push(swap_node(ver1, ver2, delta));
                        // printf("delta:%lf\n", delta);
                    }
                }
                else
                    swap_value_updated[ver1][ver2] = 0;
            }
    }
    void init(const string &origin, const string &sub)
    {
        Graph_reader reader(origin);
        adj_list = reader.get_adj_list(); //读取无向图，存成邻接表

        swap_value_updated.resize(3005);
        for (register int i = 0; i < 3005; ++i)
            swap_value_updated[i].resize(3005);

        calc_tag(sub); //计算每个结点所属子图

        init_swap_q(); //初始化优先队列
    }
    void swap_ver(int v1, int v2)
    {
        int tmp = tag[v1];
        tag[v1] = tag[v2];
        tag[v2] = tmp;
    }
    void update_value(int ver)
    {
        for (auto &e : adj_list[ver])
        {
            if (e.to < ver)
            {
                if (tag[ver] != tag[e.to])
                    swap_value_updated[e.to][ver] = calc_swap_delta(e.to, ver);
                else
                    swap_value_updated[e.to][ver] = 0;
            }
            else
            {
                if (tag[ver] != tag[e.to])
                    swap_value_updated[ver][e.to] = calc_swap_delta(e.to, ver);
                else
                    swap_value_updated[ver][e.to] = 0;
            }
        }
    }
    double calc_loss()
    {
        double ans = 0;
        for (auto &it : adj_list)
            for (auto &edge : it.second)
                if (tag[it.first] != tag[edge.to])
                    ans += edge.weight;
        return ans / 2;
    }

public:
    swap_optimization(string origin, string sub)
    {
        init(origin, sub);
    }
    void optimize()
    {
        while (!swap_q.empty()) //不空就一直可以交换
        {
            swap_node tmp = swap_q.top();
            swap_q.pop();
            if (fabs(tmp.delta - swap_value_updated[tmp.swap1][tmp.swap2]) < 1e-6) //当前就是最新
            {
                double tmp1 = calc_loss();
                swap_ver(tmp.swap1, tmp.swap2);
                printf("swapped! delta=%lf\n", tmp.delta);
                printf("current loss:%lf\n", calc_loss());
                double tmp2 = calc_loss();
                printf("%lf changed\n\n", tmp2 - tmp1);
                update_value(tmp.swap1);
                update_value(tmp.swap2);
            }
            // else //更新过
            // {
            //     if (swap_value_updated[tmp.swap1][tmp.swap2] > 0)
            //         swap_q.push(swap_node(tmp.swap1, tmp.swap2, swap_value_updated[tmp.swap1][tmp.swap2]));
            // }
        }
    }
};