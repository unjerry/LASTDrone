#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
using namespace std;
namespace GenerateParentheses
{
    class Solution
    {
    public:
        map<int, vector<string>> Table;
        vector<string> generateParenthesis(int n)
        {
            if (n == 1)
            {
                vector<string> vec = {"()"};
                return vec;
            }
            set<string> compos;
            for (size_t i = 1; i < n; i++)
            {
                vector<string> prefixvec;
                vector<string> suffixvec;
                vector<string> middlevec;
                if (Table.find(i) != Table.end())
                {
                    prefixvec = Table[i];
                }
                else
                {
                    prefixvec = generateParenthesis(i);
                }

                if (Table.find(n - i) != Table.end())
                {
                    suffixvec = Table[n - i];
                }
                else
                {
                    suffixvec = generateParenthesis(n - i);
                }

                if (Table.find(n - 1) != Table.end())
                {
                    middlevec = Table[n - 1];
                }
                else
                {
                    middlevec = generateParenthesis(n - 1);
                }
                set<string> prefix = set(prefixvec.begin(), prefixvec.end());
                set<string> suffix = set(suffixvec.begin(), suffixvec.end());
                set<string> middle = set(middlevec.begin(), middlevec.end());
                for (auto &pre : prefix)
                {
                    for (auto &suf : suffix)
                    {
                        compos.insert(pre + suf);
                    }
                }
                for (auto &mid : middle)
                {
                    compos.insert("(" + mid + ")");
                }
            }
            vector<string> vec = vector<string>(compos.begin(), compos.end());
            sort(vec.begin(), vec.end());
            return vec;
        }
    };
    Solution S;
} // namespace name
