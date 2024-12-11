#include <iostream>
#include <22.GenerateParentheses.h>
#include <32.LongestValidParentheses.h>
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
    return 0;
}