/*
 * @lc app=leetcode.cn id=316 lang=cpp
 *
 * [316] 去除重复字母
 */
#include <string>
using namespace std;
// @lc code=start
class Solution
{
  public:
    string removeDuplicateLetters(string s) {
        int harsh[26] = {0}, set[26] = {0};
        for (const auto& r : s) ++harsh[r - 'a'];
        string ret;
        for (const auto& r : s) {
            if (set[r - 'a'] == 0) {
                if (ret.empty() || r > ret.back()) {
                    ret.push_back(r);
                    set[r - 'a'] = 1;
                }
                else {
                    while (!ret.empty() && r <= ret.back() && harsh[ret.back() - 'a'] >= 1) {
                        set[ret.back() - 'a'] = 0;
                        ret.pop_back();
                    }
                    ret.push_back(r);
                    set[r - 'a'] = 1;
                }
            }
            --harsh[r - 'a'];
        }
        return ret;
    }
};
// @lc code=end
