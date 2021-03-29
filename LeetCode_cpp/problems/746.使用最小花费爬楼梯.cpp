/*
 * @lc app=leetcode.cn id=746 lang=cpp
 *
 * [746] 使用最小花费爬楼梯
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution
{
  public:
    int minCostClimbingStairs(vector<int>& cost) {
        if (cost.empty()) return 0;
        ans.assign(cost.size(),-1);
        return fmin(minCostfromX(cost, 0), minCostfromX(cost, 1));
    }

  private:
    auto minCostfromX(vector<int>& cost, vector<int>::size_type x) -> int {
        if (x + 2 >= cost.size()) return cost[x];
        if (ans[x] == -1) ans[x]=fmin(minCostfromX(cost, x + 1), minCostfromX(cost, x + 2)) + cost[x];
        return ans[x];
    }
    vector<int> ans;
};
// @lc code=end
