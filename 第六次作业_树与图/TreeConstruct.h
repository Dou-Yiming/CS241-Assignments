struct node
{
    string code;
    int weight;
    // node(node &other)
    // {
    //     code = other.code;
    //     weight = other.weight;
    // }
    node copy()
    {
        node ans;
        ans.code = code;
        ans.weight = weight;
        return ans;
    }
    node() {}
};
bool is_letter(char x)
{
    return x >= 'a' && x <= 'z' || x >= 'A' && x <= 'Z';
}
bool _cmp(const node &a, const node &b)
{
    return a.weight > b.weight;
}
int to_num(string code)
{
    int ans = 0;
    int tmp = 1;
    for (int i = code.size() - 1; i >= 0; --i)
    {
        if (code[i] == '1')
            ans += tmp;
        tmp *= 2;
    }
    return ans;
}
class Tree
{
private:
    vector<int> son[10000];
    int level[10000] = {0};
    node n[10000];
    bool exist[10000] = {0};
    int indeg[10000] = {0};
    void post_order(int x)
    {
        n[x].code = "1";
        int max_level = 0;
        for (int i = 0; i < son[x].size(); ++i) //对每个儿子
        {
            post_order(son[x][i]);
            n[son[x][i]].weight = to_num(n[son[x][i]].code);
            if (level[son[x][i]] > max_level)
                max_level = level[son[x][i]];
        }
        level[x] = max_level + 1;
        vector<node> tmp;
        for (int i = 0; i < son[x].size(); ++i)
            tmp.push_back(n[son[x][i]].copy());
        _sort(tmp);

        for (int i = 0; i < son[x].size(); ++i)
            n[x].code += tmp[i].code;

        n[x].code += "0";
        return;
    }
    void _sort(vector<node> &x)
    {
        sort(x.begin(), x.end(), _cmp);
    }

public:
    Tree() {}
    bool get_relation(string str)
    {
        for (int i = 0; i < str.length(); ++i)
        {
            if (str[i] == '<')
            {
                ++i;
                int flag = 0;
                int num1, num2;
                while (str[i] != '>')
                {
                    if (is_letter(str[i]))
                    {
                        // int tmp = str[i] <= 'Z' ? str[i] - 'A' : str[i] - 'a';
                        int tmp=str[i]-'A';
                        ++i;
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
                    son[num2].push_back(num1);
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
    void print()
    {
    }
    std::pair<int, string> ans()
    {
        int root;
        for (int i = 0; i < 10000; ++i)
            if (exist[i] && indeg[i] == 0) //根节点
            {
                root = i;
                break;
            }
        return std::make_pair(level[root], n[root].code);
    }
    void cal()
    {
        for (int i = 0; i < 10000; ++i)
        {
            if (exist[i] && indeg[i] == 0) //根节点
            {
                post_order(i);
                // cout << "searching" << i << endl;
                return;
            }
        }
    }
};