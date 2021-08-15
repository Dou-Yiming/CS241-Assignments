#include "std_lib_facilities.h"
class Huffman1
{
private:
    struct hfNode
    {
        int weight = 0;
    };
    hfNode a[300];
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
    int num_letter[200] = {0};
    Huffman1()
    {
    }
    void get_letter(string str)
    {
        for (int i = 0; i < str.length(); ++i)
            num_letter[str[i]]++;
    }
    bool is_letter(char x)
    {
        return (x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z');
    }
    void encode()
    {
        for (int i = 0; i < 200; ++i)
        {
            if (num_letter[i])
            {
                a[++pos].weight = num_letter[i];
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
        return;
    }
    void print()
    {
        cout << ans;
        return;
    }
};
