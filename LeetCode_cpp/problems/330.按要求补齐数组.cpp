/*
 * @lc app=leetcode.cn id=330 lang=cpp
 *
 * [330] 按要求补齐数组
 */
#include <set>
#include <vector>
using namespace std;
// @lc code=start
class Solution
{
  public:
    int minPatches(vector<int>& nums, int n) {
        set<int> sums;
        for (const auto& r : nums) {
            if (r > n) break;
            set<int> tem;
            for (auto it = sums.begin(); it != sums.end(); ++it) {
                if (*it + r > n) break;
                tem.insert(*it + r);
            }
            sums.insert(tem.begin(), tem.end());
            sums.insert(r);
        }
        set<int> comp;

        unsigned long long last = sums.empty() ? 0 : *sums.rbegin();
        for (int i = 1; i <= last; ++i) {
            if (!sums.count(i)) comp.insert(i);
        }
        int ret = 0;

        while (!comp.empty() && *comp.begin() <= n) {
            ++ret;
            set<int> tem;
            auto     it        = comp.begin();
            int      inserting = *it;
            for (; it != comp.end(); ++it) {
                int sum = *it + inserting;
                if (sum > n) break;
                if (sum > last || comp.count(sum)) tem.insert(sum);
            }
            swap(comp, tem);
            last += inserting;
        }
        if (comp.empty()) {
            while (last < n) {
                last = 2 * last + 1;
                ++ret;
            }
        }
        return ret;
    }
};
// @lc code=end
