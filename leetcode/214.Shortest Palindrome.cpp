#include <algorithm>
#include <string>
#include <iostream>
using namespace std;
class Solution
{
public:
    string shortestPalindrome(string s)
    {
        if (s.length() == 0)
        {
            return s;
        }
        auto prefix = longestPalindrome(s);
        auto st = prefix.second;
        auto pre = s.substr(st, s.length() - st);
        reverse(pre.begin(), pre.end());
        return pre + s;
    }
    pair<size_t, size_t> longestPalindrome(string s)
    {
        size_t slen = s.length();
        size_t ans_start = 0;
        size_t max_length = 1;
        bool T[2][slen] = {false};
        const char *cs = s.c_str();
        for (size_t i = 0; i < slen; i++)
        {
            for (size_t j = 1; i >= j && i + j < slen; j++)
            {
                if (cs[i - j] == cs[i + j])
                {
                    if (j * 2 + 1 > max_length && i == j)
                    {
                        max_length = j * 2 + 1;
                        ans_start = i - j;
                    }
                }
                else
                {
                    break;
                }
            }
        }
        for (size_t i = 0; i + 1 < slen; i++)
        {
            for (size_t j = 0; i >= j && i + j + 1 < slen; j++)
            {
                if (cs[i - j] == cs[i + 1 + j])
                {
                    if ((j + 1) * 2 > max_length && i == j)
                    {
                        ans_start = i - j;
                        max_length = (j + 1) * 2;
                    }
                }
                else
                {
                    break;
                }
            }
        }
        return make_pair(ans_start, max_length);
    }
};
