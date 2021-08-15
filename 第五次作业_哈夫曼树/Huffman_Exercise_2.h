#include "std_lib_facilities.h"
class Huffman2
{
private:
    vector<string> vct;
    struct hfNode
    {
        int weight = 0;
    };
    hfNode a[100];
    int pos = 0, ans = 0;
    void swap(hfNode &x, hfNode &y)
    {
        int tmp2 = x.weight;
        x.weight = y.weight;
        y.weight = tmp2;
    }
    void percolateUp(int pos)
    {
        while (pos > 1 && a[pos / 2].weight > a[pos].weight)
        {
            swap(a[pos / 2], a[pos]);
            pos /= 2;
        }
    }
    void percolateDown(int pos, int n)
    {
        while (pos * 2 <= n)
        {
            int child = pos * 2;
            if (child + 1 <= n && a[child + 1].weight < a[child].weight)
                ++child;
            if (a[pos].weight > a[child].weight)
                swap(a[pos], a[child]);
            else
                break;
            pos = child;
        }
    }
    int pop(int &pos)
    {
        int ans = a[1].weight;
        a[1].weight = a[pos--].weight;
        percolateDown(1, pos);
        return ans;
    }

public:
    Huffman2() {}
    int num[300] = {0};
    int num_not_letter = 0;
    bool is_letter(char x)
    {
        return (x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z');
    }
    void encode()
    {
        int cur = 0;
        string prev = vct[0];
        num[++cur] = 1;
        for (int i = 1; i < vct.size(); ++i)
        {
            if (vct[i] == prev)
                ++num[cur];
            else
            {
                prev = vct[i];
                num[++cur]++;
            }
        }
        // for (int i = 0; i < 300; ++i)
        //     cout << num[i] << ' ';
        for (int i = 1; i < 300; ++i)
        {
            if (num[i])
            {
                a[++pos].weight = num[i];
                percolateUp(pos);
            }
        }
        //每次编码
        int n = pos;
        for (int i = 0; i < n - 1; ++i)
        {
            int x = pop(pos);
            int y = pop(pos);
            a[++pos].weight = (x + y);
            percolateUp(pos);
            ans += (x + y);
        }
        ans += 8 * num_not_letter;
        return;
    }
    void print()
    {
        // cout << endl
        //      << ans - 8 * num_not_letter << endl;
        cout << ans;
        return;
    }
    void get_words(string str)
    {
        static bool is_note = false;
        string tmp;
        int len = str.length();
        int pos = 0;
        while (pos < len)
        {
            if (!is_letter(str[pos])) //遇到分隔
            {
                if (!tmp.empty() && !is_note)
                    vct.push_back(move(tmp));
                tmp.clear();
                num_not_letter++;
            }
            else
                tmp += str[pos];
            ++pos;
        }
        if (!tmp.empty() && !is_note)
            vct.push_back(tmp);
    }
    void _sort()
    {
        sort(vct.begin(), vct.end());
        // for (int i = 0; i < vct.size(); ++i)
        //     cout << vct[i] << ' ';
        // cout<<endl;
    }
};
