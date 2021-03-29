/*
 * @lc app=leetcode.cn id=435 lang=cpp
 *
 * [435] 无重叠区间
 */
#include <algorithm>
#include <vector>
using namespace std;
// @lc code=start
class Solution
{
  public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if (intervals.empty()) return 0;
        sort(intervals.begin(), intervals.end(), [](const vector<int>& a, const vector<int>& b) { return a.front() < b.front(); });
        int edge = intervals.front().back();
        int ret  = 0;
        for (auto it = intervals.begin() + 1; it != intervals.end(); ++it) {
            if (edge <= it->front())
                edge = it->back();
            else {
                ++ret;
                edge = fmin(edge, it->back());
            }
        }
        return ret;
    }
};
// @lc code=end
