/*
 * @lc app=leetcode.cn id=140 lang=cpp
 *
 * [140] 单词拆分 II
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;
// @lc code=start
class Solution
{
public:
    vector<string> wordBreak(string s, vector<string> &wordDict)
    {
        ans.assign(s.size(), {});
        wordAssemble(s, wordDict, 0);
        return ans[0];
    }

private:
    vector<string> wordAssemble(string &s, vector<string> &wordDict, vector<string>::size_type start)
    {
        if (start == s.size())
            return {{""}};
        if (!ans[start].empty())
            return ans[start];
        vector<string> tem;
        for (const auto &r : wordDict)
        {
            if (!s.compare(start, r.size(), r))
            {
                cout << r << ' ' << start << endl;
                tem = wordAssemble(s, wordDict, start + r.size());
                for (const auto &c : tem)
                {
                    if (!c.empty())
                        ans[start].push_back(r + ' ' + c);
                    else
                        ans[start].push_back(r);
                }
            }
        }
        return ans[start];
    }
    vector<vector<string>> ans;
};
// @lc code=end

