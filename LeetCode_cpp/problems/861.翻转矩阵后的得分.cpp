/*
 * @lc app=leetcode.cn id=861 lang=cpp
 *
 * [861] 翻转矩阵后的得分
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution
{
  public:
    int matrixScore(vector<vector<int>>& A) {
        int ret = 0, tem = 0;
        for (vector<int>::size_type i = 0; i < A.front().size(); ++i) {
            tem = 0;
            for (vector<vector<int>>::size_type j = 0; j < A.size(); ++j) {
                if (A[j].front())
                    tem += A[j][i];
                else
                    tem += 1 - A[j][i];
            }
            tem = A.size() - tem > tem ? A.size() - tem : tem;
            ret = (ret << 1) + tem;
        }
        return ret;
    }
};
// @lc code=end
