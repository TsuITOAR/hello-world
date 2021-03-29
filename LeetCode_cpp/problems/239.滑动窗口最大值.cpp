/*
 * @lc app=leetcode.cn id=239 lang=cpp
 *
 * [239] 滑动窗口最大值
 */
#include <set>
#include <vector>
using namespace std;

// @lc code=start
class Solution
{
  public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        if (nums.empty()) return {};
        multiset<int> win(nums.begin(), nums.begin() + k);
        vector<int>   ret{*win.rbegin()};
        for (vector<int>::iterator bg = nums.begin(), ed = bg + k; ed != nums.end(); ++ed, ++bg) {
            win.erase(win.find(*bg));
            win.insert(*ed);
            ret.push_back(*win.rbegin());
        }
        return ret;
    }
};
// @lc code=end
