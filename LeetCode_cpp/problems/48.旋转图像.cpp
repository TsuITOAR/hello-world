/*
 * @lc app=leetcode.cn id=48 lang=cpp
 *
 * [48] 旋转图像
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution
{
  public:
    void rotate(vector<vector<int>>& matrix) {
        auto m   = matrix.size();
        int  tem = 0;
        for (vector<vector<int>>::size_type i = 0; i < m / 2; ++i) {
            for (vector<int>::size_type j = i; j < m - 1 - i; ++j) {
                tem                          = matrix[i][j];
                matrix[i][j]                 = matrix[m - 1 - j][i];
                matrix[m - 1 - j][i]         = matrix[m - 1 - i][m - 1 - j];
                matrix[m - 1 - i][m - 1 - j] = matrix[j][m - 1 - i];
                matrix[j][m - 1 - i]         = tem;
            }
        }
    }
};
// @lc code=end
