#ifndef TOKEN_EXERCISE_H
#define TOKEN_EXERCISE_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <string>
#include <map>

void small_change(string &str)
{
    int len = str.size();
    for (int i = 0; i < len; i++)
        if (str[i] <= 'Z' && str[i] >= 'A')
            str[i] = str[i] - 'A' + 'a';
}

int checkout(const string &str)
{
    int len = str.size();
    if (str == "")
        return 0;
    if (len == 1 && (str[0] == '_' || str[0] == '-'))
        return 0;
    for (int i = 0; i < len; i++)
        if (!((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '-' || str[i] == '_'))
            return 0;
    return 1;
}

class token_exercise
{
    friend int checkout(const string &str);
    friend void small_change(string &str);

private:
    std::map<string, int> mp_token;

public:
    token_exercise()
    {
        mp_token.clear();
    }

    void get_count(const string &str)
    {
        int i, len = str.size();
        string in = "";
        for (i = 0; i < len; i++)
            if ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || str[i] == '-' || str[i] == '_')
                in += str[i];
            else
            {
                //cout<<in<<endl;
                if (checkout(in))
                {
                    small_change(in);
                    cout << in << endl;
                    if (mp_token.find(in) == mp_token.end())
                        mp_token[in] = 1;
                    else
                        mp_token[in]++;
                    in = "";
                }
                else
                {
                    in = "";
                    continue;
                }
            }
        if (checkout(in))
        {
            small_change(in);
            cout << in << endl;
            if (mp_token.find(in) == mp_token.end())
                mp_token[in] = 1;
            else
                mp_token[in]++;
            in = "";
        }
    }

    void get_words()
    {
        string str, sy;
        while (cin >> str)
        {
            sy = str;
            small_change(str);
            std::cout << '(' << sy << ',' << mp_token[str] << ')' << ' ';
        }
        std::cout << std::endl;
    }
};

#endif