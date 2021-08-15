#pragma once
#include <cstdio>

class Graph_merge
{
private:
    map<int, vector<edge>> origin_adj_list; //原图邻接表
    map<int, int> parent;                   //每个结点归属的子图

    void get_origin_adj_list(string origin)
    {
        Graph_reader origin_reader(origin);
        origin_adj_list = origin_reader.get_adj_list_dir();
    }
    void calc_parent(string sub)
    {
        ifstream sub_graph_file(sub.c_str());
        if (!sub_graph_file)
            cout << "err\n";
        string tmp;
        int cur_line = 1;
        while (getline(sub_graph_file, tmp))
        {
            vector<string> line = split(tmp);
            for (auto &no : line)
                parent[atoi(no.c_str())] = cur_line;
            ++cur_line;
        }
    }
    void save_sub_graph()
    {
        register int cur_vir = 0;
        for (auto &it : origin_adj_list)
        {
            if (!it.second.empty())
                for (auto &edge : it.second)
                {
                    int from = it.first, to = edge.to;
                    if (parent[from] == parent[to]) //实边
                    {
                        string str = "data\\subgraph\\sub_" + to_string(parent[from]) + ".txt";
                        ofstream ofile(str, ofstream::app);
                        string line = "<" + to_string(from) + "," + to_string(to) + "," +
                                      to_string(edge.weight) + ">\n";
                        ofile << line;
                        ofile.close();
                    }
                    else //虚边
                    {
                        string str = "data\\subgraph\\sub_" + to_string(parent[from]) + ".txt";
                        ofstream ofile(str, ofstream::app);
                        string line = "<" + to_string(from) + "," + "*" + "," + to_string(to) + "," +
                                      to_string(edge.weight) + ">\n";
                        ofile << line;
                        ofile.close();
                    }
                }
            else
            {
                string str = "data\\subgraph\\sub_" + to_string(parent[it.first]) + ".txt";
                ofstream ofile(str, ofstream::app);
                string line = "<" + to_string(it.first) + ">\n";
                ofile << line;
                ofile.close();
            }
        }
    }

public:
    Graph_merge(string origin, string sub)
    {
        get_origin_adj_list(origin);
        calc_parent(sub);
        save_sub_graph();
    }
    map<int, vector<edge>> &get_origin_adj_list()
    {
        return origin_adj_list;
    }
    map<int, int> &get_parent()
    {
        return parent;
    }
};