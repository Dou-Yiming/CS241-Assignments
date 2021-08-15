#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <ctime>
#include <fstream>
#include <ostream>
using namespace std;

bool is_num(char x)
{
	return x >= '0' && x <= '9';
}
struct edge
{
	int to;
	double weight;
	edge(int t, double w) : to(t), weight(w) {}
};
vector<string> split(string str)
{
	int len = str.length();
	string tmp;
	int pos = 0;
	vector<string> ans;
	while (pos != len)
	{
		while (pos != len && !is_num(str[pos]))
			++pos;
		while (pos != len && (is_num(str[pos]) || str[pos] == '.'))
		{
			tmp += (str[pos]);
			++pos;
		}
		ans.push_back(tmp);
		tmp.clear();
	}
	if (ans[ans.size() - 1].empty())
		ans.pop_back();
	return move(ans);
}
class Graph_reader
{
private:
	map<int, vector<edge>> adj_list;
	map<int, vector<edge>> adj_list_dir;
	int num_of_ver;
	std::pair<int, edge> transform(vector<string> vct)
	{
		int size = vct.size();
		// cout << "size:" << size << endl;
		int from, to = -1;
		double weight = 0;
		for (int i = 0; i < size; ++i)
		{
			if (i == 0)
				from = atoi(vct[0].c_str());
			else if (i == 1)
				to = atoi(vct[1].c_str());
			else
				weight = atof(vct[2].c_str());
		}
		return std::make_pair(from, edge(to, weight));
	}
	void save(std::pair<int, edge> p)
	{
		int from = p.first;
		int to = p.second.to;
		double weight = p.second.weight;
		if (to == -1 || from == to)
		{
			adj_list[from].push_back(edge(0, 0));
			adj_list[from].pop_back();
			adj_list_dir[from].push_back(edge(0, 0));
			adj_list_dir[from].pop_back();
		}
		else
		{
			adj_list_dir[from].push_back(edge(to, weight));
			adj_list[from].push_back(edge(to, weight));
			adj_list[to].push_back(edge(from, weight));
		}
	}
	void read_graph(const string &str)
	{
		ifstream origin_graph(str.c_str());
		if (!origin_graph)
			cout << "err" << endl;
		string tmp;
		while (getline(origin_graph, tmp))
			save(transform(split(tmp)));
	}

public:
	Graph_reader(string str)
	{
		read_graph(str);
	}
	void print()
	{
		cout << adj_list.size() << endl;
		for (auto &it : adj_list)
		{
			printf("size:%d\n", it.second.size());
			for (auto &_it : it.second)
			{
				cout << it.first << "->";
				cout << _it.to << " weight:" << _it.weight << endl;
			}
			cout << endl;
		}
	}
	map<int, vector<edge>> &get_adj_list()
	{
		return adj_list;
	}
	map<int, vector<edge>> &get_adj_list_dir()
	{
		return adj_list_dir;
	}
};