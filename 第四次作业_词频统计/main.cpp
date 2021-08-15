#include "std_lib_facilities.h"
#include "Token_Exercise_1.h"
#include "Code_Exercise_2.h"
#include <cstdio>
int count(string str, string word);
bool is_sep(char x);
char get_letter(string words);
int pos = 0;
int main()
{
    /********** Begin **********/
    bool exercise_1 = false;
    if (exercise_1)
    {
        //第一关执行代码
        //Please fix Token_Exercise_1.h and Token_Exercise_1.cpp
        string str;
        getline(cin, str);
        string word, words;
        getline(cin, words);
        char letter;
        while (pos != words.length())
        {
            letter = get_letter(words);
            if (letter != ' ')
                word += letter;
            else
            {
                cout << "(" << word << "," << count(str, word) << ") ";
                word = "";
                // word.clear();
                // cout<<word.size();
            }
        }
        cout << "(" << word << "," << count(str, word) << ")";
    }
    else
    {
        //第二关执行代码
        //Please fix Code_Exercise_2.h and Code_Exercise_2.cpp
        string str;
        code c;
        while (getline(cin, str))
        {
            c.get_words(str);
        }
        c._sort();
        c.print();
    }
    /********** End **********/
    return 0;
}
int count(string str, string word)
{
    int len = str.length();
    int word_len = word.length();
    int i = 0;
    int ans = 0;
    while (i < len)
    {
        for (int j = 0; j < word_len; ++j)
        {
            if (i + j < len &&
                (word[j] == str[i + j] ||
                 (word[j] <= 'Z' && word[j] >= 'A' && word[j] == str[i + j] - 'a' + 'A') || (str[i + j] <= 'Z' && str[i + j] >= 'A' && str[i + j] == word[j] - 'a' + 'A')))
                continue;
            else
                goto next;
        }
        if (i == 0 || is_sep(str[i - 1]) || ((str[i - 1] == '-' || str[i - 1] == '_') && (i == 1 || is_sep(str[i - 2]))))
            if (i + word_len == len || is_sep(str[i + word_len]))
                ++ans;
            else if (str[i + word_len] == '-' || str[i + word_len] == '_')
            {
                if (i + word_len + 1 < len && is_sep(str[i + word_len + 1]))
                    ++ans;
                else if (i + word_len + 1 == len)
                    ++ans;
            }
    next:
        ++i;
    }
    return ans;
}
bool is_sep(char x)
{
    if (!((x <= 'z' && x >= 'a') || (x <= 'Z' && x >= 'A') || (x <= '9' && x >= '0')) && x != '-' && x != '_')
        return true;
    return false;
}
char get_letter(string words)
{
    if (pos != words.length())
        return words[pos++];
    return 'a';
}