#pragma once
#include "Graph_reader.h"
#include <cstdio>
#include <cstring>
#include <queue>
struct another_edge
{
    int from, to;
    double weight;
    another_edge(int f, int t, double w) : from(f), to(t), weight(w) {}
    bool operator<(const another_edge &other)const
    {
        return weight < other.weight;
    }
};
class Graph_cutter_edge
{
private:
    map<int, vector<edge>> adj_list; //邻接表
    vector<int> ver_vct;             //所有的结点
    map<int, int> tag;
    int cur_size[3005] = {0};
    int num_of_ver;
    int num_of_root = 0;
    priority_queue<another_edge> edge_q;
    void init(Graph_reader &reader)
    {
        adj_list = reader.get_adj_list();
        num_of_ver = adj_list.size();
        for (auto &it : adj_list)
        {
            tag[it.first] = -1;
            ver_vct.push_back(it.first);
            for (auto &e : it.second)
                edge_q.push(another_edge(it.first, e.to, e.weight));
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
    Graph_cutter_edge(Graph_reader &reader)
    {
        init(reader);
    }
    double another_algorithm(int size_of_sub_graph)
    {
        while (!edge_q.empty())
        {
            another_edge tmp = edge_q.top();
            edge_q.pop();
            if (tag[tmp.from] == -1 && tag[tmp.to] == -1)
            {
                tag[tmp.from] = tag[tmp.to] = ++num_of_root;
                cur_size[num_of_root] += 2;
            }
            else if (tag[tmp.from] == -1 &&
                     cur_size[tag[tmp.to]] < size_of_sub_graph)
            {
                tag[tmp.from] = tag[tmp.to];
                cur_size[tag[tmp.to]]++;
            }
            else if (tag[tmp.to] == -1 &&
                     cur_size[tag[tmp.from]] < size_of_sub_graph)
            {
                tag[tmp.to] = tag[tmp.from];
                cur_size[tag[tmp.from]]++;
            }
        }
        return calc_loss();
    }
};