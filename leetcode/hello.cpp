#include <iostream>
#include <22.GenerateParentheses.h>
#include <32.LongestValidParentheses.h>
#include <42.TrappingRainWater.h>
#include <vector>
using namespace std;

int main()
{
    cout << "GenerateParentheses" << endl;
    for (auto &x : GenerateParentheses::S.generateParenthesis(2))
    {
        cout << x << endl;
    }

    cout << "LongestValidParentheses" << endl;
    cout << LongestValidParentheses::S.longestValidParentheses(")()())") << endl;

    cout << "TrappingRainWater" << endl;
    vector<int> e = vector({0, 2, 0});
    cout << TrappingRainWater::S.trap(e) << endl;
    return 0;
}