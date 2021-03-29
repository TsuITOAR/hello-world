/*
 * @lc app=leetcode.cn id=22 lang=cpp
 *
 * [22] 括号生成
 */
#include <iostream>
#include <vector>
using namespace std;
// @lc code=start
class Solution
{
  public:
    vector<string> generateParenthesis(int n) {
        r.assign(n, {});
        r[0].push_back("()");
        for (vector<vector<string>>::size_type i = 2; i <= n; ++i) {
            if (!r[i - 1].empty())
                continue;
            auto tem = assemble(i - 1);
            cout << "Order " << i << endl;
            for (const auto& c : tem) {
                r[i - 1].push_back(eat(c));
                cout << r[i - 1].back() << endl;
            }
        }
        return assemble(n);
    }

  private:
    string eat(const string& s) { return '(' + s + ')'; }

    vector<string> assemble(int n) {
        if (n == 1)
            return r[0];
        vector<string> ret(r[n - 1].begin(), r[n - 1].end());
        for (int i = 1; i < n; ++i) {
            auto tem = assemble(n - i);
            for (const auto& u : r[i - 1]) {
                for (const auto& v : tem) {
                    ret.push_back(u + v);
                }
            }
        }
        return ret;
    }

    vector<vector<string>> r;
};
// @lc code=end
