/*
 * @lc app=leetcode.cn id=1658 lang=cpp
 *
 * [1658] 将 x 减到 0 的最小操作数
 */
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
// @lc code=start
class Solution
{
  public:
    int minOperations(vector<int>& nums, int x) {
        if (nums.front() == x || nums.back() == x)
            return 1;
        vector<int> po(nums), ne(nums);
        int         ans = INT_MAX;
        for (vector<int>::size_type i = 0; i < nums.size() - 1; ++i) {
            po[i + 1] += po[i];
            if (po[i + 1] == x)
                ans = fmin(i + 1 + 1, ans);
            ne[nums.size() - 1 - (i + 1)] += ne[nums.size() - 1 - i];
            if (ne[nums.size() - 1 - (i + 1)] == x)
                ans = fmin(i + 1 + 1, ans);
        }
        if (ne[0] < x)
            return -1;
        else if (ne[0] == x)
            return nums.size();
        for (vector<int>::size_type i = 0, j = 1; i <= nums.size(); ++i) {
            if (po[i] > x)
                break;
            for (; j < nums.size(); ++j) {
                if (po[i] + ne[j] == x) {
                    cout << i << ',' << j << endl;
                    ans = fmin(ans, i + 1 + (nums.size() - 1) - j + 1);
                }
                else if (po[i] + ne[j] > x)
                    continue;
                else
                    break;
            }
        }
        if (ans != INT_MAX)
            return ans;
        else
            return -1;
    }
};
// @lc code=end
