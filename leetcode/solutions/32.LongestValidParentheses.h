#include <string>
#include <map>
#include <iostream>
using namespace std;
namespace LongestValidParentheses
{
#define MAX(a, b) ((a > b) ? (a) : (b))
    class Solution
    {
    public:
        ssize_t max_len;
        int longestValidParentheses(string s)
        {
            ssize_t heights[30000] = {0};
            ssize_t las_pos[30000] = {0};
            las_pos[0] = -1;
            ssize_t edstk = 0;
            bool brk = false;
            for (ssize_t i = 0; i < s.length(); i++)
            {
                char c = s[i];
                // cout << c << " " << heights[i] << ":";
                if (c == '(')
                {
                    edstk++;
                    las_pos[edstk] = i;
                    if (edstk == 1 && brk)
                    {
                        las_pos[0] = i - 1;
                        brk = false;
                    }
                }
                else
                {
                    if (edstk <= 0)
                    {
                        edstk = 0;
                        brk = true;
                    }
                    else
                    {
                        edstk--;
                        max_len = MAX(max_len, i - las_pos[edstk]);
                    }
                }
                // heights[i] = edstk;
                // cout << c << " " << heights[i] << ":";
                // for (ssize_t j = 0; j < s.length(); j++)
                // {
                //     cout << las_pos[j] << " ";
                // }
                // cout << endl;
            }
            // max_len = MAX(acc_len, max_len);
            // max_len = MAX(tmp_len, max_len);
            return max_len;
        }
    };
    Solution S;
} // namespace LongestValidParentheses
