bool cmp(pair<int, int> a, pair<int, int> b)
{
    if (a.first != b.first)
        return a.first < b.first;
    else
        return a.second < b.second;
}
class graph
{
private:
    vector<int> son[10000];
    vector<int> strict_son[10000];
    vector<std::pair<int, int>> node, b_tree, tree, _graph;
    bool exist[10000] = {0};
    int num_of_son[10000] = {0};
    int indeg[10000] = {0};
    bool checked[10000] = {0};
    bool is_num(char x)
    {
        return x <= '9' && x >= '0';
    }

public:
    graph() {}
    bool get_relation(string str)
    {
        for (int i = 0; i < str.length(); ++i)
        {
            // cout << str[i] << endl;
            if (str[i] == '<')
            {
                ++i;
                int flag = 0;
                int num1, num2;
                while (str[i] != '>')
                {
                    // cout<<str[i]<<endl;
                    if (is_num(str[i]))
                    {
                        int tmp = str[i] - '0';
                        ++i;
                        while (is_num(str[i]))
                        {
                            tmp *= 10;
                            tmp += (str[i] - '0');
                            ++i;
                        }
                        if (flag == 0)
                        {
                            num1 = tmp;
                            flag++;
                        }
                        else if (flag == 2)
                        {
                            num2 = tmp;
                            if (str[i] != '>')
                                return 0;
                        }
                    }
                    else if (str[i] == ' ')
                    {
                        flag++;
                        ++i;
                    }
                }
                if (flag == 1)
                    exist[num1] = 1;
                else if (flag == 2)
                {
                    exist[num1] = exist[num2] = 1;
                    son[num1].push_back(num2);
                    son[num2].push_back(num1);
                    strict_son[num2].push_back(num1);
                    num_of_son[num2]++;
                    indeg[num1]++;
                }
                else
                    return 0;
            }
            else if (str[i] != ' ')
            {
                return 0;
            }
        }
        return 1;
    }
    void cal()
    {
        for (int i = 0; i < 10000; ++i) //找树
        {
            if (exist[i] && !checked[i] && indeg[i] == 0)
            {
                // cout << i << endl;
                if (indeg[i] == 0 && num_of_son[i] == 0) //单点
                {
                    checked[i] = 1;
                    node.push_back(std::make_pair(i, 1));
                }
                else
                {
                    bool is_tree = 1, is_btree = 1;
                    int size = 0, weight = 0;
                    _dfs(i, is_tree, is_btree, size, weight);
                    if (!is_tree)
                        _graph.push_back(std::make_pair(weight, size));
                    else
                    {
                        if (is_btree)
                            b_tree.push_back(std::make_pair(weight, size));
                        else
                            tree.push_back(std::make_pair(weight, size));
                    }
                }
            }
        }
        if (tree.size() == 0 && b_tree.size() == 0)
        {
            for (int i = 0; i < 10000; ++i)
                checked[i] = 0;
            _graph.clear();
            node.clear();
        }
        for (int i = 0; i < 10000; ++i)
        {
            if (exist[i] && !checked[i])
            {
                if (indeg[i] == 0 && num_of_son[i] == 0) //单点
                {
                    checked[i] = 1;
                    node.push_back(std::make_pair(i, 1));
                }
                else
                {
                    bool is_tree = 1, is_btree = 1;
                    int size = 0, weight = 0;
                    dfs(i, is_tree, is_btree, size, weight);
                    if (!is_tree)
                        _graph.push_back(std::make_pair(weight, size));
                    else
                    {
                        if (is_btree)
                            b_tree.push_back(std::make_pair(weight, size));
                        else
                            tree.push_back(std::make_pair(weight, size));
                    }
                }
            }
        }
    }
    void dfs(int node, bool &is_tree, bool &is_btree, int &size, int &weight)
    {
        if (checked[node] || !exist[node])
            return; //递归终止
        checked[node] = 1;
        size++;
        weight += node;
        if (indeg[node] > 1) //入度>=1
            is_tree = 0;
        if (num_of_son[node] >= 2) //儿子多于两个
            is_btree = 0;
        for (int i = 0; i < son[node].size(); ++i) //对每个邻接点
        {
            if (checked[son[node][i]]) //已经访问过了
                is_tree = 0;
            else
            {
                dfs(son[node][i], is_tree, is_btree, size, weight);
            }
        }
    }
    void _dfs(int node, bool &is_tree, bool &is_btree, int &size, int &weight)
    {
        if (checked[node] || !exist[node])
            return; //递归终止
        checked[node] = 1;
        size++;
        weight += node;
        if (indeg[node] > 1) //入度>=1
        {
            is_tree = 0;
            // cout << node << " 的 indeg:" << indeg[node] << endl;
        }
        if (num_of_son[node] > 2) //儿子多于两个
        {
            is_btree = 0;
            // cout<<node<<"has son:"<<num_of_son[node]<<endl;
        }
        for (int i = 0; i < strict_son[node].size(); ++i) //对每个邻接点
        {
            if (checked[strict_son[node][i]]) //已经访问过了
                is_tree = 0;
            else
            {
                // cout<<"准备访问"<<strict_son[node][i]<<endl;
                _dfs(strict_son[node][i], is_tree, is_btree, size, weight);
            }
        }
    }
    void print()
    {
        int num_of_graph = node.size() + tree.size() + b_tree.size() + _graph.size();
        cout << "We have recognized " << num_of_graph << " graph";
        if (num_of_graph > 1)
            cout << "s.\n";
        else
            cout << ".\n";
        for (int i = 0; i < node.size(); ++i)
            cout << "--Node. Weight: " << node[i].first << ". Size: " << node[i].second << "." << endl;
        for (int i = 0; i < b_tree.size(); ++i)
            cout << "--Binary tree. Weight: " << b_tree[i].first << ". Size: " << b_tree[i].second << "." << endl;
        for (int i = 0; i < tree.size(); ++i)
            cout << "--Tree. Weight: " << tree[i].first << ". Size: " << tree[i].second << "." << endl;
        for (int i = 0; i < _graph.size(); ++i)
            cout << "--Graph. Weight: " << _graph[i].first << ". Size: " << _graph[i].second << "." << endl;
    }
    void _sort()
    {
        sort(node.begin(), node.end(), cmp);
        sort(tree.begin(), tree.end(), cmp);
        sort(b_tree.begin(), b_tree.end(), cmp);
        sort(_graph.begin(), _graph.end(), cmp);
    }
};