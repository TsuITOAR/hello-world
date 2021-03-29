/*
 * @lc app=leetcode.cn id=842 lang=cpp
 *
 * [842] 将数组拆分成斐波那契序列
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;
// @lc code=start
class Solution
{
  public:
    vector<int> splitIntoFibonacci(string S) {
        vector<int>       ret;
        string::size_type pos;

        for (string::size_type i = 1; i < S.size() / 2 + S.size() % 2; ++i) {
            if (S[0] == '0' && i != 1) break;
            if (i > 9 && stol(S.substr(0, i)) > INT_MAX) break;
            for (string::size_type j = 1; j < S.size() / 2 + S.size() % 2; ++j) {
                if (S[i] == '0' && j != 1) break;
                if (j > 9 && stol(S.substr(i, j)) > INT_MAX) break;
                ret.clear();
                ret.push_back(stoi(S.substr(0, i)));
                int tem = ret.back();
                ret.push_back(stoi(S.substr(i, j)));
                pos = i + j;
                while (pos < S.size()) {
                    long curnum = (long)ret.back() + (long)tem;
                    if (curnum > INT_MAX) break;
                    string curstr = to_string(curnum);
                    if (S.compare(pos, curstr.size(), curstr) == 0) {
                        tem = ret.back();
                        ret.push_back(curnum);
                        pos += curstr.size();
                    }
                    else
                        break;
                }
                if (pos == S.size() && ret.size() >= 3)
                    return ret;
            }
        }
        return {};
    }
};
// @lc code=end
