#include <iostream>
#include <vector>
using namespace std;
namespace TrappingRainWater
{
    class Solution
    {
    public:
        int trap(vector<int> &height)
        {
            ssize_t len = height.size();
            ssize_t prefix = 0, lastMaxPrefix = 0;
            ssize_t suffix = 0, lastMaxSuffix = 0;
            ssize_t sum = 0;
            for (ssize_t i = 0; i < len; i++)
            {
                ssize_t h = height[i];
                // cout << h << endl;
                // cumulate height
                sum += h;
                // test if is new max;
                if (h > lastMaxPrefix)
                {
                    prefix += i * (h - lastMaxPrefix);
                    lastMaxPrefix = h;
                }
            }
            for (ssize_t i = 0; i < len; i++)
            {
                ssize_t j = len - 1 - i;
                ssize_t h = height[j];
                // cout << h << endl;
                // test if is new max;
                if (h > lastMaxSuffix)
                {
                    suffix += i * (h - lastMaxSuffix);
                    lastMaxSuffix = h;
                }
                if (lastMaxSuffix == lastMaxPrefix)
                {
                    break;
                }
            }
            return lastMaxPrefix * len - prefix - suffix - sum;
        }
    };
    Solution S;
} // namespace TrappingRainWater
