/*
 * @lc app=leetcode.cn id=62 lang=cpp
 *
 * [62] 不同路径
 */
// @lc code=start
class Solution
{
  public:
    int uniquePaths(int m, int n) {
        --n;
        --m;
        if (m == 0 || n == 0) return 1;
        long count = 1;
        if (m < n) {
            m = m ^ n;
            n = m ^ n;
            m = m ^ n;
        }
        for (int i = 1; i <= m; ++i) count = count * (n + i) / i;
        return count;
    }
};
// @lc code=end
