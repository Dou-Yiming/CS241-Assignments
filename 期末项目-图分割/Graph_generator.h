#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <ctime>
#include <fstream>

using namespace std;

const int RANGE_OF_VER = 3000;
const int RANGE_OF_WEIGHT = 10000;
struct Edge
{
	int from, to;
	double weight;
	Edge(int f, int t, double w) : from(f), to(t), weight(w) {}
};
class generator
{
private:
	int num_of_ver, num_of_Edge;
	map<int, int> c_to_d;
	map<int, int> d_to_c;
	map<int, bool> has_Edge;
	vector<Edge> vct_Edge;
	void get_ver()
	{
		srand(time(NULL));
		int no_of_ver;
		for (register int i = 1; i <= num_of_ver; ++i)
		{
			do
			{
				no_of_ver = rand() % RANGE_OF_VER;
			} while (d_to_c[no_of_ver] != 0);
			c_to_d[i] = no_of_ver;
			d_to_c[no_of_ver] = i;
			has_Edge[no_of_ver] = false;
		}
	}
	void create_if_not_exist(int ver)
	{
		if (d_to_c[ver] == 0)
		{
			c_to_d[++num_of_ver] = ver;
			d_to_c[ver] = num_of_ver;
			has_Edge[ver] = false;
			++num_of_ver;
		}
	}
	void get_Edge()
	{
		int from, to;
		double weight;
		int num_of_Edge_huge = num_of_Edge / 10;
		srand(time(NULL));
		for (register int i = 1; i <= num_of_Edge; ++i)
		{
			from = rand() % RANGE_OF_VER;
			to = rand() % RANGE_OF_VER;
			create_if_not_exist(from);
			create_if_not_exist(to);
			has_Edge[from] = has_Edge[to] = true;
			weight = rand() % RANGE_OF_WEIGHT + (double)(rand() % RANGE_OF_WEIGHT) / (double)RANGE_OF_WEIGHT;
			if (i <= num_of_Edge_huge)
				vct_Edge.push_back(Edge(from, to, weight));
			else
				vct_Edge.push_back(Edge(from, to, weight / 4));
		}
	}
	void print()
	{
		for (auto it : vct_Edge)
			printf("<%d,%d,%d>\n", it.from, it.to, it.weight);
	}
	void _add_Edge(int num)
	{
		num_of_Edge += num;
		int from, to, weight;
		srand(time(NULL));
		for (register int i = 1; i <= num; ++i)
		{
			from = rand() % RANGE_OF_VER;
			to = rand() % RANGE_OF_VER;
			create_if_not_exist(from);
			create_if_not_exist(to);
			has_Edge[from] = has_Edge[to] = true;
			weight = rand() % RANGE_OF_WEIGHT + (double)(rand() % RANGE_OF_WEIGHT) / (double)RANGE_OF_WEIGHT;
			vct_Edge.push_back(Edge(from, to, weight));
		}
	}
	void _add_Edge(int from, int to, double weight)
	{
		++num_of_Edge;
		create_if_not_exist(from);
		create_if_not_exist(to);
		has_Edge[from] = has_Edge[to] = true;
		vct_Edge.push_back(Edge(from, to, weight));
	}
	void _save()
	{
		ofstream ofile("data\\in.txt");
		string line;
		for (auto it : has_Edge)
		{
			if (!it.second)
			{
				line += ("<" + to_string(it.first) + ">");
				ofile << line << "\n";
				line.clear();
			}
		}
		for (auto it : vct_Edge)
		{
			line += ("<" + to_string(it.from) + "," + to_string(it.to) + "," + to_string(it.weight) + ">");
			ofile << line << "\n";
			line.clear();
		}
		ofile.close();
	}

public:
	generator(int v, int e) : num_of_ver(v), num_of_Edge(e)
	{
		get_ver();
		get_Edge();
	}
	void add_Edge(int num)
	{
		_add_Edge(num);
	}
	void add_Edge(int from, int to, int weight)
	{
		_add_Edge(from, to, weight);
	}
	void save()
	{
		_save();
	}
};