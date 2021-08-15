vector<string> keywords = {"alignas", "alignof", "and", "and_eq",
                           "asm", "atomic_cancel", "atomic_commit", "atomic_noexcept",
                           "auto", "bitand", "bitor", "bool",
                           "break", "case", "catch", "char",
                           "char8_t", "char16_t", "char32_t", "class",
                           "compl", "concept", "const", "consteval",
                           "constexpr", "constinit", "const_cast", "continue",
                           "co_await", "co_return", "co_yield", "decltype",
                           "default", "define", "defined", "delete",
                           "do", "double", "dynamic_cast", "elif",
                           "else", "error", "endif", "enum",
                           "explicit", "export", "extern", "false",
                           "final", "float", "for", "friend",
                           "goto", "if", "ifdef", "ifndef",
                           "import", "include", "inline", "int",
                           "line", "long", "module", "mutable",
                           "namespace", "new", "noexcept", "not",
                           "not_eq", "nullptr", "operator", "or",
                           "or_eq", "override", "pragma", "private",
                           "protected", "public", "reflexpr", "register",
                           "reinterpret_cast", "requires", "return", "short",
                           "signed", "sizeof", "static", "static_assert",
                           "static_cast", "struct", "switch", "synchronized",
                           "template", "this", "thread_local", "throw",
                           "xor_eq", "true", "try", "typedef",
                           "typeid", "typename", "undef", "union",
                           "unsigned", "using", "virtual", "void",
                           "volatile", "wchar_t", "while", "xor"};
inline bool _is_num(char x)
{
    return x >= '0' && x <= '9';
}
class code
{
private:
    vector<string> vct;
    // bool is_note = false;

public:
    code() {}
    void get_words(string str)
    {
        static bool is_note = false;
        string tmp;
        int len = str.length();
        int pos = 0;
        while (pos < len)
        {
            if (is_sep(str[pos])) //遇到分隔
            {
                if (!tmp.empty() && !is_note)
                    vct.push_back(move(tmp));
                tmp.clear();
                if (pos + 1 < len && str[pos] == '/' && str[pos + 1] == '/' && !is_note)
                    return;
                else if (pos + 1 < len && str[pos] == '/' && str[pos + 1] == '*' && !is_note)
                {
                    is_note = true;
                    ++pos;
                }
                else if (pos + 1 < len && str[pos] == '*' && str[pos + 1] == '/' && is_note)
                {
                    is_note = false;
                    ++pos;
                }
                else if (str[pos] == '\\')
                    ++pos;
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
    }
    bool is_sep(char x)
    {
        if (!((x <= 'z' && x >= 'a') || (x <= 'Z' && x >= 'A') || (x <= '9' && x >= '0')) && x != '_')
            return true;
        return false;
    }
    void print()
    {
        string prev = "";
        for (int i = 0; i < vct.size(); ++i)
        {
            bool is_key = false, is_num = true;
            for (int j = 0; j < keywords.size(); ++j)
                if (vct[i] == keywords[j])
                {
                    is_key = true;
                    break;
                }
            for (int j = 0; j < vct[i].size(); ++j)
                if (vct[i][j] > '9' || vct[i][j] < '0')
                {
                    is_num = false;
                    break;
                }
            if (!is_key && !is_num && vct[i] != prev && !_is_num(vct[i][0]))
            {
                cout << vct[i] << ' ';
                prev = vct[i];
            }
        }
        return;
    }
};