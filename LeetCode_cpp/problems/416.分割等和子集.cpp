/*
 * @lc app=leetcode.cn id=416 lang=cpp
 *
 * [416] 分割等和子集
 */
#include <algorithm>
#include <numeric>
#include <set>
#include <vector>
using namespace std;
// @lc code=start
class Solution
{
  public:
    bool canPartition(vector<int>& nums) {
        set<int> tem, ans;
        int      goal = accumulate(nums.begin(), nums.end(), 0);
        if (goal % 2 != 0) return 0;
        goal /= 2;
        if (nums.front() == goal) return 1;
        ans = {0, nums.front()};
        tem = ans;
        for (auto it = nums.begin() + 1; it != nums.end(); ++it) {
            for (const auto& r : ans) {
                if (r + *it == goal)
                    return 1;
                else if (r + *it < goal)
                    tem.insert(r + *it);
            }
            ans = tem;
        }
        return 0;
    }
};
// @lc code=end
