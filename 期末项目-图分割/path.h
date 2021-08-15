#include "Save_sub_graph.h"
#include <map>
#include <vector>
struct path_edge
{
    int to;
    double weight;
    bool is_virtual;
    path_edge(int t, double w, bool v = false)
        : to(t), weight(w), is_virtual(v) {}
};
const double INF = 1000000;
class path
{
private:
    map<int, vector<edge>> origin_adj_list;   //原图邻接表
    map<int, vector<path_edge>> sub_adj_list; //子图邻接表
    vector<int> ver_vct;                      //所有节点
    map<int, int> parent;                     //每个结点归属的子图
    vector<vector<double>> shortest_path;     //最短路径

    void init()
    {
        bool visited[3005] = {false};
        for (auto &it : origin_adj_list)
        {
            for (auto &e : it.second)
            {
                if (parent[it.first] != parent[e.to]) //是虚结点
                    sub_adj_list[it.first].push_back(path_edge(e.to, e.weight, true));
                else
                    sub_adj_list[it.first].push_back(path_edge(e.to, e.weight, false));
                if (!visited[e.to])
                {
                    ver_vct.push_back(e.to);
                    visited[e.to] = true;
                }
            }
            if (!visited[it.first])
            {
                ver_vct.push_back(it.first);
                visited[it.first] = true;
            }
        }

        shortest_path.resize(3005);
        for (register int i = 0; i < 3005; ++i)
            shortest_path[i].resize(3005);
    }
    void dijkdtra(int source)
    {
        for (register int i = 0; i < 3005; ++i)
            for (register int j = 0; j < 3005; ++j)
                shortest_path[i][j] = i == j ? 0 : INF;
        bool final[3005] = {false};
        int s[3005] = {0};
        s[0] = source;

        for (auto &it : sub_adj_list)
            for (auto &e : it.second)
                shortest_path[it.first][e.to] = e.weight;
        int num = 1;
        while (num < sub_adj_list.size())
        {
            int k = 0;
            double min_weight = INF;
            //找连接点中最小的
            for (auto &ver : ver_vct)
            {
                if (ver == source)
                    continue;
                if (!final[ver] && shortest_path[source][ver] < min_weight)
                {
                    k = ver;
                    min_weight = shortest_path[source][ver];
                }
            }
            s[num++] = k;
            final[k] = true;
            for (auto &ver : ver_vct)
            {
                if (!final[ver] && shortest_path[source][ver] > shortest_path[source][k] + shortest_path[k][ver])
                    shortest_path[source][ver] = shortest_path[source][k] + shortest_path[k][ver];
            }
        }
    }

public:
    path(Graph_merge m)
    {
        origin_adj_list = m.get_origin_adj_list();
        parent = m.get_parent();
        init();
    }
    void print_node_connected(int source)
    {
        bool flag = false;
        for (auto &ver : ver_vct)
            if (ver == source)
            {
                flag = true;
                break;
            }
        if (!flag)
        {
            printf("node doesn't exist!\n");
            return;
        }
        dijkdtra(source);
        for (auto &ver : ver_vct)
            if (shortest_path[source][ver] == INF)
                printf("node %d can not reach node %d\n", source, ver);
            else
                printf("node %d can reach node %d\n",
                       source, ver);
    }
    void print_shortest_path(int ver1, int ver2)
    {
        bool flag1 = false, flag2 = false;
        for (auto &ver : ver_vct)
            if (ver == ver1)
                flag1 = true;
            else if (ver == ver2)
                flag2 = true;
        if (!flag1 || !flag2)
        {
            printf("node doesn't exist!\n");
            return;
        }
        dijkdtra(ver1);
        if (shortest_path[ver1][ver2] == INF)
            printf("No path exists!\n");
        else
            printf("The shortest path: %lf\n",
                   shortest_path[ver1][ver2]);
    }
};