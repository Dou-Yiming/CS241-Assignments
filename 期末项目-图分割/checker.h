#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <utility>
#include <algorithm>
#include <typeinfo>
// using namespace std;

namespace ftc
{
	// OK 2020-12-12
	inline bool is_num(char c)
	{
		// 0~9 .
		return (c >= '0' && c <= '9') || c == '.';
	}
	// OK 2020-12-12
	inline bool is_word(char c)
	{
		return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
	}
	// OK 2020-12-12
	inline bool is_split(char c)
	{
		return !is_num(c);
	}
	template <class T>
	class Checker;

	struct Error
	{
		int line;
		std::string message;
		Error(int l, const std::string &msg) : line(l), message(msg) {}
		void print_error() const noexcept
		{
			std::cerr << "error in line " << line << '\n';
			std::cerr << "error message: " << message << std::endl;
		}
	};

	// OK 2020-12-12
	template <class T>
	struct Edge
	{
		int from, to;
		T weight;
		void print_edge() const noexcept
		{
			std::cout << from << " -> " << to << "  w = " << weight << '\n';
		}
		Edge(int f, int t, T w) : from(f), to(t), weight(w) {}
	};
	//
	std::vector<std::string> split(const std::string &str) noexcept
	{
		std::vector<std::string> ans;
		for (size_t i = 0; i < str.length(); i++)
		{
			while (i < str.length() && is_split(str[i]))
				i++;
			auto prev_i = i;
			while (i < str.length() && is_num(str[i]))
				i++;
			if (i > prev_i)
				ans.push_back(std::move(str.substr(prev_i, i - prev_i)));
		}
		return std::move(ans);
	}

	template <class T = double>
	class Checker
	{
	private:
		std::map<int, std::vector<Edge<T>>> edges; // edge<T> 存的[结点原始编号]
		std::set<int> raw_node;
		std::map<int, int> node_to_base;
		int max_base;
		double total_weight;
		double run(std::ostream &out) const noexcept
		{
			double loss = 0.0;
			for (const auto &key_value : edges)
			{
				auto &vct_edge = key_value.second;
				for (const auto &edge : key_value.second)
				{
					if (node_to_base.at(edge.from) != node_to_base.at(edge.to))
						loss += edge.weight;
				}
			}
			out << "loss / total = " << loss << " / " << total_weight << std::endl;
			// out << 1.0 - loss / total_weight << "% of edges cutted" << std::endl;
			return loss;
		}

	public:
		Checker(const std::string &GraphFileName) : max_base(0), total_weight(0.0)
		{
			std::fstream fs;
			fs.open(GraphFileName);
			if (!fs.good())
				throw Error(__LINE__, "open file error");
			else
				printf("successfully open %s\n", GraphFileName.c_str());
			std::string str;
			while (std::getline(fs, str))
			{
				auto str_split = split(str);
				if (str_split.empty())
					continue;
				if (str_split.size() == 1)
				{
					int num = atoi(str_split[0].c_str());
					raw_node.insert(num);
					edges.insert(std::make_pair(num, std::vector<Edge<T>>()));
				}
				else if (str_split.size() == 3)
				{
					int from = atoi(str_split[0].c_str());
					int to = atoi(str_split[1].c_str());
					raw_node.insert(from);
					raw_node.insert(to);
					T weight;
					if (typeid(T) == typeid(double))
					{
						// printf("T == double\n");
						weight = (T)atof(str_split[2].c_str());
					}
					else if (typeid(T) == typeid(int))
					{
						// printf("T == int\n");
						weight = (T)atoi(str_split[2].c_str());
					}
					else
					{
						fs.close();
						throw Error(__LINE__, "type error");
					}

					// 无向边 from -> to
					Edge<T> e(from, to, weight);
					this->total_weight += weight;
					auto result1 = edges.insert(std::make_pair(from, std::vector<Edge<T>>{e}));
					if (!result1.second)
					{
						// 如果没有插入成功
						// e.print_edge();
						(result1.first->second).push_back(e);
					}
				}
				else
				{
					fs.close();
					throw Error(__LINE__, "format error");
				}
			} // end while getline
			fs.close();
		}
		void check(const std::string &filename, std::ostream &out = std::cout)
		{
			std::fstream fs;
			fs.open(filename, std::ios::in);
			std::string str;
			max_base = 0;
			int count = 0;
			while (std::getline(fs, str))
			{
				auto split_str = split(str);
				if (split_str.empty())
					continue;
				for (auto &s : split_str)
				{
					int node = atoi(s.c_str());
					// printf("read %d\n",node);
					if (raw_node.find(node) == raw_node.cend())
					{
						throw Error(__LINE__, "node number error");
					}
					++count;
					auto result = node_to_base.insert(std::make_pair(node, max_base));
					if (!result.second)
					{
						throw Error(__LINE__, "double node");
					}
					raw_node.insert(node);
				}

				++max_base;
			}
			if (count != raw_node.size())
			{
				// printf("count = %d, nodesize = %d\n",count,raw_node.size());
				throw Error(__LINE__, "node don't exist");
			}
			run(out);
		}

	}; // end class Checker

} // end namespace ftc