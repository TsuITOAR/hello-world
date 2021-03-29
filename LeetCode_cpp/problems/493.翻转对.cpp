/*
 * @lc app=leetcode.cn id=493 lang=cpp
 *
 * [493] 翻转对
 */
#include <iostream>
#include <map>
#include <vector>
using namespace std;
// @lc code=start
class Solution
{
  public:
    int reversePairs(vector<int>& nums) {
        if (nums.empty())
            return 0;
        map<int, int> harsh;
        ++harsh[nums.back()];
        int count = 0;
        for (vector<int>::size_type i = nums.size() - 2; i != (vector<int>::size_type) - 1; --i) {
            for (map<int, int>::reverse_iterator j(harsh.upper_bound(nums[i] / 2 - (1 - nums[i] % 2))); j != harsh.rend(); ++j) {
                count += (*j).second;
            }
            ++harsh[nums[i]];
        }
        return count;
    }
};
// @lc code=end
