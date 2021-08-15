#pragma once
#include "Graph_reader.h"
#include <cstdio>
#include <cstring>
#include <queue>
struct wait_node
{
    int from, root;
    double weight;
    wait_node(int f, int r, double w) : from(f), root(r), weight(w) {}
    bool operator<(const wait_node &other) const
    {
        return weight < other.weight;
    }
};
class Graph_cutter
{
private:
    map<int, vector<edge>> adj_list; //邻接表

    vector<int> ver_vct; //所有的结点
    int num_of_ver;      //结点数
    int num_of_root;     //生长点数

    map<int, int> tag; //生长簇标签
    int cur_size[3005];

    vector<int> root; //生长点编号
    bool is_root[3005];

    double sum_dist[3005][3005];    //结点i到生长点j的连边权重和
    priority_queue<wait_node> heap; //用来选当前权重最大的结点

    void init(Graph_reader &reader)
    {
        adj_list = reader.get_adj_list();
        num_of_ver = adj_list.size();
        for (auto &it : adj_list)
        {
            tag[it.first] = it.first;
            ver_vct.push_back(it.first);
        }
        for (auto &ver : ver_vct)
            is_root[ver] = false;
    }
    void init_sum_dist()
    {
        memset(sum_dist, 0.0, sizeof(sum_dist));
        for (auto &r : root)
            for (auto &edge : adj_list[r])
                sum_dist[edge.to][r] += edge.weight;
    }
    void init_heap()
    {
        for (auto &r : root)
            for (auto ver : ver_vct)
                if (!is_root[ver])
                    heap.push(wait_node(ver, r, sum_dist[ver][r]));
    }
    int calc_num_of_root(int size_of_subgraph)
    {
        int ans = num_of_ver / size_of_subgraph;
        if (num_of_ver % size_of_subgraph != 0)
            ans++;
        return ans;
    }
    void get_root()
    {
        int root_no;
        for (register int i = 0; i < num_of_root; ++i)
        {
            do
            {
                root_no = ver_vct[rand() % num_of_ver];
            } while (is_root[root_no]);
            root.push_back(root_no);
            is_root[root_no] = true;
            cur_size[root_no] = 1;
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
    // void swap_optimize(int num_of_swap)
    // {
    //     int swap1, swap2;
    //     double cur_loss;
    //     for (register int i = 0; i < num_of_swap; ++i)
    //     {
    //         swap1 = ver_vct[rand() % num_of_ver];
    //         swap2 = ver_vct[rand() % num_of_ver];
    //         cur_loss = calc_loss();
    //         swap_ver(swap1, swap2);
    //         double swapped_loss=calc_loss();
    //         if (swapped_loss >= cur_loss)
    //             swap_ver(swap1, swap2);
    //         else
    //             printf("     swapped! Current loss: %lf     ", swapped_loss);
    //     }
    // }
    // void swap_ver(int s1, int s2)
    // {
    //     int tmp = tag[s1];
    //     tag[s1] = tag[s2];
    //     tag[s2] = tmp;
    // }

public:
    Graph_cutter(Graph_reader &reader)
    {
        init(reader);
    }
    double ver_algorithm(int size_of_subgraph, int delta)
    {
        num_of_root = calc_num_of_root(size_of_subgraph); //计算生长点数
        if (num_of_root + delta <= num_of_ver)            //波动修正量
            num_of_root += delta;
        get_root();      //确定生长点
        init_sum_dist(); //初始化数组
        init_heap();     //初始化堆

        register int left_ver = num_of_ver - num_of_root;
        int ver_to_be_added, root_to_be_added;
        while (left_ver)
        {
            //找最大的点
            while (cur_size[heap.top().root] >= size_of_subgraph || tag[heap.top().from] != heap.top().from ||
                   is_root[heap.top().from])
                heap.pop();
            wait_node tmp_node = heap.top();
            heap.pop();
            ver_to_be_added = tmp_node.from;
            root_to_be_added = tmp_node.root;
            //更新
            tag[ver_to_be_added] = root_to_be_added;
            ++cur_size[root_to_be_added];
            for (auto &edge : adj_list[ver_to_be_added])
                if (tag[edge.to] != root_to_be_added)
                {
                    sum_dist[edge.to][root_to_be_added] += edge.weight;
                    heap.push(wait_node(edge.to, root_to_be_added, sum_dist[edge.to][root_to_be_added]));
                }
            --left_ver;
        }
        // swap_optimize(10000);
        return calc_loss();
    }
    int &get_num_of_ver()
    {
        return num_of_ver;
    }
    int &get_num_of_root()
    {
        return num_of_root;
    }
    vector<int> &get_root_vct()
    {
        return root;
    }
    vector<int> &get_ver_vct()
    {
        return ver_vct;
    }
    map<int, int> &get_tag()
    {
        return tag;
    }
};