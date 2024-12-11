#include <string>
#include <map>
using namespace std;
class Solution
{
public:
    map<pair<string, string>, bool> Table;
    bool isMatch(string s, string p)
    {
        pair<string, string> current_pair = make_pair(s, p);
        if (Table.find(current_pair) != Table.end())
        {
            return Table[current_pair];
        }
        if (p.length() == 0 && s.length() == 0)
        {
            Table[current_pair] = true;
            return Table[current_pair];
        }
        bool first_match = true;
        first_match = first_match && p.length() != 0 && s.length() != 0 && (p[0] == s[0] || p[0] == '.');
        if (p.length() >= 2)
        {
            if (p[1] == '*')
            {
                Table[current_pair] = isMatch(s, p.substr(2)) || (first_match && isMatch(s.substr(1), p));
                return Table[current_pair];
            }
        }
        Table[current_pair] = first_match && isMatch(s.substr(1), p.substr(1));
        return Table[current_pair];
    }
};
